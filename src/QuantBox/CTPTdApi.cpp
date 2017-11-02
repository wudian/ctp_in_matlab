
#include "CTPTdApi.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>
#include "toolkit.h"
#include "Enums.h"
#include "MyThreads.h"
#include "CTPRspMsg.h"
#include "CTPRspMsgQueue.h"
#include "CTPReqMsg.h"
#include "TDSQLite.h"
#include "MarketData.h"
#include "CTPLastInfos.h"
#include "CppMysql.h"
#include "GlobalVars.h"

using namespace std;


CCTPTdApi *CCTPTdApi::instance()
{
	static CCTPTdApi s_tdApi;
	return &s_tdApi;
}

CCTPTdApi::CCTPTdApi(void)
	: CCTPCommonApi()
	, m_pApi(nullptr)
	, m_nMaxOrderRef(0)
{
	m_sqliteDB = std::make_shared<TDSQLite>();
	if (!m_sqliteDB->SQLite_Init()) {
		LOG_ERROR << "TdSqlite初始化失败";
	}
	m_msgQueue = std::make_shared<CCTPRspMsgQueue>(E_TradeData, m_sqliteDB.get());

	m_pReqThreads = std::make_shared<CMyThreads>(1, std::bind(&CCTPTdApi::_RunInThread, this));
	
	m_pReqThreads->start();

	for (int i = E_QrySettlementInfoField; i <= E_QryTrade; ++i) {
		m_mapUniqueReq[(E_CTPReqType)i] = false;
	}
}


CCTPTdApi::~CCTPTdApi(void)
{
	if (m_sqliteDB)
		m_sqliteDB->SQLite_Finalize();
}

void CCTPTdApi::Disconnect()
{	
	m_nRequestID = 0;
	m_status =  E_unconnected;
	//OnFrontDisconnected(E_unconnected, "主动请求断开TD");
	m_pReqThreads->terminate();

	if(m_pApi)
	{
		m_pApi->RegisterSpi(NULL);
		m_pApi->Release();
		m_pApi = NULL;
	}	
}

void CCTPTdApi::Connect()
{
	if (m_status != E_confirmed && m_status != E_uninit)
	{
		LOG_NORMAL << "正在连接CTP交易前置";
		return;
	}
	else if (m_status == E_confirmed)
	{
		Disconnect();
		LOG_NORMAL << "断开CTP交易前置并重连";
	}

	m_pApi = CThostFtdcTraderApi::CreateFtdcTraderApi((g_Database+"TDStream\\").c_str());	// 创建UserApi

	m_status = E_inited;
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status)));

	if (m_pApi)
	{
		m_pApi->RegisterSpi(this);		// 注册事件类
		m_pApi->RegisterFront((char*)g_tdAddress.c_str());
		m_pApi->SubscribePublicTopic(g_resumeType);
		m_pApi->SubscribePrivateTopic(g_resumeType);

		//初始化连接
		m_pApi->Init();
		m_status = E_connecting;
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status)));
	}
}

void CCTPTdApi::InputReqQueue(const std::shared_ptr<CCTPReqMsgItem> &pReqMsg)
{
	if (m_mapUniqueReq[pReqMsg->get_type()])
		return;
	std::unique_lock<std::mutex> lock(m_reqMutex);
	m_reqQueue.push(pReqMsg);
	m_mapUniqueReq[pReqMsg->get_type()] = true;
	m_reqConditionVariable.notify_one();
}

