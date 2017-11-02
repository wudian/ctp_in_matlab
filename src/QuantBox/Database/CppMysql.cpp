
#include "CppMysql.h"
#include <thread>
#include <boost/algorithm/string.hpp>  
#include "logger.h"
#include "Types.h"
#include "defines.h"
#include "MarketData.h"
#include "toolkit.h"
#include "CTPLastInfos.h"
#include "CTPRspMsgQueue.h"
#include "CTPRspMsg.h"
#include "CTPReqMsg.h"
#include "CTPTdApi.h"
#include "Enums.h"
#include "GlobalVars.h"

using namespace std;

static bool s_bCreateTable = true;
// MD
static const char *S_Period[3]	=	{"tick",		"1m",				"1h"};
static const char *TABLE_NAMES[3] = {"md_tick",		"md_kline_1m",		"md_kline_1h"}; 
static const char *Mysql_Tick_Table_Format =
	"create table if not exists %s("
	"InstrumentID varchar(31),	ExchangeTime varchar(25),	Local_Time varchar(25),	LastPrice double,		BidPrice1 double,"
	"BidVolume1 int,			AskPrice1 double,			AskVolume1 int,			Volume int,				Turnover double,"
	"OpenInterest double,		HighestPrice double,		LowestPrice double,		primary key(InstrumentID, ExchangeTime));"; 

static const char *Mysql_Kline_Table_Format =
	"create table if not exists %s("
	"InstrumentID varchar(31),	ExchangeTime varchar(25),	OpenPrice double,		HighPrice double,		LowPrice double,"
	"ClosePrice double,			Volume int,					OpenInterest double,	Period varchar(5),"
	"primary key(InstrumentID, ExchangeTime, Period));";

// TD
//static const char *Table_TradingAccount = //资金账户
//	"create table if not exists td_trading_account("
//	"BrokerID varchar(11),	AccountID varchar(13),	Deposit double,		Withdraw double,		FrozenMargin double,	FrozenCash double,"
//	"CurrMargin double,		Commission double,		CloseProfit double,	PositionProfit double,	Available double,		WithdrawQuota double,"
//	"Reserve double,		TradingDay varchar(9),	primary key(BrokerID, AccountID));";
//static const char *Table_InvestorPosition = // 持仓
//	"create table if not exists td_investor_position("
//	"InstrumentID varchar(31),	BrokerID varchar(11),	InvestorID varchar(13),		PosiDirection char(1),	HedgeFlag char(1),"
//	"PositionDate char(1),		YdPosition int,			Position int,				LongFrozen int,			ShortFrozen int,"
//	"PositionCost double,		TradingDay varchar(9),	TodayPosition int,			primary key(InstrumentID, PosiDirection, PositionDate));";
//static const char *TablE_AvailableOrdersOrder = // 可撤报单
//	"create table if not exists td_available_order("
//	"BrokerID varchar(11),		InvestorID varchar(13),		InstrumentID varchar(31),	OrderRef varchar(13),		Direction char(1),"
//	"CombOffsetFlag varchar(5),	ExchangeID varchar(9),		OrderSysID varchar(21),		FrontID int,				SessionID int,"
//	"primary key(ExchangeID, OrderSysID));";
//static const char *Table_Order =	// 报单
//	"create table if not exists td_order("
//	"BrokerID varchar(11),		InvestorID varchar(13),		InstrumentID varchar(31),	OrderRef varchar(13),		UserID varchar(16),"
//	"Direction char(1),			CombOffsetFlag varchar(5),	CombHedgeFlag varchar(5),	LimitPrice double,			VolumeTotalOriginal int,"
//	"TimeCondition char(1),		GTDDate varchar(9),			VolumeCondition char(1),	MinVolume int,				ContingentCondition char(1),"
//	"StopPrice double,			ForceCloseReason char(1),	OrderLocalID varchar(13),	ExchangeID varchar(9),		ExchangeInstID varchar(31),"
//	"TraderID varchar(21),		OrderSubmitStatus char(1),	NotifySequence int,			TradingDay varchar(9),		SettlementID int,"
//	"OrderSysID varchar(21),	OrderStatus char(1),		InsertDate varchar(9),		InsertTime varchar(9),		ActiveTime varchar(9),"
//	"SuspendTime varchar(9),	UpdateTime varchar(9),		CancelTime varchar(9),		SequenceNo int,				FrontID int,"
//	"SessionID int,				StatusMsg varchar(81),		BrokerOrderSeq int,			primary key(ExchangeID, OrderSysID));";
//static const char *Table_Trade = // 成交
//	"create table if not exists td_trade("
//	"BrokerID varchar(11),		InvestorID varchar(13),		InstrumentID varchar(31),	OrderRef varchar(13),		UserID varchar(16),"
//	"ExchangeID varchar(9),		TradeID varchar(21),		Direction char(1),			OrderSysID varchar(21),		ParticipantID varchar(11),"
//	"ClientID varchar(11),		ExchangeInstID varchar(31), OffsetFlag char(1),			HedgeFlag char(1),			Price double,"
//	"Volume int,				TradeDate varchar(9),		TradeTime varchar(9),		TraderID varchar(21),		SequenceNo int,"
//	"TradingDay varchar(9),		primary key(ExchangeID, TraderID));";
//
//static const char *Sql_Clear_Tables =
//	"delete from td_trading_account;"
//	"delete from td_investor_position;"
//	"delete from td_instrument;"
//	"delete from td_available_order;"
//	"delete from td_order;"
//	"delete from td_trade;";

