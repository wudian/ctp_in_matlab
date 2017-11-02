
#include "MDSQLite.h"
#include <sstream>
#include <boost/algorithm/string.hpp>  
#include <SQLite3/sqlite3.h>
#include "CTPRspMsgQueue.h"
#include "toolkit.h"
#include "MarketData.h"
#include "CTPRspMsg.h"
#include "CTPLastInfos.h"
#include "defines.h"
#include "Enums.h"

using namespace std;

static const char *S_Period[3]	=	{"tick",		"1m",				"1h"};
static const char *TABLE_NAMES[3] = {"Tick_CTP",	"KLine_CTP_1M",		"KLine_CTP_1H"}; 
static const char *SQLite_Tick_Table_Format =
	"create table if not exists %s("
	"InstrumentID varchar(31),	ExchangeTime dateTime,		LocalTime dateTime,		LastPrice double,		BidPrice1 double,"
	"BidVolume1 int,			AskPrice1 double,			AskVolume1 int,			Volume int,				Turnover double,"
	"OpenInterest double,		HighestPrice double,		LowestPrice double,		primary key(InstrumentID, ExchangeTime));"; 

static const char *SQLite_Kline_Table_Format =
	"create table if not exists %s("
	"InstrumentID varchar(31),	ExchangeTime dateTime,		OpenPrice double,		HighPrice double,		LowPrice double,"
	"ClosePrice double,			Volume int,					OpenInterest double,	Period varchar(5),"
	"primary key(InstrumentID, ExchangeTime, Period));";


MDSQLite::MDSQLite(void) 
	: SQLiteBase()
{	
}


MDSQLite::~MDSQLite(void)
{
}

bool MDSQLite::SQLite_Init(void)
{
	if (!SQLiteBase::SQLite_Init())
		return false;

	if (nullptr != m_sqlite3)
		return true;

	extern string g_mdDBPath;
	int res = sqlite3_open(g_mdDBPath.c_str(), &m_sqlite3);
	if (res)
	{
		SQLite_Error_Log(res, "", sqlite3_errmsg(m_sqlite3));
		sqlite3_close(m_sqlite3);
		m_sqlite3 = nullptr;
		return false;
	}

	// 关闭本地磁盘同步 可提高插入速度
	if (!SQLite_EXEC("PRAGMA synchronous = OFF;"))
		return false;
	
	if (!SQLite_Create_Tables())
		return false;
	
	return true;
}

void MDSQLite::SQLite_Finalize()
{
}

// Tick表和K线表
bool MDSQLite::SQLite_Create_Tables()
{
	char sql[1024] = {0};

	for (int i = 0; i < 3; ++i) {
		if (0 == i) {
			sprintf_s(sql, SQLite_Tick_Table_Format, TABLE_NAMES[i]);
		}
		else {
			memset((void*)sql, 0, sizeof(sql));
			sprintf_s(sql, SQLite_Kline_Table_Format, TABLE_NAMES[i]);
		}
		if (!SQLite_EXEC(sql))
			return false;
	}	
		
	return true;
}

void MDSQLite::SQLite_MarketData_Insert(const wdTick &tick)
{	
	for (int i = 0; i < 3; ++i) {
		if (0 == i) {
			SQLite_Tick_Insert(&tick);
			continue;
		}
		int n = GetSeconds(S_Period[i]);
		wdKLine &kline = m_mapInstKLine[tick.InstrumentID][S_Period[i]];
		if (GetTimeNum(tick.ExchangeTime) - GetTimeNum(kline.ExchangeTime) < n) {	// 判断是否切换
			// 不切换 更新K线
			kline.OpenInterest = tick.OpenInterest;//持仓量
			kline.Volume = tick.Volume;//累计成交量
			kline.ClosePrice = tick.LastPrice;
			if (kline.HighestPrice < tick.LastPrice)
				kline.HighestPrice = tick.LastPrice;
			if (kline.LowestPrice > tick.LastPrice)
				kline.LowestPrice = tick.LastPrice;
		}
		else {
			// 切换(超过时间间隔) 保存K线数据
			SQLite_K_Line_Insert(kline);

			// 切换(超过时间间隔 首个数据到来)  添加新K线	
			sprintf_s(kline.InstrumentID, tick.InstrumentID);
			sprintf_s(kline.ExchangeTime, GetKLineExchangeTime(tick, n).c_str());
			kline.OpenPrice = tick.LastPrice;
			kline.HighestPrice = tick.LastPrice;
			kline.LowestPrice = tick.LastPrice;
			kline.ClosePrice = tick.LastPrice;
			kline.OpenInterest = tick.OpenInterest;//持仓量
			kline.Volume = tick.Volume;
			sprintf_s(kline.Period, S_Period[i]);
		}
	}
}

