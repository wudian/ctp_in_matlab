
#include "CTPLastInfos.h"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>  
#include <boost/property_tree/xml_parser.hpp>
#include <WinSock2.h>
#include "MarketData.h"
#include "TradeData.h"
#include "Enums.h"
#include "CTPMdApi.h"
#include "toolkit.h"
#include "GlobalVars.h"
#include "mysql.h"

using namespace std;

wdCTPLastInfos *wdCTPLastInfos::instance()
{
	static wdCTPLastInfos ctpInfo;
	return &ctpInfo;
}

wdCTPLastInfos::wdCTPLastInfos(void)
{
	_ReadConfigFile();
	if (mysql_library_init(0, nullptr, nullptr))
		LOG_ERROR << "could not initialize mysql library";

	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2,2), &WSAData)) {
		LOG_ERROR << "WSAStartup失败";
	}
}


wdCTPLastInfos::~wdCTPLastInfos(void)
{
	mysql_library_end();

	WSACleanup();
}
//
//void wdCTPLastInfos::GetInstrument(std::vector<wdInstrument> &vecInsts)
//{
//	lock_guard<mutex> lock(m_mutexInstruments);
//	for_each(m_Instruments.begin(), m_Instruments.end(), 
//		[&](std::map<std::string, wdInstrument>::reference value){vecInsts.push_back(value.second);});
//}
//
//wdInstrument wdCTPLastInfos::GetInstrument(const char *InstrumentID)
//{
//	lock_guard<mutex> lock(m_mutexInstruments);
//	return m_Instruments[InstrumentID];
//}

wdTick wdCTPLastInfos::GetLastTick(const char *Instrument, bool isHistory)
{
	if (isHistory) {
		lock_guard<mutex> lock(m_mutexHistoryLastTick);
		if (m_vecHistoryTicks[Instrument].empty())
			return wdTick();
		else
			return m_vecHistoryTicks[Instrument].back();
	}
	lock_guard<mutex> lock(m_mutexLastTick);
	if (m_vecTicks[Instrument].empty())
		return wdTick();
	else
		return m_vecTicks[Instrument].back();
}

void wdCTPLastInfos::GetLastTick(const char *Instrument, int Num, std::vector<wdTick> &vecLastTicks, bool isHistory) 
{
	if (Instrument == nullptr || Num <= 0)
		return;
	if (isHistory) {
		lock_guard<mutex> lock(m_mutexHistoryLastTick);
		for (auto it = m_vecHistoryTicks[Instrument].rbegin(); it != m_vecHistoryTicks[Instrument].rend() && Num-- > 0; ++it)
			vecLastTicks.push_back(*it);
		return;
	}	
	lock_guard<mutex> lock(m_mutexLastTick);
	for (auto it = m_vecTicks[Instrument].rbegin(); it != m_vecTicks[Instrument].rend() && Num-- > 0; ++it)
		vecLastTicks.push_back(*it);
}

void wdCTPLastInfos::_AddLastTick(const wdTick &tick, bool isHistory)
{
	if (isHistory) {
		lock_guard<mutex> lock(m_mutexHistoryLastTick);
		m_vecHistoryTicks[tick.InstrumentID].push_back(tick);
		return;
	}
	lock_guard<mutex> lock(m_mutexLastTick);
	m_vecTicks[tick.InstrumentID].push_back(tick);
}

wdKLine wdCTPLastInfos::GetLastKLine(const char *szInstrumentID, const char *period, bool isHistory)
{
	if (isHistory) {
		lock_guard<mutex> lock(m_mutexHistoryKLine);
		if (m_mapHistoryInstVecKLine[szInstrumentID][period].empty())
			return wdKLine();
		else
			return m_mapHistoryInstVecKLine[szInstrumentID][period].back();
	}
	lock_guard<mutex> lock(m_mutexKLine);
	if (m_mapInstVecKLine[szInstrumentID][period].empty())
		return wdKLine();
	else
		return m_mapInstVecKLine[szInstrumentID][period].back();
}

void wdCTPLastInfos::GetLastKLine(const char *Instrument, const char *period, int Num, std::vector<wdKLine> &vecLastKLines, bool isHistory)
{
	if (Instrument == nullptr || period == nullptr || Num <= 0)
		return;
	if (isHistory) {
		lock_guard<mutex> lock(m_mutexHistoryKLine);
		for (auto it = m_mapHistoryInstVecKLine[Instrument][period].rbegin(); it != m_mapHistoryInstVecKLine[Instrument][period].rend() && Num-- > 0; ++it)
			vecLastKLines.push_back(*it);
		return;
	}
	lock_guard<mutex> lock(m_mutexKLine);
	for (auto it = m_mapInstVecKLine[Instrument][period].rbegin(); it != m_mapInstVecKLine[Instrument][period].rend() && Num-- > 0; ++it)
		vecLastKLines.push_back(*it);
}