/*
 查询数据注意事项：
 1) 综合交易平台仅对查询进行流量限制，对交易指令没有限制。
 2) 如果有在途的查询，不允许发新的查询。
 3) 1 秒钟最多允许发送1个查询。
 4) 返回值“-2”表示“未处理请求超过许可数”
 5) “-3”表示“每秒发送请求数超过许可数”
*/
void CCTPTdApi::_RunInThread()
{
	int iRet = 0;
	std::shared_ptr<CCTPReqMsgItem> pRequest = nullptr;
	{
		unique_lock<mutex> lock(m_reqMutex);
		if (m_reqQueue.empty())
			m_reqConditionVariable.wait(lock);
		pRequest = m_reqQueue.front();
	}

	unsigned request_id = ++m_nRequestID;
	switch(pRequest->get_type())
	{
	
	case E_SettlementInfoConfirmField:
		{
			iRet = m_pApi->ReqSettlementInfoConfirm(*pRequest, request_id);
			LOG_NORMAL << "--->>> 投资者结算结果确认: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	case E_QryInstrumentField:
		{
			iRet = m_pApi->ReqQryInstrument(*pRequest, request_id);
			LOG_NORMAL << "--->>> 请求查询合约: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	case E_QryTradingAccountField:
		{
			iRet = m_pApi->ReqQryTradingAccount(*pRequest, request_id);
			LOG_NORMAL << "--->>> 请求查询资金账户: " << ((iRet == 0) ? "成功" : "失败");
		}		

		break;
	case E_QryInvestorPositionField:
		{
			iRet = m_pApi->ReqQryInvestorPosition(*pRequest, request_id);
			LOG_NORMAL << "--->>> 请求查询持仓: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	case E_QryInvestorPositionDetailField:
		{
			iRet=m_pApi->ReqQryInvestorPositionDetail(*pRequest, request_id);
		}
		break;
	case E_QryInstrumentCommissionRateField:
		{
			iRet = m_pApi->ReqQryInstrumentCommissionRate(*pRequest, request_id);
			LOG_NORMAL << "--->>> 请求查询合约手续费率: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	case E_QryInstrumentMarginRateField:
		{
			iRet = m_pApi->ReqQryInstrumentMarginRate(*pRequest, request_id);
			LOG_NORMAL << "--->>> 请求查询合约保证金率: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	case E_QryDepthMarketDataField:
		{
			iRet = m_pApi->ReqQryDepthMarketData(*pRequest, request_id);
			LOG_NORMAL << "--->>> 请求查询行情: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	case E_QrySettlementInfoField:
		{
			iRet = m_pApi->ReqQrySettlementInfo(*pRequest, request_id);
			LOG_NORMAL << "--->>> 请求查询投资者结算结果: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	case E_QryOrder:
		{
			iRet = m_pApi->ReqQryOrder(*pRequest, request_id);
			LOG_NORMAL << "--->>> 请求查询报单: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	case E_QryTrade:
		{
			iRet = m_pApi->ReqQryTrade(*pRequest, request_id);
			LOG_NORMAL << "--->>> 请求查询成交: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	default:
		_ASSERT(FALSE);
		break;
	}

	if (0 == iRet || -1 == iRet) {
		m_nSleep = 1;

		unique_lock<mutex> lock(m_reqMutex);
		m_reqQueue.pop();

		if (-1 == iRet)
			LOG_ERROR << "网络连接失败";
	}
	else {
		m_nSleep *= 4;
		m_nSleep %= 1023;
		if (-2 == iRet) {
			LOG_WARNING << "未处理请求超过许可数";
		}
		else if (-3 == iRet) {
			LOG_WARNING << "每秒发送请求数超过许可数";
		}
	}
	Sleep(m_nSleep);
}

void CCTPTdApi::OnFrontConnected()
{
	m_status =  E_connected;
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status,nullptr)));
	
	if (g_tdAuthCode.length()>0 && g_tdUserProductInfo.length()>0)
	{
		//填了认证码就先认证
		ReqAuthenticate();
	}
	else
	{
		ReqUserLogin();
	}
}

void CCTPTdApi::OnFrontDisconnected(int nReason)
{	
	m_status = E_unconnected;
	CThostFtdcRspInfoField RspInfo;
	//构造出来的错误消息，为了统一出错信息
	RspInfo.ErrorID = nReason;
	GetOnFrontDisconnectedMsg(&RspInfo);

	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status,nullptr, RspInfo.ErrorMsg)));
}

void CCTPTdApi::OnFrontDisconnected(wdConnectionStatus status, const char *szReason)
{
	CThostFtdcRspInfoField RspInfo;
	strcpy_s(RspInfo.ErrorMsg, szReason);
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status,nullptr, RspInfo.ErrorMsg)));
}

void CCTPTdApi::ReqAuthenticate()
{	
	if (NULL == m_pApi)
		return;
	m_status = E_authing;
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status)));

	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_ReqAuthenticateField);
	pRequest->MakeCThostFtdcReqAuthenticateField();
	int iRet = m_pApi->ReqAuthenticate(*pRequest, ++m_nRequestID);
	LOG_NORMAL << "--->>> 发送用户认证请求: " << ((iRet == 0) ? "成功" : "失败");
}

