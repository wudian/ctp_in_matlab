#ifndef _ENUMS_H_
#define _ENUMS_H_

/*! 交易类型分类 */
enum wdTradeType
{
	E_Simulate,				/*!< 模拟盘 */ 
	E_Actual				/*!< 实盘 */ 
};

/*! 系统类型分类 */
enum wdSystemType 
{
	E_RealtimeMarketData,	/*!< 实时行情 */  
	E_HistoryMarketData,	/*!< 历史行情 */  
	E_TradeData				/*!< 交易部分 */  
};

/*! 报单类型 */
enum wdOrderType
{
	E_Limit,				/*!< 限价单 */ 
	E_Market,				/*!< 市价单 */ 
	E_Contingent,			/*!< 触发单 */ 
	E_Trash					/*!< 废单 */ 
};



#endif