void wdCTPLastInfos::AddPeriods(const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod, bool isHistory)
{
	if (isHistory) {
		for (const string &inst : listInstrumentIDs) {
			m_mapHistoryInstKLine.erase(inst);

			for (const string &period : listPeriod) {
				m_mapHistoryInstKLine[inst][period] = wdKLine();
			}
		}
		return;
	}

	lock_guard<mutex> lock(m_mutexKLine);
	for (const std::string &inst : listInstrumentIDs)
		for (const std::string &period : listPeriod) {
			m_mapInstKLine[inst][period] = wdKLine(inst.c_str(), period.c_str());
		}
}

bool wdCTPLastInfos::RemovePeriods(const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod)
{
	lock_guard<mutex> lock(m_mutexKLine);
	if (listPeriod.empty() || boost::iequals(listPeriod.front(), "all")) {
		for (const std::string &inst : listInstrumentIDs) {
			m_mapInstKLine.erase(inst);
		}
		return true;
	}

	for (const std::string &inst : listInstrumentIDs)
		for (const std::string &period : listPeriod) {
			m_mapInstKLine[inst].erase(period);
		}

	bool ret = false;
	for (const std::string &inst : listInstrumentIDs)
		if (m_mapInstKLine[inst].empty()) {
			m_mapInstKLine.erase(inst);
			ret = true;
		}

	return ret;
}

void wdCTPLastInfos::_AddLastKLine(const wdKLine &kline, bool isHistory)
{
	if (isHistory) {
		lock_guard<mutex> lock(m_mutexHistoryKLine);
		m_mapHistoryInstVecKLine[kline.InstrumentID][kline.Period].push_back(kline);
		return;
	}
	lock_guard<mutex> lock(m_mutexKLine);
	m_mapInstVecKLine[kline.InstrumentID][kline.Period].push_back(kline);
}

void wdCTPLastInfos::_Output_OnRtnDepthMarketData(wdTick &tick)
{
	std::map<std::string, wdKLine> &period_kline = m_mapInstKLine[tick.InstrumentID];
	// 遍历订阅了的各周期
	for (auto it = period_kline.begin(); it != period_kline.end(); ++it) {
		const std::string &period = it->first;
		if (boost::iequals(period, "tick")) {
			_AddLastTick(tick);
			if(g_fnOnRtnDepthMarketData_Tick) // 订阅了tick
				g_fnOnRtnDepthMarketData_Tick(&tick);
			continue;
		}
		wdKLine &kline = it->second;
		int nSec = GetSeconds(period);

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
				// 存起来
				_AddLastKLine(kline);
				// 调用回调deal K线
				if (g_fnOnRtnDepthMarketData_KLine)
					g_fnOnRtnDepthMarketData_KLine(&kline);
			}

			// 切换(超过时间间隔 首个数据到来)  添加新K线	
			sprintf_s(kline.InstrumentID, tick.InstrumentID);
			sprintf_s(kline.ExchangeTime, GetKLineExchangeTime(tick, nSec).c_str());
			kline.OpenPrice = tick.LastPrice;
			kline.HighestPrice = tick.LastPrice;
			kline.LowestPrice = tick.LastPrice;
			kline.ClosePrice = tick.LastPrice;
			kline.Volume = tick.Volume;
			kline.OpenInterest = tick.OpenInterest;//持仓量
			sprintf_s(kline.Period, period.c_str());
		}
	}
}

wdTradingAccount wdCTPLastInfos::GetTradingAccount(const char *szAccountID)
{
	if (szAccountID)
		return m_mapTradingAccount[szAccountID];
	else 
		return wdTradingAccount();
}

//void wdCTPLastInfos::GetOrder(std::map<wdOrderKey, wdOrder> &mapOrder)
//{
//	lock_guard<mutex> lock(m_mutexOrder);
//	for_each(m_Order.begin(), m_Order.end(), 
//		[&](std::map<wdOrderKey, wdOrder>::reference value){mapOrder[value.first] = value.second;});
//}

//void wdCTPLastInfos::GetTrashOrder(std::vector<wdOrder> &vecOrder)
//{
//	lock_guard<mutex> lock(m_mutexTrashOrder);
//	for_each(m_TrashOrder.begin(), m_TrashOrder.end(), 
//		[&](std::vector<wdOrder>::reference value){vecOrder.push_back(value);});
//}