void CCTPTdApi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (!IsErrorRspInfo(pRspInfo, nRequestID, bIsLast) && pRspAuthenticateField) // 正确
	{
		m_status = E_authed;
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status)));

		ReqUserLogin();
	}
	else
	{
		m_status = E_connected;
		OnFrontDisconnected(E_authing, "认证失败，无法登陆CTP交易前置");
	}
}

void CCTPTdApi::ReqUserLogin()
{	
	if (NULL == m_pApi)
		return;

	m_status = E_logining;
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status)));

	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_ReqUserLoginField);
	pRequest->MakeCThostFtdcReqUserLoginField();
	int iRet = m_pApi->ReqUserLogin(*pRequest, ++m_nRequestID);	
	LOG_NORMAL << "--->>> 发送用户登录请求: " << ((iRet == 0) ? "成功" : "失败");
}

void CCTPTdApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (!IsErrorRspInfo(pRspInfo, nRequestID, bIsLast) && pRspUserLogin)
	{
		m_status = E_logined;
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, E_logined, pRspUserLogin)));		
		g_RspUserLogin = *pRspUserLogin;
		m_nMaxOrderRef = atoi(pRspUserLogin->MaxOrderRef);

		/*ReqQrySettlementInfoConfirm();
		unique_lock<mutex> lock(m_mutex_Status);
		if (!m_cvStatus.wait_until(lock, std::chrono::system_clock::now()+std::chrono::seconds(3)))*/
		ReqSettlementInfoConfirm();
	}
	else
	{
		if (g_tdAuthCode.length()>0 && g_tdUserProductInfo.length()>0)
			m_status = E_authed;
		else
			m_status = E_connected;
		if (pRspInfo == nullptr)
			OnFrontDisconnected(m_status, "登陆交易前置失败");
		else
			OnFrontDisconnected(m_status, pRspInfo->ErrorMsg);		
	}
}

void CCTPTdApi::ReqSettlementInfoConfirm()
{	
	if (NULL == m_pApi)
		return;

	m_status = E_confirming;
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status)));

	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_SettlementInfoConfirmField);
	pRequest->MakeCThostFtdcSettlementInfoConfirmField();
	int iRet = m_pApi->ReqSettlementInfoConfirm(*pRequest, ++m_nRequestID);	
}

///请求查询结算信息确认
void CCTPTdApi::ReqQrySettlementInfoConfirm()
{
	if (NULL == m_pApi)
		return;
	m_status = E_confirming;
	m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status)));

	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QrySettlementInfoConfirmField);
	pRequest->MakeCThostFtdcQrySettlementInfoConfirmField();
	int iRet = m_pApi->ReqQrySettlementInfoConfirm(*pRequest, ++m_nRequestID);	
}

void CCTPTdApi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	DoSthOnBeginning(pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast);
}

void CCTPTdApi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	DoSthOnBeginning(pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast);
}

bool CCTPTdApi::_IsMyOrder(TThostFtdcOrderRefType OrderRef)
{
	if (g_trader_no == "00") // 不支持子账号
		return true;

	string trade_no = ((string)OrderRef).substr(0, 2);
	return trade_no == g_trader_no;
}

void CCTPTdApi::DoSthOnBeginning(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_status == E_confirmed)
		return;
	if (!IsErrorRspInfo(pRspInfo, nRequestID, bIsLast) && pSettlementInfoConfirm)
	{
		m_status = E_confirmed;
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnConnectInfo, &wdConnectInfo(E_TD, m_status)));

		//m_cvStatus.notify_all();
		LOG_NORMAL << "成功确认结算，可以进行交易";
		ReqQryTradingAccount();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		ReqQryDepthMarketData();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		ReqQryOrder();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		ReqQryTrade();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		ReqQryInvestorPosition();
	}
	else
	{
		m_status = E_logined;
		OnFrontDisconnected(E_confirming, "确认结算失败，无法进行交易");
		LOG_ERROR << "确认结算失败，无法进行交易";
	}
}

void CCTPTdApi::SendLimitOrder(const char *Instrument, double Price, int Volume, wdDirectionType Direction, wdOffsetFlagType OffsetFlag)
{	
	if (m_pApi == nullptr)
		return;

	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_InputOrderField);

	pRequest->MakeCThostFtdcInputOrderField(m_nMaxOrderRef++, Instrument, THOST_FTDC_OPT_LimitPrice, Price, Volume, Direction, OffsetFlag, THOST_FTDC_TC_GFD);

	_ReqOrderInsert(*pRequest, E_Limit);
}