CppMysql::CppMysql(void) : m_pSql(nullptr)
{
}


CppMysql::~CppMysql(void)
{
}

bool CppMysql::Mysql_Init()
{
	if (m_pSql)
		return true;
	m_pSql = mysql_init(0);
	static bool	s_bReconnect = true;	
	if (mysql_options(m_pSql, MYSQL_OPT_RECONNECT, &s_bReconnect))
		LOG_WARNING << "设置mysql的option失败";
	if (nullptr == mysql_real_connect(m_pSql, g_mysqlHost.c_str(), g_mysqlUser.c_str(), g_mysqlPassword.c_str(), MYSQL_DB_NAME, MYSQL_PORT, nullptr, CLIENT_MULTI_STATEMENTS)) {
		LOG_ERROR << mysql_error(m_pSql);
		return false;
	}
	
	/*static std::once_flag oc;
	std::call_once(oc, &CppMysql::_Mysql_Create_Tables, this);*/
	if (!_Mysql_Create_Tables())
		return false;
	return true;
}

void CppMysql::Mysql_Finalize()
{
	mysql_close(m_pSql);
}

void CppMysql::Mysql_MarketData_Insert(const wdTick &tick)
{
	//记录各个合约的1m和1h的最新K线
	static std::map<std::string, std::map<std::string, wdKLine> > s_mapInstKLine;
	for (int i = 0; i < 3; ++i) {
		if (0 == i) {
			_Mysql_Tick_Insert(tick);
			continue;
		}
		int nSec = GetSeconds(S_Period[i]);
		wdKLine &kline = s_mapInstKLine[tick.InstrumentID][S_Period[i]];
		if (GetTimeNum(tick.ExchangeTime) - GetTimeNum(kline.ExchangeTime) < nSec) {	// 判断是否切换
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
			if (GetTimeNum(kline.ExchangeTime) == 0) { // tick first coming
				kline.LastVolume = tick.Volume;
				kline.LastOpenInterest = tick.OpenInterest;
			}
			else { // 切换(超过时间间隔) 保存K线数据
				// 赋值为上一个k线的最后一个tick的值
				int tempVolume = kline.Volume;
				double tempOpenInterest = kline.OpenInterest;
				kline.Volume -= kline.LastVolume;
				kline.OpenInterest -= kline.LastOpenInterest;
				kline.LastVolume = tempVolume;
				kline.LastOpenInterest = tempOpenInterest;						
				_Mysql_KLine_Insert(kline);
			}

			// 切换(超过时间间隔 首个数据到来)  添加新K线	
			sprintf_s(kline.InstrumentID, tick.InstrumentID);
			sprintf_s(kline.ExchangeTime, GetKLineExchangeTime(tick, nSec).c_str());
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

void CppMysql::SubscribeHistory(const char *beginTime, const char *endTime, const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod)
{
	// 记录已经订阅了的某个周期的K线
	static std::map<std::string, std::map<std::string, bool> >	s_mapHasSubscribe;

	wdCTPLastInfos::instance()->AddPeriods(listInstrumentIDs, listPeriod, true);

	char sql[1024] = {0};
	for (const string &inst : listInstrumentIDs) {
		s_mapHasSubscribe[inst][S_Period[0]] = false;
		s_mapHasSubscribe[inst][S_Period[1]] = false;
		s_mapHasSubscribe[inst][S_Period[2]] = false;

		for (const string &period : listPeriod) {
			if (period.find('s') != string::npos || period.find("tick") != string::npos) {
				if (s_mapHasSubscribe[inst][S_Period[0]])
					continue;
				else 
					s_mapHasSubscribe[inst][S_Period[0]] = true;
			}
			else if (period.find('m') != string::npos) {
				if (s_mapHasSubscribe[inst][S_Period[1]])
					continue;
				else 
					s_mapHasSubscribe[inst][S_Period[1]] = true;
			}

			else if (period.find('h') != string::npos) {
				if (s_mapHasSubscribe[inst][S_Period[2]])
					continue;
				else 
					s_mapHasSubscribe[inst][S_Period[2]] = true;
			}				
			else {
				LOG_ERROR << "暂不支持这个period: " << period;
				continue;
			}

			memset(sql, 0, sizeof(sql));
			sprintf_s(sql, "select * from %s where InstrumentID='%s' and ExchangeTime between '%s' and '%s';", _GetTableName(period).c_str(), inst.c_str(), beginTime, endTime);
			if (!_Mysql_EXEC(sql, E_HISTORY_MD))
				return;
		}
	}
}

bool CppMysql::Mysql_Insert_TradingAccount(const CThostFtdcTradingAccountField &pTradingAccount)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into td_trading_account values("
		"'%s',	'%s',	%g,		%g,		%g,"
		"%g,	%g,		%g,		%g,		%g,"
		"%g,	%g,		%g,		'%s'	);",
		pTradingAccount.BrokerID, pTradingAccount.AccountID, pTradingAccount.Deposit, pTradingAccount.Withdraw,	pTradingAccount.FrozenMargin, 
		pTradingAccount.FrozenCash, pTradingAccount.CurrMargin, pTradingAccount.Commission,	pTradingAccount.CloseProfit, pTradingAccount.PositionProfit,
		pTradingAccount.Available, pTradingAccount.WithdrawQuota, pTradingAccount.Reserve, pTradingAccount.TradingDay);

	if (!_Mysql_EXEC(sql))
		return false;
	return true;
}

bool CppMysql::Mysql_Insert_InvestorPosition(const CThostFtdcInvestorPositionField &pInvestorPosition)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into td_investor_position values("
		"'%s','%s','%s','%c','%c',"
		"'%c',%d,%d,%d,%d,"
		"%g,'%s',%d);",
		pInvestorPosition.InstrumentID, pInvestorPosition.BrokerID, pInvestorPosition.InvestorID, pInvestorPosition.PosiDirection,pInvestorPosition.HedgeFlag,
		pInvestorPosition.PositionDate, pInvestorPosition.YdPosition, pInvestorPosition. Position,pInvestorPosition.LongFrozen, pInvestorPosition.ShortFrozen,
		pInvestorPosition.PositionCost, pInvestorPosition.TradingDay,	pInvestorPosition.TodayPosition);

	if (!_Mysql_EXEC(sql))
		return false;
	return true;
}

bool CppMysql::Mysql_Insert_Instrument(const CThostFtdcInstrumentField &pInstrument)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into td_instrument values('%s','%s','%s','%s','%c',%g,%g);",
		pInstrument.InstrumentID, pInstrument.ExchangeID, pInstrument.InstrumentName, pInstrument.ExchangeInstID,
		pInstrument.InstLifePhase, pInstrument.LongMarginRatio, pInstrument.ShortMarginRatio);

	if (!_Mysql_EXEC(sql))
		return false;
	return true;
}

