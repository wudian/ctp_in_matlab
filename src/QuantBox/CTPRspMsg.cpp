
#include "CTPRspMsg.h"
#include "MarketData.h"
#include "TradeData.h"

CCTPRspMsgItem::CCTPRspMsgItem(E_CTPRspMsgType type, void *pMsgItem) : m_type(type)
{
	switch (m_type)
	{
	case E_fnOnConnectInfo:
		ConnectInfo = new wdConnectInfo(*(wdConnectInfo*)pMsgItem);
		break;
	case E_fnOnTick:
		Tick = new wdTick(*(wdTick*)pMsgItem);
		break;
	case E_fnOnKLine:
		KLine = new wdKLine(*(wdKLine*)pMsgItem);
		break;	
	case E_fnOnOrder:
		Order = pMsgItem != nullptr ? new wdOrder(*(wdOrder*)pMsgItem) : nullptr;
		break;
	case E_fnOnTrade:
		TradeTicket =  pMsgItem != nullptr ? new wdTradeTicket(*(wdTradeTicket*)pMsgItem) : nullptr;
		break;
	case E_fnOnPosition:
		Position =  pMsgItem != nullptr ? new wdPosition(*(wdPosition*)pMsgItem) : nullptr;
		break;
	case E_fnOnSettlementInfo:
		SettlementInfo = new std::string(*(std::string*)pMsgItem);
		break;
	case E_fnOnInstrument:
		InstrumentInfo = new std::map<std::string, wdInstrument>(*(std::map<std::string, wdInstrument>*)pMsgItem);
		break;
	case E_fnOnError:
		RspError = new std::string(*(std::string*)pMsgItem);
		break;	
	default:
		break;
	}
}

CCTPRspMsgItem::~CCTPRspMsgItem()
{
	switch (m_type)
	{
	case E_fnOnConnectInfo:
		delete ConnectInfo;
		break;
	case E_fnOnTick:
		delete Tick;
		break;
	case E_fnOnKLine:
		delete KLine;
		break;	
	case E_fnOnOrder:
		delete Order;
		break;
	case E_fnOnTrade:
		delete TradeTicket;
		break;
	case E_fnOnPosition:
		delete Position;
		break;
	case E_fnOnSettlementInfo:
		delete SettlementInfo;
		break;	
	case E_fnOnInstrument:
		delete InstrumentInfo;
		break;
	case E_fnOnError:
		delete RspError;
		break;
	default:
		break;
	}
}