void CCTPTdApi::_ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, wdOrderType type)
{
	int nRet = m_pApi->ReqOrderInsert(pInputOrder, ++m_nRequestID);
	std::string str = "--->>> ";
	switch (type)
	{
	case E_Limit:
		str += "限价单发送";
		break;
	case E_Market:
		str += "市价单发送";
		break;
	case E_Contingent:
		str += "触发单发送";
		break;
	default:
		break;
	}
	str += ((nRet == 0) ? "成功" : "失败");
	
	LOG_NORMAL << str;

	wdOrder &order = m_mapOrders[wdOrderKey(g_RspUserLogin.FrontID, g_RspUserLogin.SessionID, pInputOrder->OrderRef)];
	order.Type = type;
	order.update(pInputOrder, E_InsertSubmitted, str.c_str());

	m_sqliteDB->SQLite_Insert_Order(order);

	if (m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnOrder, &order));
}

void CCTPTdApi::TD_SendMarketOrder(const char *Instrument, int Volume, wdDirectionType Direction, wdOffsetFlagType OffsetFlag)
{
	if (m_pApi == nullptr)
		return;

	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_InputOrderField);

	if (g_tradeType == E_Actual) {
		pRequest->MakeCThostFtdcInputOrderField(m_nMaxOrderRef++, Instrument, THOST_FTDC_OPT_AnyPrice, 0, Volume, Direction, OffsetFlag, THOST_FTDC_TC_IOC);
	}
	else { // 模拟盘
		double Price = 0.;
		wdLimitPrice limitPrice = m_Instruments[Instrument].LimitPrice;
		if (Direction == E_Buy)
			Price = limitPrice.UpperLimitPrice;
		else 
			Price = limitPrice.LowerLimitPrice;
		pRequest->MakeCThostFtdcInputOrderField(m_nMaxOrderRef++, Instrument, THOST_FTDC_OPT_LimitPrice, Price, Volume, Direction, OffsetFlag, THOST_FTDC_TC_GFD);
	}

	_ReqOrderInsert(*pRequest, E_Market);
}

void CCTPTdApi::TD_SendContingentOrder(const char *Instrument, double Price, int Volume, wdDirectionType Direction, wdOffsetFlagType OffsetFlag, 
									   wdContingentConditionType ContingentCondition, double StopPrice)
{
	if (m_pApi == nullptr)
		return;

	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_InputOrderField);

	pRequest->MakeCThostFtdcInputOrderField(m_nMaxOrderRef++, Instrument, THOST_FTDC_OPT_LimitPrice, Price, Volume, Direction, OffsetFlag, THOST_FTDC_TC_GFD, ContingentCondition, StopPrice);
	_ReqOrderInsert(*pRequest, E_Contingent);
}

void CCTPTdApi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (!pInputOrder || !pRspInfo || !_IsMyOrder(pInputOrder->OrderRef))
		return;

	wdOrder &order = m_mapOrders[wdOrderKey(g_RspUserLogin.FrontID, g_RspUserLogin.SessionID, pInputOrder->OrderRef)];
	order.update(pInputOrder, E_InsertTrash, pRspInfo->ErrorMsg);

	m_sqliteDB->SQLite_Insert_Order(order);

	if (m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnOrder, &order));
}

void CCTPTdApi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
	if (pInputOrder && pRspInfo && _IsMyOrder(pInputOrder->OrderRef)) {
		wdOrder &order = m_mapOrders[wdOrderKey(g_RspUserLogin.FrontID, g_RspUserLogin.SessionID, pInputOrder->OrderRef)];
		order.update(pInputOrder, E_InsertTrash, pRspInfo->ErrorMsg);

		m_sqliteDB->SQLite_Insert_Order(order);

		if (m_msgQueue)
			m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnOrder, &order));	
	}
}

