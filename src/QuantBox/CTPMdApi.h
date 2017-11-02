#ifndef _CTP_MD_API_
#define _CTP_MD_API_

#include <set>
#include <string>
#include <map>
#include <mutex>
#include "CTP\ThostFtdcMdApi.h"
#include "CTPCommonApi.h"
#include "defines.h"

struct wdTick;
struct wdKLine;

class CCTPMdApi : public CThostFtdcMdSpi, CCTPCommonApi
{
public:
	static CCTPMdApi *instance();

	void Connect();
	void Disconnect();
	
	// szInstrumentIDs: "IF1409,IF1410"               period: "tick,3s,6m,1h"
	void Subscribe(const char *szInstrumentIDs, const char *period = "tick");
	void Unsubscribe(const char *szInstrumentIDs = "all", const char *period = "all");
	// beginTime、endTime: "20140815 10:00:00 000"
	void SubscribeHistory(const char *beginTime, const char *endTime, const char *szInstrumentIDs, const char *period = "tick");

private:
	CCTPMdApi(void);
	virtual ~CCTPMdApi(void);
	
	//登录请求
	void ReqUserLogin();

	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason);
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID = UNIQUE_REQUEST_ID, bool bIsLast = true);
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///Tick推送
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

	bool Checking();

	//断线重连后 订阅行情
	void Subscribe(const std::set<std::string>& instrumentIDs);
	void SubscribeQuote(const std::set<std::string>& instrumentIDs);

	void SubscribeQuote(const char *szInstrumentIDs);
	void UnsubscribeQuote(const char *szInstrumentIDs);
private:
	CThostFtdcMdApi						*m_pApi;					//行情API
	
	std::set<std::string>				m_setInstrumentIDs;			//正在订阅的合约
	std::mutex							m_mutexSetInstrumentIDs;

	std::set<std::string>				m_setQuoteInstrumentIDs;	//正在订阅的询价
	std::mutex							m_mutexSetQuoteInstrumentIDs;
};

#endif