bool CppMysql::Mysql_Insert_Order(const CThostFtdcOrderField &pOrder)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into td_order values("
		"'%s','%s','%s','%s','%s',"
		"'%c','%s','%s',%g,%d,"
		"'%c','%s','%c',%d,'%c',"
		"%g,'%c','%s','%s','%s',"
		"'%s','%c',%d,'%s',%d,"
		"'%s','%c','%s','%s','%s',"
		"'%s','%s','%s',%d,%d,"
		"%d,'%s',%d);",
		pOrder.BrokerID, pOrder.InvestorID, pOrder.InstrumentID, pOrder.OrderRef, pOrder.UserID, 
		pOrder.Direction, pOrder.CombOffsetFlag, pOrder.CombHedgeFlag, pOrder.LimitPrice, pOrder.VolumeTotalOriginal, 
		pOrder.TimeCondition, pOrder.GTDDate, pOrder.VolumeCondition, pOrder.MinVolume, pOrder.ContingentCondition,
		pOrder.StopPrice, pOrder.ForceCloseReason, pOrder.OrderLocalID, pOrder.ExchangeID, pOrder.ExchangeInstID, 
		pOrder.TraderID, pOrder.OrderSubmitStatus, pOrder.NotifySequence, pOrder.TradingDay, pOrder.SettlementID,
		pOrder.OrderSysID, pOrder.OrderStatus, pOrder.InsertDate, pOrder.InsertTime, pOrder.ActiveTime, 
		pOrder.SuspendTime,	pOrder.UpdateTime, pOrder.CancelTime, pOrder.SequenceNo, pOrder.FrontID, 
		pOrder.SessionID, pOrder.StatusMsg, pOrder.BrokerOrderSeq);

	if (!_Mysql_EXEC(sql))
		return false;
	return true;
}