void CCTPTdApi::CancelOrder(wdOrder &order)
{
	if (m_pApi == nullptr)
		return;
	CThostFtdcInputOrderActionField orderAction = order;
	int nRet = m_pApi->ReqOrderAction(&orderAction, ++m_nRequestID);
	std::string str = "--->>> 撤单请求发送";
	str += ((nRet == 0) ? "成功" : "失败");
	LOG_NORMAL << str;

	order.Status = E_CancelSubmitted;
	strcpy_s(order.InsertTime, GetLocalTime().c_str());
	strcpy_s(order.StatusMsg, str.c_str());

	m_sqliteDB->SQLite_Insert_Order(order);

	if (m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnOrder, &order));	
}

void CCTPTdApi::CancelOrder(const char *Instrument, wdDirectionType Direction, wdOffsetFlagType OffsetFlag)
{
	m_sqliteDB->CancelOrder(Instrument, Direction, OffsetFlag);
}

void CCTPTdApi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (!pInputOrderAction || !pRspInfo || !_IsMyOrder(pInputOrderAction->OrderRef)) 
		return;
	
	wdOrder &order = m_mapOrders[wdOrderKey(pInputOrderAction->FrontID, pInputOrderAction->SessionID, pInputOrderAction->OrderRef)];
	order.update(pInputOrderAction, pRspInfo->ErrorMsg);

	m_sqliteDB->SQLite_Insert_Order(order);

	if (m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnOrder, &order));	
}

void CCTPTdApi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	if (!pOrderAction || !pRspInfo || !_IsMyOrder(pOrderAction->OrderRef)) 
		return;

	wdOrder &order = m_mapOrders[wdOrderKey(pOrderAction->FrontID, pOrderAction->SessionID, pOrderAction->OrderRef)];
	order.update(pOrderAction, pRspInfo->ErrorMsg);

	m_sqliteDB->SQLite_Insert_Order(order);

	if (m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnOrder, &order));
}

int CCTPTdApi::ReqQuoteInsert(
	int QuoteRef,
	const char *szInstrumentId,
	TThostFtdcPriceType	AskPrice,
	TThostFtdcPriceType	BidPrice,
	TThostFtdcVolumeType AskVolume,
	TThostFtdcVolumeType BidVolume,
	TThostFtdcOffsetFlagType AskOffsetFlag,
	TThostFtdcOffsetFlagType BidOffsetFlag,
	TThostFtdcHedgeFlagType	AskHedgeFlag,
	TThostFtdcHedgeFlagType	BidHedgeFlag
	)
{	
	return 0;
}

void CCTPTdApi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	
}

void CCTPTdApi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)
{	
	
}

void CCTPTdApi::OnRtnQuote(CThostFtdcQuoteField *pQuote)
{	

}

int CCTPTdApi::ReqQuoteAction(CThostFtdcQuoteField *pQuote)
{	
	if (m_pApi == nullptr)
		return 0;

	return 0;
}

void CCTPTdApi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	
}

void CCTPTdApi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
	
}

void CCTPTdApi::ReqQryTradingAccount()
{	
	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QryTradingAccountField);
	pRequest->MakeCThostFtdcQryTradingAccountField();
	InputReqQueue(pRequest);
}

void CCTPTdApi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if(pTradingAccount == nullptr || IsErrorRspInfo(pRspInfo, nRequestID, bIsLast))
		return;
	wdCTPLastInfos::instance()->UpdateTradingAccount(pTradingAccount);
}

//查持仓
void CCTPTdApi::ReqQryInvestorPosition(const char *szInstrumentId)
{	
	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QryInvestorPositionField);
	pRequest->MakeCThostFtdcQryInvestorPositionField(szInstrumentId==nullptr ? "" : szInstrumentId);
	InputReqQueue(pRequest);
}

void CCTPTdApi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (pInvestorPosition == nullptr || IsErrorRspInfo(pRspInfo, nRequestID, bIsLast))
		return;

	wdPosition position;
	position.update(pInvestorPosition);
	m_sqliteDB->SQLite_Insert_Position(position);
	if (m_msgQueue) 
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnPosition, &position));
}

void CCTPTdApi::ReqQryInvestorPositionDetail(const char *szInstrumentId)
{	
}

void CCTPTdApi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	
}

void CCTPTdApi::ReqQryInstrument(const char *szInstrumentId)
{
	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QryInstrumentField);
	pRequest->MakeCThostFtdcQryInstrumentField(szInstrumentId);
	InputReqQueue(pRequest);
}

