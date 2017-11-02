
#include "CTPReqMsgQueue.h"
#include <windows.h>
#include "CTP/ThostFtdcTraderApi.h"
#include "CTPReqMsg.h"
#include "MyThreads.h"

//#include "CTPTdApi.h"
#include "logger.h"
#include "Types.h"

CCTPReqMsgQueue::CCTPReqMsgQueue(std::atomic<unsigned int> &nRequestID)
	//: m_pApi(nullptr)
	: m_nRequestID(nRequestID)
	, m_nSleep(1)
{
	for (int i = E_QrySettlementInfoField; i <= E_QryTrade; ++i) {
		m_mapUnique[(E_CTPReqType)i] = false;
	}

	//m_pThreads_Important = std::make_shared<CMyThreads>(1, std::bind(&CCTPReqMsgQueue::ProcessImportantReqs, this));
	//m_pThreads_Important->start(THREAD_PRIORITY_HIGHEST);
	m_pThreads = std::make_shared<CMyThreads>(1, std::bind(&CCTPReqMsgQueue::ProcessReqs, this));
	m_pThreads->start(THREAD_PRIORITY_NORMAL);
}


CCTPReqMsgQueue::~CCTPReqMsgQueue(void)
{
}

//void CCTPReqMsgQueue::InputQueue_Important(std::shared_ptr<CCTPReqMsgItem> pReqMsg)
//{
//	std::unique_lock<std::mutex> lock(m_mutex_Important);
//	m_reqQueue_Important.push(pReqMsg);
//	m_condition_variable_Important.notify_one();
//}

//void CCTPReqMsgQueue::ProcessImportantReqs()
//{
//	std::shared_ptr<CCTPReqMsgItem> pReqMsg;
//	{
//		std::unique_lock<std::mutex> lock(m_mutex_Important);
//		if (m_reqQueue_Important.empty())
//			m_condition_variable_Important.wait(lock);
//		pReqMsg = m_reqQueue_Important.front();
//	}
//	m_ctpTdApi.ReqOrderInsert()
//}


void CCTPReqMsgQueue::InputQueue(std::shared_ptr<CCTPReqMsgItem> pReqMsg)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_reqQueue.push(pReqMsg);
	m_condition_variable.notify_one();
}

void CCTPReqMsgQueue::ProcessReqs()
{
	std::shared_ptr<CCTPReqMsgItem> pReqMsg;
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_reqQueue.empty())
			m_condition_variable.wait(lock);
		pReqMsg = m_reqQueue.front();
	}
	/*
	int iRet = 0;
	switch (pReqMsg->get_type())
	{
	case E_QryInstrumentField:
		{			
			iRet = m_pApi->ReqQryInstrument((CThostFtdcQryInstrumentField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
			std::string msg = "";
			if (iRet == -1) msg = "网络连接失败";
			else if (iRet == -2) msg = "未处理请求超过许可数";
			else if (iRet == -3) msg = "每秒发送请求数超过许可数";
			else msg = "成功";
			LOG_NORMAL << "--->>> 请求查询合约: " << msg;
		}
		break;
	case E_QryTradingAccountField:
		{		
			iRet = m_pApi->ReqQryTradingAccount((CThostFtdcQryTradingAccountField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
			LOG_NORMAL << "--->>> 请求查询资金账户: " << ((iRet == 0) ? "成功" : "失败");
		}
		break;
	case E_QryInvestorPositionField:
		{
			iRet = m_pApi->ReqQryInvestorPosition((CThostFtdcQryInvestorPositionField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
		}
		break;
	case E_QryInvestorPositionDetailField:
		{
			iRet = m_pApi->ReqQryInvestorPositionDetail((CThostFtdcQryInvestorPositionDetailField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
		}
		break;
	case E_QryInstrumentCommissionRateField:
		{
			iRet = m_pApi->ReqQryInstrumentCommissionRate((CThostFtdcQryInstrumentCommissionRateField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
		}
		break;
	case E_QryInstrumentMarginRateField:
		{
			iRet = m_pApi->ReqQryInstrumentMarginRate((CThostFtdcQryInstrumentMarginRateField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
		}
		break;
	case E_QryDepthMarketDataField:
		{
			iRet = m_pApi->ReqQryDepthMarketData((CThostFtdcQryDepthMarketDataField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
		}
		break;
	case E_QrySettlementInfoField:
		{
			iRet = m_pApi->ReqQrySettlementInfo((CThostFtdcQrySettlementInfoField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
		}
		break;
	case E_QryOrder:
		{
			iRet = m_pApi->ReqQryOrder((CThostFtdcQryOrderField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
		}
		break;
	case E_QryTrade:
		{
			iRet = m_pApi->ReqQryTrade((CThostFtdcQryTradeField*)pReqMsg->GetMsgItem(), ++m_nRequestID);
		}
		break;
	default:
		_ASSERT(FALSE);
		break;
	}*/
}