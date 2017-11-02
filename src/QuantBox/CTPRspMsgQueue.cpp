#include "CTPRspMsgQueue.h"
#include <string.h>
#include "TDSQLite.h"
#include "toolkit.h"
#include "logger.h"
#include "CTPRspMsg.h"
#include "MarketData.h"
#include "MyThreads.h"
#include "CTPLastInfos.h"
#include "Enums.h"
#include "CppMysql.h"
#include "GlobalVars.h"
#include "defines.h"

using namespace std;

#ifdef MD_SERVER
	#define MD_THREAD_NUM 4
#else
	#define MD_THREAD_NUM 1
#endif

CCTPRspMsgQueue::CCTPRspMsgQueue(wdSystemType type, TDSQLite *pSqliteDB) : m_type(type), m_pSqliteDB(pSqliteDB)
{
	if (m_type == E_RealtimeMarketData)
		m_pThreads = std::make_shared<CMyThreads>(MD_THREAD_NUM, std::bind(&CCTPRspMsgQueue::_RunInThread, this),
			std::bind(&CCTPRspMsgQueue::_RunInThreadFormer, this), std::bind(&CCTPRspMsgQueue::_RunInThreadLater, this));		
	else
		m_pThreads = std::make_shared<CMyThreads>(1, std::bind(&CCTPRspMsgQueue::_RunInThread, this));
	
	m_pThreads->start();
}

CCTPRspMsgQueue::~CCTPRspMsgQueue(void)
{
}

void CCTPRspMsgQueue::_RunInThreadFormer()
{
#ifdef MD_SERVER // 服务器
	if (!m_mapMysql[this_thread::get_id()].Mysql_Init())
		LOG_ERROR << "线程" << this_thread::get_id() << "连接mysql失败";
#endif
}

void CCTPRspMsgQueue::_RunInThread()
{
	std::shared_ptr<CCTPRspMsgItem> pMsgItem;
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_queue.empty()) {
			m_conditionVariable.wait(lock);
			return;
		}
		pMsgItem = m_queue.front();
		m_queue.pop();
	}

	switch (pMsgItem->get_type())
	{
	case E_fnOnConnectInfo:			
		{
			if (g_fnOnMdConnect)
				(g_fnOnMdConnect)(*pMsgItem);
		}
		break;
	case E_fnOnTick:
		{
			if (m_type == E_RealtimeMarketData)
				_Output_OnRtnDepthMarketData(pMsgItem);
			else
				_Output_OnHistoryTick(pMsgItem);
		}		
		break;
	case E_fnOnKLine:
		// 历史K线
		_Output_OnHistoryKLine(pMsgItem);
		break;
	case E_fnOnOrder:
		{
			if (g_fnOnRspQryOrder)
				g_fnOnRspQryOrder(*pMsgItem);
		}
		break;
	case E_fnOnTrade:
		{
			if (g_fnOnRspQryTrade)
				g_fnOnRspQryTrade(*pMsgItem);
		}
		break;
	case E_fnOnPosition:
		{
			if (g_fnOnRspQryInvestorPosition)
				g_fnOnRspQryInvestorPosition(*pMsgItem);
		}
		break;
	case E_fnOnInstrument:
		{
			if (g_fnOnRspQryInstrument)
				g_fnOnRspQryInstrument(*pMsgItem);
		}
		break;
	case E_fnOnSettlementInfo:
		{
			if (g_fnOnRspQrySettlementInfo)
				g_fnOnRspQrySettlementInfo(pMsgItem->get_settlement_info()->c_str());
		}
		break;
	case E_fnOnTradingAccount:
		{
			
		}
		break;
	case E_fnOnError:
		{
			if (g_fnOnMdRspError)
				g_fnOnMdRspError(pMsgItem->get_error()->c_str());
		}
		break;
	default:
		break;
	}
}

void CCTPRspMsgQueue::_RunInThreadLater()
{
#ifdef MD_SERVER // 服务器
	m_mapMysql[this_thread::get_id()].Mysql_Finalize();
#endif
}

void CCTPRspMsgQueue::InputQueue(const std::shared_ptr<CCTPRspMsgItem> &pMsgItem)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_queue.push(pMsgItem);

	if (m_queue.size() == 1)
		m_conditionVariable.notify_one();
}

void CCTPRspMsgQueue::_SQLite_OnOrder(const std::shared_ptr<CCTPRspMsgItem> &pMsgItem)
{	
//	CThostFtdcOrderField *pOrder = *pMsgItem;
//#ifndef MD_SERVER
//	if (m_pSqliteDB) {
//		m_pSqliteDB->SQLite_Insert_Order(*pOrder);
//		if (IsAvailableOrder(pOrder))
//			m_pSqliteDB->SQLite_Insert_AvailableOrder(*pOrder);
//		else
//			m_pSqliteDB->SQLite_DeletE_AvailableOrdersOrder(*pOrder);
//	}
//#endif
}

void CCTPRspMsgQueue::_SQLite_OnTrade(const std::shared_ptr<CCTPRspMsgItem> &pMsgItem)
{	
//	CThostFtdcTradeField *pTrade = *pMsgItem;
//#ifndef MD_SERVER
//	if (m_pSqliteDB)
//		m_pSqliteDB->SQLite_Insert_Trade(*pTrade);
//#endif
}


void CCTPRspMsgQueue::_Output_OnRtnDepthMarketData(const std::shared_ptr<CCTPRspMsgItem> &pMsgItem)
{
	wdTick &tick = *(wdTick*)*pMsgItem;
	if (isStrNULL(tick.InstrumentID)) {
		LOG_ERROR << "行情有错误:InstrumentID为''";
		return;
	}		

	wdCTPLastInfos::instance()->_Output_OnRtnDepthMarketData(tick);
#ifdef MD_SERVER
	m_mapMysql[this_thread::get_id()].Mysql_MarketData_Insert(tick);
#endif
}


void CCTPRspMsgQueue::_Output_OnHistoryTick(const std::shared_ptr<CCTPRspMsgItem> &pMsgItem)
{
	wdTick *pTick = *pMsgItem;
	wdCTPLastInfos::instance()->_AddLastTick(*pTick, true);
	if (g_fnOnHistory_Tick) {
		g_fnOnHistory_Tick(pTick);
	}
}

void CCTPRspMsgQueue::_Output_OnHistoryKLine(const std::shared_ptr<CCTPRspMsgItem> &pMsgItem)
{
	wdKLine *pKLine = *pMsgItem;
	wdCTPLastInfos::instance()->_AddLastKLine(*pKLine, true);
	if (g_fnOnHistory_KLine) {		
		g_fnOnHistory_KLine(pKLine);
	}
}
