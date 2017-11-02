//////////////////////////////////////////////////////////////////
///@system 东航资管C++量化交易接口
///@company 东航金控
///@file QuantBoxApi.h  
///@brief 定义了量化平台客户端的C风格的接口和各个数据结构,实现订阅行情、下单、撤单等功能
///@20140915 吴典	创建该文件
/*! \section sec_example 简单例子
	\code
	//1、注册回调函数
	//2、连接CTP的行情前端与交易前端
	//3、订阅行情、编写策略，在行情回调中执行策略，根据交易信号调用下单、撤单接口
	//4、断开CTP的行情前端、交易前端，程序退出
	\endcode
 */
//////////////////////////////////////////////////////////////////

#ifndef _QUANT_BOX_API_H_
#define _QUANT_BOX_API_H_

#include <vector>
#include <map>
#include <string>
#include "MarketData.h"
#include "TradeData.h"

QUANTBOX_API extern std::string			g_mdDBPath;
QUANTBOX_API extern std::string			g_tdDBPath;
QUANTBOX_API extern const char			*g_Table_Order;
QUANTBOX_API extern const char			*g_Table_Trade;
QUANTBOX_API extern const char			*g_Table_Position;
//#ifdef __cplusplus
//extern "C" {
//#endif

/*!	\brief 行情接口 ***********************************************************************************/


/*!	\brief 连接CTP的行情前端	关于服务器的ip、port、user、passwd等 见 ConfigFile.xml */
QUANTBOX_API void __stdcall MD_Connect();

/*!	\brief 订阅行情
	\param Instruments 合约列表，用","隔开，"IF1409,IF1410"
	\param period 周期，用","隔开,"tick,3s,6m,8m,1h"
	\n\n函数使用范例：
	\code
	//订阅IF1410和IF1411的tick数据、3s数据、1m数据
	MD_Subscribe("IF1410,IF1411", "tick,3s,1m");
	\endcode
*/
QUANTBOX_API void __stdcall MD_Subscribe(const char *Instruments, const char *period = "tick");

/*!	\brief 取消行情
	\param Instruments 合约列表，用","隔开，"IF1409,IF1410"
	\param period 周期，用","隔开,"tick,3s,6m,8m,1h"
	\n\n函数使用范例：
	\code
	//取消IF1410和IF1411的tick数据、3s数据、1m数据
	MD_Unsubscribe("IF1410,IF1411", "tick,3s,1m");
	//取消所有合约的行情
	MD_Subscribe();
	\endcode
*/
QUANTBOX_API void __stdcall MD_Unsubscribe(const char *Instruments = "all", const char *period = "all");

/*!	\brief 订阅历史数据	
	\param beginTime 开始时间 "20140910-09:30:00.000"
	\param endTime 结束时间 "20140910-15:30:00.000"
	\param Instruments 合约列表，用","隔开，"IF1409,IF1410"
	\param period 周期，用","隔开,"tick,3s,6m,8m,1h"
	\n\n函数使用范例：
	\code
	//订阅 IF1409从"20140910-09:30:00.000"到"20140910-15:30:00.000"的tick和4s的历史数据
	MD_SubscribeHistory("20140910-09:30:00.000", "20140910-15:30:00.000", "IF1409", "tick,4s");
	\endcode
*/
QUANTBOX_API void __stdcall MD_SubscribeHistory(const char *beginTime, const char *endTime, const char *Instruments, const char *period = "tick");

/*!	\brief 断开CTP的行情前端 */
QUANTBOX_API void __stdcall MD_Disconnect();

/*!	\brief 获取某个合约的最新的tick
	\param Instrument 合约名
	\param isHistory 是否订阅的历史数据
	\return 最新tick
	\n\n函数使用范例：
	\code
	//获取IF1410最新的tick
	wdTick tick = GetLastTick("IF1410");
	\endcode
*/
QUANTBOX_API wdTick __stdcall GetLastTick(const char *Instrument, bool isHistory = false);

/*!	\brief 获取某个合约的最新的一些tick数据
	\param Instrument 合约名
	\param Num 多少个数据
	\param isHistory 是否订阅的历史数据
	\return vecLastTicks 存放数据的容器，最新的tick放在第一个，上一个tick放在容器的第二个位置...
	\n\n函数使用范例：
	\code
	//获取IF1410最新的10个tick
	std::vector<wdTick> vecLastTicks;
	GetLastTick("IF1410", 10, vecLastTicks);	
	\endcode
*/
QUANTBOX_API void __stdcall GetLastTick(const char *Instrument, int Num, std::vector<wdTick> &vecLastTicks, bool isHistory = false);

/*!	\brief 获取某个合约的某个周期的最新的K线
	\param Instrument 合约名
	\param period 周期
	\param isHistory 是否订阅的历史数据
	\return 最新K线
	\n\n函数使用范例：
	\code
	//获取IF1410最新的1m K线。前提是订阅了IF1410的1m K线
	wdKLine kline = GetLastKLine("IF1410", "1m");
	\endcode
*/
QUANTBOX_API wdKLine __stdcall GetLastKLine(const char *Instrument, const char *period, bool isHistory = false);

/*!	\brief 获取某个合约的某个周期的最新的一些K线
	\param Instrument 合约名
	\param period 周期
	\param Num 多少个数据
	\param isHistory 是否订阅的历史数据	
	\return vecLastKLines 存放K线的容器
	\n\n函数使用范例：
	\code
	//获取IF1410最新的30根 5sK线。前提是订阅了IF1410的5s K线
	std::vector<wdKLine> vecLastKLines;
	GetLastKLine("IF1410", "5s", 30, vecLastKLines);
	\endcode
*/
QUANTBOX_API void __stdcall GetLastKLine(const char *Instrument, const char *period, int Num, std::vector<wdKLine> &vecLastKLines, bool isHistory = false);

