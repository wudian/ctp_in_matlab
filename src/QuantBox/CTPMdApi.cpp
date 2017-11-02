
#include "CTPMdApi.h"
#include <stdio.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <string>
#include <boost/scoped_array.hpp>
#include <boost/format.hpp>     
#include <boost/tokenizer.hpp>     
#include <boost/algorithm/string.hpp>  
#include "CTP/ThostFtdcUserApiDataType.h"
#include "logger.h"
#include "toolkit.h"
#include "MarketData.h"
#include "TradeData.h"
#include "CTPLastInfos.h"
#include "CTPRspMsg.h"
#include "CTPRspMsgQueue.h"
#include "CTPRspMsgQueue.h"
#include "defines.h"
#include "Enums.h"
#include "CppMysql.h"
#include "GlobalVars.h"
#include "CTPTdApi.h"

using namespace std;

CCTPMdApi *CCTPMdApi::instance()
{
	static CCTPMdApi s_mdApi;
	return &s_mdApi;
}

CCTPMdApi::CCTPMdApi(void)
	: CCTPCommonApi()
	, m_pApi(nullptr)
{
	m_msgQueue = std::make_shared<CCTPRspMsgQueue>(E_RealtimeMarketData);
}

CCTPMdApi::~CCTPMdApi(void)
{
	//Disconnect();
}

void CCTPMdApi::Connect()
{
	if (m_status != E_logined && m_status != E_uninit)
	{
		LOG_NORMAL << "正在连接CTP行情前置";
		return;
	}
	else if (m_status == E_logined)
	{
		Disconnect();
		LOG_NORMAL << "断开CTP行情前置并重连";
	}

	m_pApi = CThostFtdcMdApi::CreateFtdcMdApi((g_Database+"MDStream\\").c_str(), (g_mdAddress.find("udp://") != g_mdAddress.npos));

	m_status = E_inited;
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_MD, E_inited)));

	if (m_pApi)
	{
		m_pApi->RegisterSpi(this);
		m_pApi->RegisterFront((char*)g_mdAddress.c_str());
		LOG_NORMAL << "--->>>请求连接CTP行情服务器 " << g_mdAddress;

		//初始化连接
		m_pApi->Init();
		m_status = E_connecting;
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_MD, m_status)));
	}
}

void CCTPMdApi::ReqUserLogin()
{	
	if (NULL == m_pApi)
		return;

	CThostFtdcReqUserLoginField request = {0};	
	strncpy(request.BrokerID, g_mdBrokerID.c_str(), sizeof(TThostFtdcBrokerIDType));
	
	int res = m_pApi->ReqUserLogin(&request, ++m_nRequestID);
	LOG_NORMAL << "--->>>请求登陆CTP行情服务器 " << res == 0 ? "成功" : "失败";
	
	m_status = E_logining;
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_MD, m_status)));
}

void CCTPMdApi::Disconnect()
{
	m_nRequestID = 0;
	m_status = E_unconnected;	
	//m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, m_status));
	if(m_pApi)
	{
		m_pApi->RegisterSpi(NULL);
		m_pApi->Release();
		m_pApi = NULL;				
	}
}

void CCTPMdApi::Subscribe(const char *szInstrumentIDs, const char *period)
{
	if (!Checking())
		return;
	string InstrumentIDs(szInstrumentIDs);
	if (boost::iequals(szInstrumentIDs, "all")) {
		InstrumentIDs = CCTPTdApi::instance()->GetAllInstruments();
	}
	std::list<std::string> listInstrumentIDs, listPeriod;
	boost::split(listInstrumentIDs, InstrumentIDs, boost::is_any_of(QUANTBOX_SEPS));
	boost::split(listPeriod, period, boost::is_any_of(QUANTBOX_SEPS));
	listInstrumentIDs.remove_if(isStdStrNULL);
	listPeriod.remove_if(isStdStrNULL);

	size_t num = listInstrumentIDs.size();
	if (listPeriod.empty() || num == 0)
		return;

	wdCTPLastInfos::instance()->AddPeriods(listInstrumentIDs, listPeriod);

	boost::scoped_array<char *> pArray(new char *[num]);
	int i = 0;
	for (string &value : listInstrumentIDs) {
		pArray[i++] = (char*)value.c_str();
	}
	//订阅
	m_pApi->SubscribeMarketData(pArray.get(), num);
	LOG_NORMAL << "订阅" << szInstrumentIDs << "的" << period << "行情";
}