bool CppMysql::Mysql_Insert_Trade(const CThostFtdcTradeField &pTrade)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into td_trade values("
		"'%s','%s','%s','%s','%s',"
		"'%s','%s','%c','%s','%s',"
		"'%s','%s','%c','%c',%g,"
		"%d,'%s','%s','%s',%d,"
		"'%s');",
		pTrade.BrokerID, pTrade.InvestorID,pTrade.InstrumentID,pTrade.OrderRef,pTrade.UserID,
		pTrade.ExchangeID,pTrade.TradeID,pTrade.Direction,pTrade.OrderSysID,pTrade.ParticipantID,
		pTrade.ClientID,pTrade.ExchangeInstID,pTrade.OffsetFlag,pTrade.HedgeFlag,pTrade.Price,
		pTrade.Volume, pTrade.TradeDate,pTrade.TradeTime,pTrade.TraderID,pTrade.SequenceNo, 
		pTrade.TradingDay);

	if (!_Mysql_EXEC(sql))
		return false;
	return true;
}

bool CppMysql::Mysql_Insert_AvailableOrder(const CThostFtdcOrderField &pAvailableOrder)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into td_available_order values("
		"'%s','%s','%s','%s', '%c',"
		"'%s','%s','%s',%d,  %d);",
		pAvailableOrder.BrokerID, pAvailableOrder.InvestorID, pAvailableOrder.InstrumentID, pAvailableOrder.OrderRef, pAvailableOrder.Direction,
		pAvailableOrder.CombOffsetFlag, pAvailableOrder.ExchangeID,pAvailableOrder.OrderSysID, pAvailableOrder.FrontID, pAvailableOrder.SessionID);

	if (!_Mysql_EXEC(sql))
		return false;
	return true;
}

bool CppMysql::Mysql_DeletE_AvailableOrdersOrder(const CThostFtdcOrderField &pAvailableOrder)
{
	char sql[1024] = {0};
	sprintf_s(sql, "delete from td_available_order where OrderSysID = '%s' and ExchangeID = '%s';", pAvailableOrder.OrderSysID, pAvailableOrder.ExchangeID);

	if (!_Mysql_EXEC(sql))
		return false;
	return true;
}

bool CppMysql::Mysql_DeletE_AvailableOrdersOrder(const CThostFtdcTradeField &pTrade)
{
	char sql[1024] = {0};
	sprintf_s(sql, "delete from td_available_order where OrderSysID = '%s' and ExchangeID = '%s';", pTrade.OrderSysID, pTrade.ExchangeID);

	if (!_Mysql_EXEC(sql))
		return false;
	return true;
}

bool CppMysql::CancelOrder(const char *Instrument, TThostFtdcDirectionType Direction, const TThostFtdcCombOffsetFlagType CombOffsetFlag)
{
	char sql[1024] = {0};
	char inst[64] = {0}; 
	char direct[64] = {0};
	char offset[64] = {0};
	if (!isStrNULL(Instrument))
		sprintf_s(inst, "t.InstrumentID = '%s' and", Instrument);
	if (Direction != 0)
		sprintf_s(direct, "t.Direction = '%c' and", Direction);
	if (!isStrNULL(CombOffsetFlag))
		sprintf_s(offset, "t.CombOffsetFlag = '%s' and", CombOffsetFlag);

	sprintf_s(sql, "select * from td_available_order t where %s %s %s;", inst, direct, offset);

	std::string temp = sql;
	size_t iter = temp.rfind("and");
	if (iter == std::string::npos) {
		boost::algorithm::erase_first(temp, "where");
	}
	else {
		boost::algorithm::erase_last(temp, "and");
	}

	if (!_Mysql_EXEC(temp.c_str(), E_CANCEL_ORDER))
		return false;
	
	return true;
}