void MDSQLite::AddPeriods(const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod)
{
	for (const string &inst : listInstrumentIDs) {
		m_mapHistoryInstKLine.erase(inst);

		for (const string &period : listPeriod) {
			m_mapHistoryInstKLine[inst][period] = wdKLine();
		}
	}
}

static int SQLite_SubscribeHistory_Callback(void *param, int num, char **values, char **colName)
{
	MDSQLite *mdSql = (MDSQLite*)param;

	map<string, wdKLine> &period_kline = mdSql->GetPeriod_KLine(values[0]);
	for (auto it = period_kline.begin(); it != period_kline.end(); ++it) {
		const string &period = it->first;
		wdKLine &kline = it->second;
		int n = GetSeconds(period);

		if (num == 11) { // tick过来
			if (boost::iequals(period, "tick")) { // 订阅的是tick
				CTick tick(values[0], values[1], values[2], atof(values[3]), atof(values[4]), atoi(values[5]),
					atof(values[6]), atoi(values[7]), atoi(values[8]), atof(values[9]), atof(values[10]), atof(values[11]), atof(values[12]));
				std::shared_ptr<CCTPRspMsgItem> pMsgItem = std::make_shared<CCTPRspMsgItem>(E_fnOnHistoryTick, UNIQUE_REQUEST_ID, nullptr, true, &tick);
				mdSql->InputQueue(pMsgItem);
				continue;
			}
			else if (period.find('s') != string::npos || period.find('S') != string::npos) { // 订阅的是秒数据
				if (GetTimeNum(values[1]) - GetTimeNum(kline.ExchangeTime) < n) {	// 判断是否切换
					// 不切换 更新K线
					kline.OpenInterest = atof(values[10]);//持仓量
					kline.Volume = atoi(values[8]);//累计成交量
					kline.ClosePrice = atof(values[3]);
					if (kline.HighestPrice < atof(values[3]))
						kline.HighestPrice = atof(values[3]);
					if (kline.LowestPrice > atof(values[3]))
						kline.LowestPrice = atof(values[3]);
				}
				else {
					// 切换(超过时间间隔) 保存K线数据
					if (GetTimeNum(kline.ExchangeTime) > 0)
						mdSql->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnHistoryTick, UNIQUE_REQUEST_ID, nullptr, true, &kline));

					// 切换(超过时间间隔 首个数据到来)  添加新K线	
					sprintf_s(kline.InstrumentID, values[0]);
					sprintf_s(kline.ExchangeTime, values[1]);
					kline.OpenPrice = atof(values[3]);
					kline.HighestPrice = atof(values[3]);
					kline.LowestPrice = atof(values[3]);
					kline.ClosePrice = atof(values[3]);
					kline.OpenInterest = atof(values[10]);//持仓量
					kline.Volume = atoi(values[8]);
					sprintf_s(kline.Period, period.c_str());
				}
			}
		}
		else if (num == 9) { // K线过来 1m或1h
			// 由1m线拼凑成任意分钟的K线；  由1h线拼凑成任意h的K线
			if (GetTimeNum(values[1]) - GetTimeNum(kline.ExchangeTime) < n) {	// 判断是否切换
				// 不切换 更新K线
				kline.OpenInterest = atof(values[7]);//持仓量
				kline.Volume = atoi(values[6]);//累计成交量
				kline.ClosePrice = atof(values[5]);
				if (kline.HighestPrice < atof(values[3]))
					kline.HighestPrice = atof(values[3]);
				if (kline.LowestPrice > atof(values[4]))
					kline.LowestPrice = atof(values[4]);
			}
			else {
				// 切换(超过时间间隔) 保存K线数据
				if (GetTimeNum(kline.ExchangeTime) > 0)
					mdSql->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnHistoryKLine, UNIQUE_REQUEST_ID, nullptr, true, &kline));

				// 切换(超过时间间隔 首个数据到来)  添加新K线	
				sprintf_s(kline.InstrumentID, values[0]);
				sprintf_s(kline.ExchangeTime, values[1]);
				kline.OpenPrice = atof(values[2]);
				kline.HighestPrice = atof(values[3]);
				kline.LowestPrice = atof(values[4]);
				kline.ClosePrice = atof(values[5]);
				kline.OpenInterest = atof(values[7]);//持仓量
				kline.Volume = atoi(values[6]);
				sprintf_s(kline.Period, period.c_str());
			}
		}
		else 
			assert(false);		
	}
	return 0;
}

