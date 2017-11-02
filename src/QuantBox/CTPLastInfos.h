#ifndef _CTP_LAST_INFOS_H_
#define _CTP_LAST_INFOS_H_

#include <mutex>
#include <condition_variable>
#include <map>
#include <list>
#include <vector>
#include <string>

#include "CTP/ThostFtdcUserApiStruct.h"

struct wdLimitPrice;
struct wdTick;
struct wdKLine;
struct wdTradingAccount;
struct wdInstrument;

///记录CTP的所有的最新行情和交易信息
class wdCTPLastInfos
{
public:
	// 面向用户===================================================================================
	static wdCTPLastInfos *instance();	

	// 获取某个合约的最新的一些Tick数据
	wdTick GetLastTick(const char *Instrument, bool isHistory = false);
	void GetLastTick(const char *Instrument, int Num, std::vector<wdTick> &vecLastTicks, bool isHistory = false);

	// 获取某个合约的某个period的最新的一些K线
	wdKLine GetLastKLine(const char *Instrument, const char *period, bool isHistory = false);
	void GetLastKLine(const char *Instrument, const char *period, int Num, std::vector<wdKLine> &vecLastKLines, bool isHistory = false);


	// 获取账号信息 （目前还是获取总账号信息）
	wdTradingAccount GetTradingAccount(const char *szAccountID);


	// 内部使用===================================================================================
	void _AddLastTick(const wdTick &tick, bool isHistory = false);
	
	void AddPeriods(const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod, bool isHistory = false);
	// 如果订阅的period全部被清掉，则返回true
	bool RemovePeriods(const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod);
	void _AddLastKLine(const wdKLine &kline, bool isHistory = false);
	void _Output_OnRtnDepthMarketData(wdTick &tick);
	std::map<std::string, wdKLine> &GetHistoryPeriod_KLine(const char *szInstrumentID) { return m_mapHistoryInstKLine[szInstrumentID]; }


	void UpdateTradingAccount(const CThostFtdcTradingAccountField *pTradingAccount);

	//bool isCZCE(const std::string &szInstrumentID); // 判断某个合约是否属于郑商所

private:
	wdCTPLastInfos(void);
	~wdCTPLastInfos(void);

	bool _ReadConfigFile();

	//////////////////////////////////////////////////////////////////////////	行情
	// 实时
	std::mutex													m_mutexLastTick;
	std::map<std::string, std::vector<wdTick> >					m_vecTicks;					// 存储当天的Tick数据，key为合约
	std::map<std::string, std::map<std::string, wdKLine> >		m_mapInstKLine;				// 订阅的的实时最新K线 key为合约   value（key为period）
	std::mutex																m_mutexKLine;
	std::map<std::string, std::map<std::string, std::vector<wdKLine> > >	m_mapInstVecKLine;//存储当天的K线

	// 历史
	std::mutex													m_mutexHistoryLastTick;
	std::map<std::string, std::vector<wdTick> >					m_vecHistoryTicks;			// 存储历史Tick数据，key为合约
	std::map<std::string, std::map<std::string, wdKLine> >		m_mapHistoryInstKLine;		// 订阅的历史最新K线
	std::mutex																m_mutexHistoryKLine;
	std::map<std::string, std::map<std::string, std::vector<wdKLine> > >	m_mapHistoryInstVecKLine;//存储当天的K线


	//////////////////////////////////////////////////////////////////////////	交易

	std::map<std::string, wdTradingAccount>						m_mapTradingAccount;		// key为资金账户

	std::vector<std::vector<std::string> >						m_vecInstrumentAssemble;	// 合约集的数组
};

#endif // _CTP_LAST_INFOS_H_