void CCTPTdApi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pInstrument == nullptr || IsErrorRspInfo(pRspInfo, nRequestID, bIsLast)) {
		if (bIsLast)
			ReqQryInstrumentCommissionRate();
		return;
	}
	
	m_Instruments[pInstrument->InstrumentID].update(pInstrument);
	
	if (bIsLast)
		ReqQryInstrumentCommissionRate();
}

void CCTPTdApi::ReqQryInstrumentCommissionRate(const char *szInstrumentId)
{	
	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QryInstrumentCommissionRateField);
	pRequest->MakeCThostFtdcQryInstrumentCommissionRateField(szInstrumentId==nullptr ? "" : szInstrumentId);
	InputReqQueue(pRequest);
}

void CCTPTdApi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (pInstrumentCommissionRate == nullptr || IsErrorRspInfo(pRspInfo, nRequestID, bIsLast)) {
		if (bIsLast)
			ReqQryInstrumentMarginRate();
		return;
	}

	for (auto it = m_Instruments.begin(); it != m_Instruments.end(); ++it) {
		if (boost::equals(it->second.ProductID, pInstrumentCommissionRate->InstrumentID))
			it->second.update(pInstrumentCommissionRate);
	}

	if (bIsLast)
		ReqQryInstrumentMarginRate();
}

std::string CCTPTdApi::GetAllInstruments()
{
	static string s_allInstruments = "";
	if (s_allInstruments != "") {
		return s_allInstruments;
	}
	unique_lock<mutex> lock(m_mutexInstruments);
	m_cv_Instruments.wait(lock);
	//m_cv_Instruments.wait_until(lock, std::chrono::system_clock::now()+std::chrono::seconds(10));
	for (auto it = m_Instruments.begin(); it != m_Instruments.end(); ++it) {
		s_allInstruments += it->first + ",";
	}
	return s_allInstruments;
}

int CCTPTdApi::GetVolumeMultiple(const std::string &inst)
{
	return m_Instruments[inst].VolumeMultiple; 
}

void CCTPTdApi::ReqQryInstrumentMarginRate(const char *szInstrumentId, TThostFtdcHedgeFlagType HedgeFlag)
{	
	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QryInstrumentMarginRateField);
	pRequest->MakeCThostFtdcQryInstrumentMarginRateField(szInstrumentId==nullptr ? "" : szInstrumentId, HedgeFlag);
	InputReqQueue(pRequest);
}

//返回的保证金率已经包含了交易所保证金率及保证金率调整，也就是说返回最终的比率，即绝对值
void CCTPTdApi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (pInstrumentMarginRate == nullptr || IsErrorRspInfo(pRspInfo, nRequestID, bIsLast)) {
		if (bIsLast && m_msgQueue)
			m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnInstrument, &m_Instruments));
		return;
	}
	// 有待检验
	m_Instruments[pInstrumentMarginRate->InstrumentID].update(pInstrumentMarginRate);

	if (bIsLast && m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnInstrument, &m_Instruments));
}

void CCTPTdApi::ReqQryDepthMarketData()
{
	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QryDepthMarketDataField);
	pRequest->MakeCThostFtdcQryDepthMarketDataField();
	InputReqQueue(pRequest);
}

void CCTPTdApi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pDepthMarketData == nullptr || IsErrorRspInfo(pRspInfo, nRequestID, bIsLast)) 
		return;

	m_Instruments[pDepthMarketData->InstrumentID].update(pDepthMarketData);
	if (bIsLast) {
		m_cv_Instruments.notify_all();
		ReqQryInstrument();
	}
}


bool CCTPTdApi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool isErr = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (isErr && m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnError, &(std::string)pRspInfo->ErrorMsg));
	return isErr;
}

void CCTPTdApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	IsErrorRspInfo(pRspInfo, nRequestID, bIsLast);
}

bool CCTPTdApi::Checking()
{
	if (m_status == E_confirmed)
		return true;
	
	CThostFtdcRspInfoField RspInfo;
	unique_lock<mutex> lock(m_mutex_Status);
	if (!m_cvStatus.wait_until(lock, std::chrono::system_clock::now()+std::chrono::milliseconds(3000))) {
		strcpy(RspInfo.ErrorMsg, "3s之内还没连上CTP交易服务器");
		OnRspError(&RspInfo, 0, true);
		return false;
	}

	if (nullptr == m_pApi) {
		memset((void*)&RspInfo, 0, sizeof(CThostFtdcRspInfoField));
		strcpy(RspInfo.ErrorMsg, "CCTPTdApi : nullptr == m_pApi");
		OnRspError(&RspInfo, 0, true);
		return false;
	}

	return true;
}