bool CppMysql::_Mysql_CancelOrder_Handler(MYSQL_RES *result)
{
	/*MYSQL_ROW row; 
	while (row = mysql_fetch_row(result)) {
		std::shared_ptr<CCTPReqMsgItem> pRequest(CCTPReqMsgItem(E_InputOrderActionField).MakeCThostFtdcInputOrderActionField(
			row[0], row[1], row[3], atoi(row[8]), atoi(row[9]), row[6], row[7], THOST_FTDC_AF_Delete, row[2]));
		if (CCTPTdApi::instance()->_ReqOrderAction(*pRequest))
			return false;
	}*/
	return true;
}

void CppMysql::_Mysql_Tick_Insert(const wdTick &tick)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into %s values("
		"'%s','%s','%s',%g,%g,"
		"%d,%g,%d,%d,%g,"
		"%g,%g,%g);", 
		TABLE_NAMES[0], 
		tick.InstrumentID, tick.ExchangeTime, tick.LocalTime, tick.LastPrice, tick.BidPrice1,
		tick.BidVolume1, tick.AskPrice1, tick.AskVolume1, tick.Volume,  tick.Turnover,
		tick.OpenInterest, tick.HighestPrice, tick.LowestPrice);
	if (!_Mysql_EXEC(sql))
		return;
}

void CppMysql::_Mysql_KLine_Insert(wdKLine &kline)
{
	char sql[1024] = {0};
	sprintf_s(sql, 
		"replace into %s values("
		"'%s','%s',%g,%g,%g,"
		"%g,%d,%g,'%s');", 
		_GetTableName(kline.Period).c_str(),
		kline.InstrumentID, kline.ExchangeTime, kline.OpenPrice, kline.HighestPrice, kline.LowestPrice, 
		kline.ClosePrice, kline.Volume, kline.OpenInterest, kline.Period);
	if (!_Mysql_EXEC(sql))
		return;
}

bool CppMysql::_Mysql_Create_Tables()
{
	// 只执行一遍
	if (!s_bCreateTable)
		return true;
	s_bCreateTable = false;
	// MD
	char sql[1024] = {0};
	for (int i = 0; i < 3; ++i) {
		if (0 == i) {
			sprintf_s(sql, Mysql_Tick_Table_Format, TABLE_NAMES[i]);
		}
		else {
			memset((void*)sql, 0, sizeof(sql));
			sprintf_s(sql, Mysql_Kline_Table_Format, TABLE_NAMES[i]);
		}
		if (!_Mysql_EXEC(sql))
			return false;
	}	
	// TD
	/*char sql2[10240] = {0};
	sprintf_s(sql2, "%s%s%s%s%s%s", Table_TradingAccount, Table_InvestorPosition, TablE_AvailableOrdersOrder, Table_Order, Table_Trade, Sql_Clear_Tables);
	if (!_Mysql_EXEC(sql2))
		return false;*/
	return true;
}

bool CppMysql::_Mysql_EXEC(const char *sql, SQL_TYPE t)
{
	if (mysql_query(m_pSql, sql)) {
		LOG_ERROR << "sql语句(" << sql << ")\n errMsg(" << mysql_error(m_pSql) << ")";
		std::cout << std::this_thread::get_id() <<mysql_error(m_pSql) <<mysql_thread_id(m_pSql)<< "\n";
		return false;
	}

	int status = 0;
	/* process each statement result */
	do {
		/* did current statement return data? */
		MYSQL_RES *result = mysql_store_result(m_pSql);
		if (result)
		{
			/* yes; process rows and free the result set */
			if (t == E_HISTORY_MD && !_Mysql_HistoryMd_Handler(result)) 
				return false;
			else if (t == E_CANCEL_ORDER && !_Mysql_CancelOrder_Handler(result))
				return false;
			mysql_free_result(result);
		}
		else /* no result set or error */
		{
			if (mysql_field_count(m_pSql) == 0)
			{
				LOG_NORMAL << mysql_affected_rows(m_pSql) << " rows affected";
			}
			else /* some error occurred */
			{
				LOG_ERROR << "Could not retrieve result set";
				return false;
			}
		}
		/* more results? -1 = no, >0 = error, 0 = yes (keep looping) */
		if ((status = mysql_next_result(m_pSql)) > 0)
			LOG_ERROR << "Could not execute statement";
	} while (status == 0);

	return true;
}

