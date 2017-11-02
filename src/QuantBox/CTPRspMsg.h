#ifndef _CTP_RSP_MSG_H_
#define _CTP_RSP_MSG_H_

#include <string>
#include <map>

enum E_CTPRspMsgType;
struct wdConnectInfo;
struct wdKLine;
struct wdTick;
struct wdOrder;
struct wdTradeTicket;
struct wdPosition;
struct wdInstrument;

// CTP返回的消息类型
enum E_CTPRspMsgType
{
	E_fnOnConnectInfo,			// 连接

	E_fnOnTick,			
	E_fnOnKLine,

	E_fnOnOrder,	
	E_fnOnTrade,
	E_fnOnPosition,

	E_fnOnInstrument,			// 合约信息(包括合约状态、保证金、手续费)
	E_fnOnSettlementInfo,		// 结算信息
	E_fnOnTradingAccount,		// 资金	

	E_fnOnError,				// 错误信息
};

// CTP响应消息数据结构
class CCTPRspMsgItem
{
	E_CTPRspMsgType				m_type;			// 消息类型
	union {
		wdConnectInfo			*ConnectInfo;	// 连接信息	
		wdTick					*Tick;			// tick		
		wdKLine					*KLine;			// kline	
		wdOrder					*Order;
		wdTradeTicket			*TradeTicket;
		wdPosition				*Position;
		std::map<std::string, wdInstrument> *InstrumentInfo;
		std::string				*SettlementInfo;// 结算
		std::string				*RspError;		// 错误信息
	};

public:
	CCTPRspMsgItem(E_CTPRspMsgType type, void *pMsgItem);
	~CCTPRspMsgItem();

	E_CTPRspMsgType get_type() const { return m_type; }
	std::string *get_settlement_info() { return SettlementInfo; }
	std::string *get_error() { return RspError; }
	operator wdConnectInfo*() { return ConnectInfo; }
	operator wdTick*() { return Tick; }
	operator wdKLine*() { return KLine; }
	operator wdOrder*() { return Order; }
	operator wdTradeTicket*() { return TradeTicket; }
	operator wdPosition*() { return Position; }
	operator std::map<std::string, wdInstrument> *() { return InstrumentInfo; }

private:
	CCTPRspMsgItem();
};

#endif