void CCTPTdApi::ReqQryOrder(const char *InstrumentID)
{
	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QryOrder);
	pRequest->MakeCThostFtdcQryOrderField(InstrumentID==nullptr ? "" : InstrumentID);
	InputReqQueue(pRequest);
}

void CCTPTdApi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//有可能最后一个单子不是自己的
	if (bIsLast && m_msgQueue) {
		//m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnOrder, nullptr));
	}

	if (pOrder == nullptr || !_IsMyOrder(pOrder->OrderRef) || IsErrorRspInfo(pRspInfo, nRequestID, bIsLast))
		return;

	wdOrder &order = m_mapOrders[wdOrderKey(pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef)];
	order.update(pOrder);

	m_sqliteDB->SQLite_Insert_Order(order);
	if (m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnOrder, &order));
}

void CCTPTdApi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	if (pOrder == nullptr || !_IsMyOrder(pOrder->OrderRef))
		return;

	wdOrder &order = m_mapOrders[wdOrderKey(pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef)];
	order.update(pOrder);

	m_sqliteDB->SQLite_Insert_Order(order);

	if (m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnOrder, &order));
}

void CCTPTdApi::ReqQryTrade(const char *InstrumentID)
{	
	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QryTrade);
	pRequest->MakeCThostFtdcQryTradeField(InstrumentID==nullptr ? "" : InstrumentID);
	InputReqQueue(pRequest);
}

void CCTPTdApi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (pTrade == nullptr || !_IsMyOrder(pTrade->OrderRef) || IsErrorRspInfo(pRspInfo, nRequestID, bIsLast))
		return;

	wdTradeTicket tradeTick;
	tradeTick.update(pTrade);
	m_sqliteDB->SQLite_Insert_Trade(tradeTick);
	if (m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnTrade, &tradeTick));

	if (g_trader_no != "00") { // 支持子账号
		wdPosition &position = m_mapPositions[wdPositionKey(pTrade->InstrumentID, pTrade->Direction)];
		position.update(pTrade);
		m_sqliteDB->SQLite_Insert_Position(position);
		if (m_msgQueue) 
			m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnPosition, &position));
	}
}

void CCTPTdApi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	if (nullptr == pTrade || !_IsMyOrder(pTrade->OrderRef))
		return;

	wdTradeTicket tradeTick;
	tradeTick.update(pTrade);
	m_sqliteDB->SQLite_Insert_Trade(tradeTick);
	if (m_msgQueue)
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnTrade, &tradeTick));
	
	if (g_trader_no != "00") { // 支持子账号
		wdPosition &position = m_mapPositions[wdPositionKey(pTrade->InstrumentID, pTrade->Direction)];
		position.update(pTrade);
		m_sqliteDB->SQLite_Insert_Position(position);
		if (m_msgQueue) 
			m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnPosition, &position));
	}
}

void CCTPTdApi::ReqQrySettlementInfo(const char *szTradingDay)
{
	if (m_mapSettlementInfo[szTradingDay] != "" && m_msgQueue) { // 已经查过了,不必重复查询
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnSettlementInfo, &m_mapSettlementInfo[szTradingDay]));
		return;
	}
	
	std::shared_ptr<CCTPReqMsgItem> pRequest = std::make_shared<CCTPReqMsgItem>(E_QrySettlementInfoField);
	pRequest->MakeCThostFtdcQrySettlementInfoField(szTradingDay);
	InputReqQueue(pRequest);
}

void CCTPTdApi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (pSettlementInfo == nullptr || IsErrorRspInfo(pRspInfo, nRequestID, bIsLast)) 
		return;

	m_mapSettlementInfo[pSettlementInfo->TradingDay] += pSettlementInfo->Content;
	if (bIsLast && m_msgQueue) {
		m_msgQueue->InputQueue(std::make_shared<CCTPRspMsgItem>(E_fnOnSettlementInfo, &m_mapSettlementInfo[pSettlementInfo->TradingDay]));
	}
}

void CCTPTdApi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
	m_Instruments[pInstrumentStatus->InstrumentID].update(pInstrumentStatus);
}