void MDSQLite::SubscribeHistory(const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod, 
								const char *beginTime, const char *endTime)
{
	AddPeriods(listInstrumentIDs, listPeriod);

	char sql[1024] = {0};
	for (const string &inst : listInstrumentIDs) {
		m_mapHasSubscribe[inst][S_Period[0]] = false;
		m_mapHasSubscribe[inst][S_Period[1]] = false;
		m_mapHasSubscribe[inst][S_Period[2]] = false;

		for (const string &period : listPeriod) {
			if (period.find('s') != string::npos || period.find("tick") != string::npos) {
				if (m_mapHasSubscribe[inst][S_Period[0]])
					continue;
				else 
					m_mapHasSubscribe[inst][S_Period[0]] = true;
			}
			else if (period.find('m') != string::npos) {
				if (m_mapHasSubscribe[inst][S_Period[1]])
					continue;
				else 
					m_mapHasSubscribe[inst][S_Period[1]] = true;
			}
				
			else if (period.find('h') != string::npos) {
				if (m_mapHasSubscribe[inst][S_Period[2]])
					continue;
				else 
					m_mapHasSubscribe[inst][S_Period[2]] = true;
			}				
			else {
				LOG_ERROR << "暂不支持这个period: " << period;
				continue;
			}
						
			memset(sql, 0, sizeof(sql));
			sprintf_s(sql, "select * from %s where ExchangeTime between '%s' and '%s';", GetTableName(period).c_str(), beginTime, endTime);
			if (!SQLite_EXEC(sql, SQLite_SubscribeHistory_Callback, this))
				return;
		}
	}
}

void MDSQLite::SQLite_Tick_Insert(const wdTick *tick)
{
	char sql[1024] = {0};
	
	sprintf_s(sql, "replace into %s values("
		"'%s','%s','%s',%g,%g,"
		"%d,%g,%d,%d,%g,"
		"%g,%g,%g);", 
		TABLE_NAMES[0], 
		tick->InstrumentID, tick->ExchangeTime, tick->LocalTime, tick->LastPrice, tick->BidPrice1,
		tick->BidVolume1, tick->AskPrice1, tick->AskVolume1, tick->Volume,  tick->Turnover,
		tick->OpenInterest, tick->HighestPrice, tick->LowestPrice);
	if (!SQLite_EXEC(sql))
		return;
}

void MDSQLite::SQLite_K_Line_Insert(wdKLine &kline)
{
	if (GetTimeNum(kline.ExchangeTime) == 0)
		return;

	char sql[1024] = {0};
	sprintf_s(sql, 
		"replace into %s values("
		"'%s','%s',%g,%g,%g,"
		"%g,%d,%g,'%s');", 
		GetTableName(kline.Period).c_str(),
		kline.InstrumentID, kline.ExchangeTime, kline.OpenPrice, kline.HighestPrice, kline.LowestPrice, 
		kline.ClosePrice, kline.Volume-kline.LastVolume, kline.OpenInterest, kline.Period);
	// 成交量为累计成交量
	kline.LastVolume = kline.Volume;
	
	if (!SQLite_EXEC(sql))
		return;
}


std::string MDSQLite::GetTableName(const std::string &period)
{	
	if (period.find('s') != string::npos || period.find("tick") != string::npos)
		return TABLE_NAMES[0];
	else if (period.find('m') != string::npos)
		return TABLE_NAMES[1];
	else if (period.find('h') != string::npos)
		return TABLE_NAMES[2];
	else
		return "";
}