void CCTPMdApi::Unsubscribe(const char *szInstrumentIDs, const char *period)
{
	if (!Checking())
		return;
	string InstrumentIDs(szInstrumentIDs);
	if (boost::iequals(szInstrumentIDs, "all")) {
		InstrumentIDs = CCTPTdApi::instance()->GetAllInstruments();
	}
	std::list<std::string> listInstrumentIDs, listPeriod;
	boost::split(listInstrumentIDs, InstrumentIDs, boost::is_any_of(QUANTBOX_SEPS));
	boost::split(listPeriod, period, boost::is_any_of(QUANTBOX_SEPS));
	listInstrumentIDs.remove_if(isStdStrNULL);
	listPeriod.remove_if(isStdStrNULL);
	
	size_t num = listInstrumentIDs.size();
	if (num == 0)
		return;

	if (wdCTPLastInfos::instance()->RemovePeriods(listInstrumentIDs, listPeriod))
		return;

	boost::scoped_array<char *> pArray(new char *[num]);
	int i = 0;
	for (string &value : listInstrumentIDs) {
		pArray[i++] = (char*)value.c_str();
	}
	
	m_pApi->UnSubscribeMarketData(pArray.get(), num);
}

// 用于断线重连
void CCTPMdApi::Subscribe(const set<string>& instrumentIDs)
{
	if(NULL == m_pApi)
		return;

	boost::scoped_array<char *> pArray(new char *[instrumentIDs.size()]);
	int i = 0;
	for (const string &value : instrumentIDs) {
		pArray[i++] = (char*)value.c_str();
	}
	//订阅
	m_pApi->SubscribeMarketData(pArray.get(), instrumentIDs.size());
	LOG_NORMAL << "断线重连";
}

void CCTPMdApi::SubscribeHistory(const char *beginTime, const char *endTime, const char *szInstrumentIDs, const char *period)
{	
	if (nullptr == m_pApi)
		return;
	if (m_pApi==nullptr || isStrNULL(szInstrumentIDs)||isStrNULL(period)||isStrNULL(beginTime)||isStrNULL(endTime))
		return;
	std::list<std::string> listInstrumentIDs, listPeriod;
	string InstrumentIDs(szInstrumentIDs);
	if (boost::iequals(szInstrumentIDs, "all")) {
		InstrumentIDs = CCTPTdApi::instance()->GetAllInstruments();
	}
	boost::split(listInstrumentIDs, InstrumentIDs, boost::is_any_of(QUANTBOX_SEPS));
	boost::split(listPeriod, period, boost::is_any_of(QUANTBOX_SEPS));
	listInstrumentIDs.remove_if(isStdStrNULL);
	listPeriod.remove_if(isStdStrNULL);

	if (listPeriod.empty() || listInstrumentIDs.empty())
		return;

	m_pMysql->SubscribeHistory(beginTime, endTime, listInstrumentIDs, listPeriod);
}

void CCTPMdApi::SubscribeQuote(const char *szInstrumentIDs)
{	
	if(!Checking())
		return;

	vector<char*> vct;

	size_t len = strlen(szInstrumentIDs)+1;
	boost::scoped_array<char> buf(new char[len]);
	strncpy(buf.get() ,szInstrumentIDs, len);

	lock_guard<mutex> cl(m_mutexSetQuoteInstrumentIDs);

	char* token = strtok(buf.get(), QUANTBOX_SEPS);
	while (token)
	{
		size_t l = strlen(token);
		if (l>0)
		{
			//合约已经存在，不用再订阅，但多次订阅也没关系
			m_setQuoteInstrumentIDs.insert(token);//记录此合约进行订阅
			vct.push_back(token);
		}
		token = strtok(NULL, QUANTBOX_SEPS);
	}

	if (vct.size()>0)
	{
		//转成字符串数组
		char** pArray = new char*[vct.size()];
		for (size_t j = 0; j<vct.size(); ++j)
		{
			pArray[j] = vct[j];
		}

		//订阅
		m_pApi->SubscribeForQuoteRsp(pArray, (int)vct.size());

		delete[] pArray;
	}
}

void CCTPMdApi::SubscribeQuote(const set<string>& instrumentIDs)
{
	if (NULL == m_pApi)
		return;

	string szInstrumentIDs;
	for (set<string>::iterator i = instrumentIDs.begin(); i != instrumentIDs.end(); ++i)
	{
		szInstrumentIDs.append(*i);
		szInstrumentIDs.append(";");
	}

	if (szInstrumentIDs.length()>1)
	{
		SubscribeQuote(szInstrumentIDs.c_str());
	}
}

void CCTPMdApi::UnsubscribeQuote(const char *szInstrumentIDs)
{
	
	if(!Checking())
		return;

	vector<char*> vct;
	
	size_t len = strlen(szInstrumentIDs)+1;
	boost::scoped_array<char> buf(new char[len]);
	strncpy(buf.get() ,szInstrumentIDs, len);

	lock_guard<mutex> cl(m_mutexSetQuoteInstrumentIDs);

	char* token = strtok(buf.get(), QUANTBOX_SEPS);
	while (token)
	{
		size_t l = strlen(token);
		if (l>0)
		{
			//合约已经不存在，不用再取消订阅，但多次取消也没什么关系
			m_setQuoteInstrumentIDs.erase(token);
			vct.push_back(token);
		}
		token = strtok(NULL, QUANTBOX_SEPS);
	}

	if (vct.size()>0)
	{
		//转成字符串数组
		char** pArray = new char*[vct.size()];
		for (size_t j = 0; j<vct.size(); ++j)
		{
			pArray[j] = vct[j];
		}

		//订阅
		m_pApi->UnSubscribeForQuoteRsp(pArray, (int)vct.size());

		delete[] pArray;
	}
}