bool CppMysql::_Mysql_HistoryMd_Handler(MYSQL_RES *result)
{
	// 历史数据的缓存队列
	static CCTPRspMsgQueue s_msgQueue(E_HistoryMarketData);
	MYSQL_ROW row; 

	while (row = mysql_fetch_row(result)) {
		map<string, wdKLine> &period_kline = wdCTPLastInfos::instance()->GetHistoryPeriod_KLine(row[0]);
		for (auto it = period_kline.begin(); it != period_kline.end(); ++it) {
			const string &period = it->first;
			wdKLine &kline = it->second;
			int nSec = GetSeconds(period);
			int num_fields = mysql_num_fields(result);
			if (num_fields == 13) { // tick过来
				if (boost::iequals(period, "tick")) { // 订阅的是tick										
					s_msgQueue.InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnTick, 
						&wdTick(row[0], row[1], row[2], atof(row[3]), atof(row[4]), atoi(row[5]),
						atof(row[6]), atoi(row[7]), atoi(row[8]), atof(row[9]), atof(row[10]), atof(row[11]), atof(row[12]))));
					continue;
				}
				else if (period.find('s') != string::npos || period.find('S') != string::npos) { // 订阅的是秒数据。由tick拼凑秒K线
					if (GetTimeNum(row[1]) - GetTimeNum(kline.ExchangeTime) < nSec) {	// 判断是否切换
						// 不切换 更新K线
						kline.OpenInterest = atof(row[10]);//持仓量
						kline.Volume = atoi(row[8]);//累计成交量
						kline.ClosePrice = atof(row[3]);
						if (kline.HighestPrice < atof(row[3]))
							kline.HighestPrice = atof(row[3]);
						if (kline.LowestPrice > atof(row[3]))
							kline.LowestPrice = atof(row[3]);
					}
					else {
						if (GetTimeNum(kline.ExchangeTime) == 0) { // tick first coming
							kline.LastVolume = atoi(row[8]);
							kline.LastOpenInterest = atof(row[10]);
						}	
						else { // 切换(超过时间间隔) 保存K线数据
							int tempVolume = kline.Volume;
							double tempOpenInterest = kline.OpenInterest;
							kline.Volume -= kline.LastVolume;
							kline.OpenInterest -= kline.LastOpenInterest;
							kline.LastVolume = tempVolume;
							kline.LastOpenInterest = tempOpenInterest;
							s_msgQueue.InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnKLine, &kline));
						}

						// 切换(超过时间间隔 首个数据到来)  添加新K线	
						sprintf_s(kline.InstrumentID, row[0]);
						sprintf_s(kline.ExchangeTime, row[1]);
						kline.OpenPrice = atof(row[3]);
						kline.HighestPrice = atof(row[3]);
						kline.LowestPrice = atof(row[3]);
						kline.ClosePrice = atof(row[3]);
						kline.Volume = atoi(row[8]);
						kline.OpenInterest = atof(row[10]);//持仓量
						sprintf_s(kline.Period, period.c_str());
					}
				}
			}
			else if (num_fields == 9) { // K线过来 1m或1h
				// 由1m线拼凑成任意分钟的K线；  由1h线拼凑成任意h的K线
				if (GetTimeNum(row[1]) - GetTimeNum(kline.ExchangeTime) < nSec) {	// 判断是否切换
					// 不切换 更新K线
					kline.OpenInterest += atof(row[7]);//累计持仓量
					kline.Volume += atoi(row[6]);//累计成交量
					kline.ClosePrice = atof(row[5]);
					if (kline.HighestPrice < atof(row[3]))
						kline.HighestPrice = atof(row[3]);
					if (kline.LowestPrice > atof(row[4]))
						kline.LowestPrice = atof(row[4]);
				}
				else { // 切换(超过时间间隔 首个数据到来)  添加新K线	
					if (GetTimeNum(kline.ExchangeTime) > 0) { 
						s_msgQueue.InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnKLine, &kline));
					}
					
					sprintf_s(kline.InstrumentID, row[0]);
					sprintf_s(kline.ExchangeTime, row[1]);
					kline.OpenPrice = atof(row[2]);
					kline.HighestPrice = atof(row[3]);
					kline.LowestPrice = atof(row[4]);
					kline.ClosePrice = atof(row[5]);
					kline.Volume = atoi(row[6]);//成交量
					kline.OpenInterest = atof(row[7]);//持仓量
					sprintf_s(kline.Period, period.c_str());
				}				
			}
			else {
				return false;	
			}
		}
	}	
	return true;
}

std::string CppMysql::_GetTableName(const std::string &period)
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
