#ifndef _GLOBAL_VARS_H_
#define _GLOBAL_VARS_H_

extern CThostFtdcRspUserLoginField			g_RspUserLogin;			//返回的登录成功响应，目前利用此内成员进行报单所属区分

extern wdTradeType							g_tradeType;
extern my_severity_level					g_severityLevel;
extern std::string							g_trader_no;			//如果是"00",表明不支持分账户;否则子账号的值的范围是"01"~"99"								

// 行情
extern std::string							g_mdAddress;
extern std::string							g_mdBrokerID;
extern std::string							g_mdInstrumentAssemble;	//合约的组合。每个组合之间用分号";"隔开，组合内的合约用逗号","隔开
// 交易
extern std::string							g_tdAddress;
extern std::string							g_tdBrokerID;
extern std::string							g_tdInvestorId;			//投资者ID
extern std::string							g_tdPassword;			//密码
extern std::string							g_tdUserProductInfo;	//产品信息
extern std::string							g_tdAuthCode;			//认证码
extern THOST_TE_RESUME_TYPE					g_resumeType;
//数据库
extern std::string							g_Database;
QUANTBOX_API extern std::string				g_mdDBPath;
QUANTBOX_API extern std::string				g_tdDBPath;
QUANTBOX_API extern const char				*g_Table_Order;
QUANTBOX_API extern const char				*g_Table_Trade ;
QUANTBOX_API extern const char				*g_Table_Position ;
// mysql
extern std::string							g_mysqlHost;
extern std::string							g_mysqlUser;
extern std::string							g_mysqlPassword;

 
extern fnOnConnect							g_fnOnMdConnect;

extern fnOnTick								g_fnOnRtnDepthMarketData_Tick;
extern fnOnKLine							g_fnOnRtnDepthMarketData_KLine;
extern fnOnTick								g_fnOnHistory_Tick;
extern fnOnKLine							g_fnOnHistory_KLine;

extern fnOnPosition							g_fnOnRspQryInvestorPosition;
extern fnOnOrder							g_fnOnRspQryOrder;
extern fnOnTrade							g_fnOnRspQryTrade;

extern fnOnSettlementInfo					g_fnOnRspQrySettlementInfo;
extern fnOnTradingAccount					g_fnOnTradingAccount;
extern fnOnInstrument						g_fnOnRspQryInstrument;

extern fnOnError							g_fnOnMdRspError;

#endif // !_GLOBAL_VARS_H_