void CCTPMdApi::OnFrontConnected()
{
	LOG_NORMAL << "<<<---成功连接CTP行情服务器";
	m_status =  E_connected;
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_MD, m_status)));

	//连接成功后自动请求登录
	ReqUserLogin();
}

void CCTPMdApi::OnFrontDisconnected(int nReason)
{	
	m_status = E_unconnected;
	CThostFtdcRspInfoField RspInfo;
	RspInfo.ErrorID = nReason;
	GetOnFrontDisconnectedMsg(&RspInfo);
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_MD, m_status, nullptr, RspInfo.ErrorMsg)));
}

void CCTPMdApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (!IsErrorRspInfo(pRspInfo, nRequestID, bIsLast) && pRspUserLogin)
	{
		LOG_NORMAL << "<<<---登陆CTP行情服务器成功";
		m_status = E_logined;		
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_MD, m_status, pRspUserLogin)));	
		
		m_cvStatus.notify_one();

		//有可能断线了，本处是断线重连后重新订阅
		Subscribe(m_setInstrumentIDs);
		if (m_setInstrumentIDs.empty())
			CCTPTdApi::instance()->GetAllInstruments();
	}
	else
	{
		m_status = E_connected;
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_MD, m_status, nullptr, pRspInfo->ErrorMsg)));
	}
}

void CCTPMdApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	//在模拟平台可能这个函数不会触发，所以要自己维护一张已经订阅的合约列表
	if(!IsErrorRspInfo(pRspInfo,nRequestID,bIsLast)
		&&pSpecificInstrument)
	{
		lock_guard<mutex> cl(m_mutexSetInstrumentIDs);

		m_setInstrumentIDs.insert(pSpecificInstrument->InstrumentID);
	}
}

void CCTPMdApi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//模拟平台可能这个函数不会触发
	if(!IsErrorRspInfo(pRspInfo,nRequestID,bIsLast)
		&&pSpecificInstrument)
	{
		lock_guard<mutex> cl(m_mutexSetInstrumentIDs);

		m_setInstrumentIDs.erase(pSpecificInstrument->InstrumentID);
	}
}

//行情回调，得保证此函数尽快返回
void CCTPMdApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	if (pDepthMarketData && pDepthMarketData->LastPrice < pDepthMarketData->UpperLimitPrice) {

		wdTick tick(pDepthMarketData);
		if (IsInTradeTime_Check_KLine(tick.InstrumentID, tick.ExchangeTime) && // 合法时间内
			strcmp(wdCTPLastInfos::instance()->GetLastTick(pDepthMarketData->InstrumentID).ExchangeTime, tick.ExchangeTime) /*排除重复tick到来*/ ) {

			m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnTick, &tick));
		}
	}
}


void CCTPMdApi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	
	if (!IsErrorRspInfo(pRspInfo, nRequestID, bIsLast)
		&& pSpecificInstrument)
	{
		lock_guard<mutex> cl(m_mutexSetQuoteInstrumentIDs);

		m_setQuoteInstrumentIDs.insert(pSpecificInstrument->InstrumentID);
	}
}

void CCTPMdApi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	
	if (!IsErrorRspInfo(pRspInfo, nRequestID, bIsLast)
		&& pSpecificInstrument)
	{
		lock_guard<mutex> cl(m_mutexSetQuoteInstrumentIDs);

		m_setQuoteInstrumentIDs.erase(pSpecificInstrument->InstrumentID);
	}
}

void CCTPMdApi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{

}

bool CCTPMdApi::Checking()
{
	if (m_status == E_logined)
		return true;

	CThostFtdcRspInfoField RspInfo;
	unique_lock<mutex> lock(m_mutex_Status);
	if (!m_cvStatus.wait_until(lock, std::chrono::system_clock::now()+std::chrono::seconds(5))) {
		strcpy(RspInfo.ErrorMsg, "5s之内还没连上CTP行情服务器");
		OnRspError(&RspInfo, 0, true);
		return false;
	}

	if (nullptr == m_pApi) {
		memset((void*)&RspInfo, 0, sizeof(CThostFtdcRspInfoField));
		strcpy(RspInfo.ErrorMsg, "CCTPMdApi : nullptr == m_pApi");
		OnRspError(&RspInfo, 0, true);
		return false;
	}
	return true;
}

bool CCTPMdApi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool isErr = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (isErr)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnError, pRspInfo));
	return isErr;
}

void CCTPMdApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	IsErrorRspInfo(pRspInfo, nRequestID, bIsLast);
}