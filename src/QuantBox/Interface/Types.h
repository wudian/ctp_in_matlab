#ifndef _TYPES_H_
#define _TYPES_H_

#include <map>
#include <functional>

#ifdef QUANTBOX_EXPORTS
#define QUANTBOX_API __declspec(dllexport)
#else
#define QUANTBOX_API __declspec(dllimport)
#endif


struct wdTick;
struct wdKLine;
struct wdConnectInfo;
struct wdInstrument;
struct wdTradingAccount;
struct wdOrder;
struct wdPosition;
struct wdTradeTicket;

///行情or交易
enum wdConnectType { E_MD, E_TD };

/*! 连接状态枚举 */
enum wdConnectionStatus
{
	E_uninit,		//未初始化
	E_inited,		//已经初始化
	E_unconnected,	//连接已经断开
	E_connecting,	//连接中
	E_connected,	//连接成功
	E_authing,		//5.授权中
	E_authed,		//授权成功
	E_logining,		//登录中
	E_logined,		//登录成功
	E_confirming,	//结算单确认中
	E_confirmed,	//10.已经确认
	E_conn_max		//最大值
};

/*! 买卖方向 */
enum wdDirectionType
{
	E_Direction_Default = -1, // 净持仓？？
	E_Buy,			/*!< 买 */ 
	E_Sell,			/*!< 卖 */ 
};

/*! 开平标志类型 
 *	上期所区分昨仓和今仓: 平昨仓THOST_FTDC_OFEN_Close; 平今仓THOST_FTDC_OFEN_CloseToday
 *	其他交易所不区分昨仓和今仓: THOST_FTDC_OFEN_Close
 */
enum wdOffsetFlagType
{
	E_OffsetFlag_Default = -1,
	E_Open,			/*!< 开仓 */ 
	E_Close,		/*!< 上期所平昨仓、其他交易所平仓 */ 
	E_CloseToday	/*!< 上期所平今仓 */ 
};

/*! 交易类型 */
enum wdHedgeFlagType
{
	E_Speculation,	/*!< 投机 */ 
	E_Arbitrage,	/*!< 套利 */ 
	E_Hedge			/*!< 保值 */ 
};

///报单状态 [除了E_PartTradedNotQueueing E_AllTraded E_Canceled 其余均可撤单]
enum wdOrderStatus
{
	E_InsertSubmitted,			//报单已发
	E_CancelSubmitted,			//撤单已发
	E_PartTradedQueueing,		//部分成交(可撤)
	E_PartTradedNotQueueing,	//部分成交(不可撤)
	E_AllTraded,				//全成
	E_Canceled,					//全撤
	E_WaitTrade,				//等待成交(可撤)
	E_Unknown,					//未知	
	E_InsertTrash,				//报单失败
	E_CancelTrash,				//撤单失败
};

/*! 触发单条件类型 */
enum wdContingentConditionType
{
	///立即
	E_Immediately,
	///止损
    E_Touch,
	///止赢
    E_TouchProfit,
	///预埋单
    E_ParkedOrder,
	///最新价大于条件价
    E_LastPriceGreaterThanStopPrice,
	///最新价大于等于条件价
    E_LastPriceGreaterEqualStopPrice,
	///最新价小于条件价
    E_LastPriceLesserThanStopPrice,
	///最新价小于等于条件价
    E_LastPriceLesserEqualStopPrice,
	///卖一价大于条件价
    E_AskPriceGreaterThanStopPrice,
	///卖一价大于等于条件价
    E_AskPriceGreaterEqualStopPrice,
	///卖一价小于条件价
    E_AskPriceLesserThanStopPrice,
	///卖一价小于等于条件价
    E_AskPriceLesserEqualStopPrice,
	///买一价大于条件价
    E_BidPriceGreaterThanStopPrice,
	///买一价大于等于条件价
    E_BidPriceGreaterEqualStopPrice,
	///买一价小于条件价
    E_BidPriceLesserThanStopPrice,
	///买一价小于等于条件价
    E_BidPriceLesserEqualStopPrice
};

#define CPP_FUNCTIONAL
#ifndef CPP_FUNCTIONAL
	//! 连接、断开的响应
	typedef void(__stdcall *fnOnConnect)(wdConnectInfo *);	

	//! Tick数据到来触发的回调类型
	typedef void(__stdcall *fnOnTick)(wdTick *pTick);
	//! K线数据到来触发的回调类型
	typedef void(__stdcall *fnOnKLine)(wdKLine *pKLine);

	//! 交易数据到来触发的回调类型
	typedef void(__stdcall *fnOnPosition)(wdPosition *);
	typedef void(__stdcall *fnOnOrder)(wdOrder *);
	typedef void(__stdcall *fnOnTrade)(wdTradeTicket *);
	
	typedef void(__stdcall *fnOnSettlementInfo)(const char *);
	typedef void(__stdcall *fnOnTradingAccount)(wdTradingAccount *);	
	typedef void(__stdcall *fnOnInstrument)(std::map<std::string, wdInstrument> *);	

	//! 错误信息
	typedef void(__stdcall *fnOnError)(const char *);

#else

	//! 连接、断开的响应
	typedef std::function<void (wdConnectInfo *)> fnOnConnect;

	//! Tick数据到来触发的回调类型
	typedef std::function<void (wdTick *)> fnOnTick;
	//! K线数据到来触发的回调类型
	typedef std::function<void (wdKLine *)> fnOnKLine;

	//! 交易数据到来触发的回调类型
	typedef std::function<void (wdPosition *)> fnOnPosition;	 
	typedef std::function<void (wdOrder *)> fnOnOrder;	 
	typedef std::function<void (wdTradeTicket *)> fnOnTrade;	 	 
		
	typedef std::function<void (const char *)> fnOnSettlementInfo;	
	typedef std::function<void (wdTradingAccount *)> fnOnTradingAccount;	 
	typedef std::function<void (std::map<std::string, wdInstrument> *)> fnOnInstrument;	 

	//! 错误信息
	typedef std::function<void (const char *)> fnOnError;

#endif // !CPP_FUNCTIONAL

	/** 查询SQlite数据库的回调函数 */
	typedef int (*fnOnQuerySQLite)(void*, int,char**, char**);

#endif