void wdCTPLastInfos::UpdateTradingAccount(const CThostFtdcTradingAccountField *pTradingAccount)
{
	m_mapTradingAccount[pTradingAccount->AccountID].update(pTradingAccount);
}
//
//void wdCTPLastInfos::UpdateInstrument(const CThostFtdcDepthMarketDataField *pDept)
//{
//	lock_guard<mutex> lock(m_mutexInstruments);
//	m_Instruments[pDept->InstrumentID].update(pDept);
//}
//
//void wdCTPLastInfos::UpdateInstrument(const CThostFtdcInstrumentField *pInstrument)
//{
//	lock_guard<mutex> lock(m_mutexInstruments);
//	m_Instruments[pInstrument->InstrumentID].update(pInstrument);
//}
//
//void wdCTPLastInfos::UpdateInstrument(const CThostFtdcInstrumentMarginRateField *pMarginRate)
//{
//	lock_guard<mutex> lock(m_mutexInstruments);
//	m_Instruments[pMarginRate->InstrumentID].update(pMarginRate);
//}
//
//void wdCTPLastInfos::UpdateInstrument(const CThostFtdcInstrumentCommissionRateField *pCommissionRate)
//{
//	lock_guard<mutex> lock(m_mutexInstruments);
//	m_Instruments[pCommissionRate->InstrumentID].update(pCommissionRate);
//}
//
//void wdCTPLastInfos::UpdateInstrument(const CThostFtdcInstrumentStatusField *pStatus)
//{
//	lock_guard<mutex> lock(m_mutexInstruments);
//	m_Instruments[pStatus->InstrumentID].update(pStatus);
//}
//
//bool wdCTPLastInfos::isCZCE(const std::string &szInstrumentID)
//{
//	lock_guard<mutex> lock(m_mutexInstruments);
//	return boost::iequals(m_Instruments[szInstrumentID].ExchangeID, "CZCE");
//}
//
//void wdCTPLastInfos::PrepareAllInstruments()
//{
//	unique_lock<mutex> lock(m_mutex_allInstruments);
//	m_cv_allInstruments.wait_until(lock, std::chrono::system_clock::now()+std::chrono::seconds(10));
//}
//
//std::string wdCTPLastInfos::GetAllInstruments()
//{
//	if ("" != m_allInstruments)
//		return m_allInstruments;
//	PrepareAllInstruments();
//	return m_allInstruments;
//}


bool wdCTPLastInfos::_ReadConfigFile()
{
	boost::system::error_code ec;
	if (!boost::filesystem::exists("ConfigFile.xml", ec)) {
		assert(false);
		return false;
	}
	boost::filesystem::path confPath = boost::filesystem::current_path();

	g_Database = confPath.string() + "\\LocalDatabase\\";
	g_mdDBPath = g_Database + "MarketData.db";
	QUANTBOX_API extern std::string							g_tdDBPath;
	g_tdDBPath = g_Database + "TradeInfo.db";
	boost::filesystem::create_directory("LocalDatabase");
	boost::filesystem::create_directory("LocalDatabase\\MDStream");
	boost::filesystem::create_directory("LocalDatabase\\TDStream");

	using boost::property_tree::ptree;
	ptree pt;
	try {
		boost::property_tree::xml_parser::read_xml("ConfigFile.xml", pt);
	}
	catch (...) {
		assert(false);
		return false;
	}

	string tradeType = pt.get("TRADE_TYPE", "simulate");
	if (boost::iequals(tradeType, "actual"))
		g_tradeType = E_Actual;
	else 
		g_tradeType = E_Simulate;

	string lev = pt.get("SEVERITY_LEVEL", "error");
	if (boost::iequals(lev, "normal"))
		g_severityLevel = normal;
	else if (boost::iequals(lev, "warning"))
		g_severityLevel = warning;
	else if (boost::iequals(lev, "error"))
		g_severityLevel = error;
	else
		assert(false);
	initLog(confPath.string()+"\\kiiik_ctp.log", g_severityLevel);
	g_trader_no = pt.get("TRADER_NO", "00");

	g_mdAddress = pt.get("FRONT_ADDR_MD", "");
	g_mdBrokerID = pt.get("BROKER_ID_MD", "");
#ifndef MD_SERVER
	g_mdInstrumentAssemble = pt.get("INSTRUMENT_ASSEMBLE", "");
	std::list<std::string> listInstrumentAssemble;
	boost::split(listInstrumentAssemble, g_mdInstrumentAssemble, boost::is_any_of(";"));
	listInstrumentAssemble.remove_if(isStdStrNULL);
	for (const string &insts : listInstrumentAssemble) {
		std::vector<std::string> vecInstAssemble;
		boost::split(vecInstAssemble, insts, boost::is_any_of(","));
		if (vecInstAssemble.size() > 1)
			m_vecInstrumentAssemble.push_back(vecInstAssemble);
	}
#endif

	g_tdAddress = pt.get("FRONT_ADDR_TD", "");
	g_tdBrokerID = pt.get("BROKER_ID_TD", "");
	g_tdInvestorId = pt.get("INVESTOR_ID_TD", "");
	g_tdPassword = pt.get("PASSWORD_TD", "");
	g_tdUserProductInfo = pt.get("USER_PRODUCT_INFO", "");
	g_tdAuthCode = pt.get("AUTH_CODE", "");
	string resumeType = pt.get("THOST_TE_RESUME_TYPE", "THOST_TERT_QUICK");
	if (resumeType == "THOST_TERT_RESTART")
		g_resumeType = THOST_TERT_RESTART;
	else if (resumeType == "THOST_TERT_RESUME")
		g_resumeType = THOST_TERT_RESUME;

	g_mysqlHost = pt.get("MYSQL_HOST", "");
	g_mysqlUser = pt.get("MYSQL_USER", "");
	g_mysqlPassword = pt.get("MYSQL_PASSWORD", "");

	return true;
}
