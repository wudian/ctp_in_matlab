#ifndef _TRADE_DATA_H_
#define _TRADE_DATA_H_

#include "CTP\ThostFtdcUserApiStruct.h"
#include "Types.h"

enum wdOrderType;

//! 登陆信息
struct QUANTBOX_API wdConnectInfo
{
	wdConnectType type;
	wdConnectionStatus status;
	CThostFtdcRspUserLoginField loginField;
	TThostFtdcErrorMsgType	ErrorMsg;

	wdConnectInfo(wdConnectType t, wdConnectionStatus s, CThostFtdcRspUserLoginField *l = nullptr, TThostFtdcErrorMsgType e = nullptr);
};

//! 资金账户
struct QUANTBOX_API wdTradingAccount
{
	///可用资金
	double FundAvailable; 	
	///平仓盈亏
	double CloseProfit; 
	///持仓盈亏
	double PositionProfit; 
	///手续费
	double Commission; 
	///冻结手续费
	double FrozenCommission; 
	///保证金总额
	double CurrMargin; 
	///冻结的保证金
	double FrozenMargin; 
	///入金金额
	double Deposit; 
	///出金金额
	double Withdraw; 
	///上日权益
	double PreEquity; 
	///今日动态权益
	double CurrentEquity; 
	///风险率
	double RiskRatio; 

	void update(const CThostFtdcTradingAccountField *pTradingAccount);
};

struct QUANTBOX_API wdOrderKey
{
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;

	wdOrderKey() { memset(this, 0, sizeof(wdOrderKey));}
	wdOrderKey(TThostFtdcFrontIDType, TThostFtdcSessionIDType, const TThostFtdcOrderRefType);
	wdOrderKey(char **values); // 从数据库数据构造报单键值
	wdOrderKey(const wdOrderKey &other);
	wdOrderKey &operator=(const wdOrderKey &other);
	bool operator<(const wdOrderKey &other) const ;
};

//! 报单
struct QUANTBOX_API wdOrder
{
	///前置编号
	TThostFtdcFrontIDType		FrontID;
	///会话编号
	TThostFtdcSessionIDType		SessionID;
	///报单引用
	TThostFtdcOrderRefType		OrderRef;

	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;	
	///报单类型
	wdOrderType					Type;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///买卖
	wdDirectionType				Dir;
	///开平
	wdOffsetFlagType			Offset;
	///状态
	wdOrderStatus				Status;
	///报单价格
	double						Price; 
	///报单手数
	int							Hands;	
	///未成交手数
	int							AvaHands;
	///成交手数
	int							TradedHands;
	///委托时间
	TThostFtdcTimeType			InsertTime;
	///状态信息
	TThostFtdcErrorMsgType		StatusMsg;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;

	wdOrder() { memset(this, 0, sizeof(wdOrder));}
	wdOrder(char **values); // 从数据库数据构造报单
	wdOrder &update(const CThostFtdcInputOrderField *, wdOrderStatus, const char *);
	wdOrder &update(const CThostFtdcOrderField *);
	wdOrder &update(const CThostFtdcInputOrderActionField *, const char *);
	wdOrder &update(const CThostFtdcOrderActionField *, const char *);
	operator CThostFtdcInputOrderActionField();
};

//! 成交单
struct QUANTBOX_API wdTradeTicket
{
	///成交编号
	TThostFtdcTradeIDType		TradeID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///买卖
	wdDirectionType				Dir;
	///开平
	wdOffsetFlagType			Offset;
	///成交均价
	double						Price; 
	///成交量
	int							Hands;	
	///成交类型
	TThostFtdcTradeTypeType		TradeType;
	///成交时间
	TThostFtdcTimeType			TradeTime;	
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///投机套保标志
	TThostFtdcHedgeFlagType		HedgeFlag;

	wdTradeTicket() { memset(this, 0, sizeof(wdTradeTicket));}
	wdTradeTicket &update(const CThostFtdcTradeField *pTrade);
};

struct QUANTBOX_API wdPositionKey
{
	///合约号
	TThostFtdcInstrumentIDType	InstrumentID;
	///多空
	wdDirectionType				Dir;

	wdPositionKey() { memset(this, 0, sizeof(wdPositionKey));}
	wdPositionKey(const TThostFtdcInstrumentIDType inst, TThostFtdcDirectionType d);
	bool operator<(const wdPositionKey &other) const;
};

//! 持仓 
struct QUANTBOX_API wdPosition
{
	///合约号
	TThostFtdcInstrumentIDType	InstrumentID;
	///多空
	wdDirectionType				Dir;

	///总仓
	int		TPos; 
	///可用仓
	int		APos; 
	///开仓均价
	double	PosAvgPrice; 
	
	wdPosition() { memset(this, 0, sizeof(wdPosition));}
	void update(const CThostFtdcTradeField *pTrade); 
	void update(const CThostFtdcInvestorPositionField *);
};

//! 涨跌停板
struct QUANTBOX_API wdLimitPrice
{
	///涨停价
	double	UpperLimitPrice;
	///跌停价
	double	LowerLimitPrice;

	wdLimitPrice(double UpperLimitPrice = 0., double LowerLimitPrice = 0.);
};
//! 合约信息
struct QUANTBOX_API wdInstrument
{
	///产品代码
	TThostFtdcInstrumentIDType	ProductID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TThostFtdcInstrumentNameType	InstrumentName;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///合约数量乘数
	TThostFtdcVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TThostFtdcPriceType	PriceTick;
	///产品类型
	TThostFtdcProductClassType	ProductClass;
	///到期日
	TThostFtdcDateType	ExpireDate;
	///多头保证金率
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///空头保证金率
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///开仓手续费率
	TThostFtdcRatioType	OpenRatioByMoney;
	///平仓手续费率
	TThostFtdcRatioType	CloseRatioByMoney;
	///平今手续费率
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///合约交易状态
	TThostFtdcInstrumentStatusType	InstrumentStatus;
	wdLimitPrice				LimitPrice;

	wdInstrument() { memset(this, 0, sizeof(wdInstrument));}
	void update(const CThostFtdcInstrumentField *);
	void update(const CThostFtdcInstrumentMarginRateField *);
	void update(const CThostFtdcInstrumentCommissionRateField *);
	void update(const CThostFtdcInstrumentStatusField *);
	void update(const CThostFtdcDepthMarketDataField *);
};


#endif