/*!	\brief 获取所有合约的信息
	\return vecInsts 合约详细
*/
QUANTBOX_API void __stdcall GetInstrument(std::vector<wdInstrument> &vecInsts);

/*!	\brief 获取某个账户的信息
	\param AccountID 账号ID
	\return 账号信息
*/
QUANTBOX_API wdTradingAccount __stdcall GetTradingAccount(const char *AccountID);



/*!	\brief 交易接口 ***********************************************************************************/

/*!	\brief 连接CTP交易前端 */
QUANTBOX_API void __stdcall TD_Connect();

/*!	\brief 报单-限价
	\param Instrument 合约名
	\param Price 价格
	\param Volume 数量
	\param Direction 买卖方向
	\param OffsetFlag 开平标志
	\n\n函数使用范例：
	\code
	//以3000点的价格买开1手IF1410
	TD_SendLimitOrder("IF1410", 3000., 1, E_Buy, E_Open);
	\endcode
*/
QUANTBOX_API void __stdcall TD_SendLimitOrder(const char *Instrument, double Price, int Volume,	wdDirectionType Direction, wdOffsetFlagType OffsetFlag);

/*!	\brief 报单-市价
	\param Instrument 合约名
	\param Volume 数量
	\param Direction 买卖方向
	\param OffsetFlag 开平标志
	\n\n函数使用范例：
	\code
	//以市价买开1手IF1410
	TD_SendMarketOrder("IF1410", 1, E_Buy, E_Open);
	\endcode
*/
QUANTBOX_API void __stdcall TD_SendMarketOrder(const char *Instrument, int Volume, wdDirectionType Direction, wdOffsetFlagType OffsetFlag);

/*!	\brief 报单-触发单
	\param Instrument 合约名
	\param Price 价格
	\param Volume 数量
	\param Direction 买卖方向
	\param OffsetFlag 开平标志
	\param ContingentCondition 触发条件
	\param StopPrice 止损价
*/
QUANTBOX_API void __stdcall TD_SendContingentOrder(const char *Instrument, double Price, int Volume, wdDirectionType Direction, wdOffsetFlagType OffsetFlag,
												   wdContingentConditionType ContingentCondition, double StopPrice);

/*!	\brief 撤单
	\param Instrument 合约名
	\param Direction 买卖方向
	\param OffsetFlag 开平标志
	\n\n函数使用范例：
	\code
	//撤销IF1410的买开单
	TD_CancelOrder("IF1410", E_Buy, E_Open);
	\endcode
*/
QUANTBOX_API void __stdcall TD_CancelOrder(const char *Instrument, wdDirectionType Direction = E_Direction_Default, wdOffsetFlagType OffsetFlag = E_OffsetFlag_Default);
QUANTBOX_API void __stdcall TD_CancelOrder(const wdOrder &);

/*!	\brief 查持仓
	\param Instrument 合约名,为""查所有
*/
QUANTBOX_API void __stdcall TD_ReqQryInvestorPosition(const char *Instrument = nullptr);

/*!	\brief 查合约
	\param Instrument 合约名
*/
QUANTBOX_API void __stdcall TD_ReqQryInstrument(const char *Instrument = nullptr);

/*!	\brief 查手续费
	\param Instrument 合约名
*/
QUANTBOX_API void __stdcall TD_ReqQryInstrumentCommissionRate(const char *Instrument = nullptr);

/*!	\brief 查保证金
	\param Instrument 合约名
*/
QUANTBOX_API void __stdcall TD_ReqQryInstrumentMarginRate(const char *Instrument = nullptr);

/*!	\brief 请求查询投资者结算结果
	\param TradingDay 交易日，例如"20140912"
*/
QUANTBOX_API void __stdcall TD_ReqQrySettlementInfo(const char *TradingDay);

/*!	\brief 查委托
	\param Instrument 合约名
*/
QUANTBOX_API void __stdcall TD_ReqQryOrder(const char *Instrument = nullptr);

/*!	\brief 查成交
	\param Instrument 合约名
*/
QUANTBOX_API void __stdcall TD_ReqQryTrade(const char *Instrument = nullptr);

/*!	\brief 断开连接 */
QUANTBOX_API void __stdcall TD_Disconnect();


QUANTBOX_API void __stdcall CTP_RegOnConnect(fnOnConnect);
QUANTBOX_API void __stdcall CTP_RegOnRspError(fnOnError);

/*!	\brief 注册行情回调 ***********************************************************************************/
QUANTBOX_API void __stdcall CTP_RegOnRtnDepthMarketData_Tick(fnOnTick);
QUANTBOX_API void __stdcall CTP_RegOnRtnDepthMarketData_KLine(fnOnKLine);
QUANTBOX_API void __stdcall CTP_RegOnHistory_Tick(fnOnTick);
QUANTBOX_API void __stdcall CTP_RegOnHistory_KLine(fnOnKLine);

/*!	\brief 注册交易回调 ***********************************************************************************/
QUANTBOX_API void __stdcall CTP_RegOnRspQryInstrument(fnOnInstrument);
QUANTBOX_API void __stdcall CTP_RegOnRspQryInvestorPosition(fnOnPosition);
QUANTBOX_API void __stdcall CTP_RegOnRspQryOrder(fnOnOrder);
QUANTBOX_API void __stdcall CTP_RegOnRspQryTrade(fnOnTrade);
QUANTBOX_API void __stdcall CTP_RegOnRspQrySettlementInfo(fnOnSettlementInfo);

//#ifdef __cplusplus
//}
//#endif


#endif