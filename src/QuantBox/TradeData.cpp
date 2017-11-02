
#include "TradeData.h"
#include <string.h>
#include <boost/algorithm/string.hpp>
#include "CTPTdApi.h"
#include "Enums.h"
#include "logger.h"
#include "defines.h"
#include "toolkit.h"

extern CThostFtdcRspUserLoginField			g_RspUserLogin;

wdConnectInfo::wdConnectInfo(wdConnectType t, wdConnectionStatus s, CThostFtdcRspUserLoginField *l, TThostFtdcErrorMsgType e)
	: type(t)
	, status(s)
{
	if (l)
		loginField = *l;
	if (e)
		strcpy_s(ErrorMsg, e);
}

void wdTradingAccount::update(const CThostFtdcTradingAccountField *pTradingAccount)
{
	CloseProfit = pTradingAccount->CloseProfit;
	PositionProfit = pTradingAccount->PositionProfit;
	Commission = pTradingAccount->Commission;
	FrozenCommission = pTradingAccount->FrozenCommission;
	CurrMargin = pTradingAccount->CurrMargin;
	FrozenMargin = pTradingAccount->FrozenMargin;
	Deposit = pTradingAccount->Deposit;
	Withdraw = pTradingAccount->Withdraw;
	PreEquity = pTradingAccount->PreBalance;
	//静态权益=上日结算准备金（上日权益）-出金金额+入金金额
	//double sEquity = pTradingAccount->PreBalance - pTradingAccount->Withdraw + pTradingAccount->Deposit;
	//静态权益=上日结算准备金（上日权益）-上次信用额度-上次质押金额+质押金额-今日出金+今日入金
	double sEquity = pTradingAccount->PreBalance - pTradingAccount->PreCredit - pTradingAccount->PreMortgage + pTradingAccount->Mortgage - pTradingAccount->Withdraw + pTradingAccount->Deposit;
	//动态权益=静态权益+ 平仓盈亏+ 持仓盈亏- 手续费
	CurrentEquity = sEquity + pTradingAccount->CloseProfit + pTradingAccount->PositionProfit - pTradingAccount->Commission;
	//风险率 = 保证金 / 今日动态权益
	RiskRatio = pTradingAccount->CurrMargin / CurrentEquity;
	//可用资金=动态权益-占用保证金-冻结保证金-冻结手续费-交割保证金+信用金额
	double _FundAvailable = CurrentEquity - pTradingAccount->CurrMargin - pTradingAccount->FrozenMargin - pTradingAccount->FrozenCommission - pTradingAccount->DeliveryMargin + pTradingAccount->Credit;
	FundAvailable = pTradingAccount->Available;
	if (_FundAvailable != FundAvailable)
		LOG_ERROR << "可用资金计算有问题！";
}

wdOrderKey::wdOrderKey(TThostFtdcFrontIDType f, TThostFtdcSessionIDType s, const TThostFtdcOrderRefType o)
	: FrontID(f)
	, SessionID(s)
{
	strcpy_s(OrderRef, o);
}

wdOrderKey::wdOrderKey(char **values)
	: FrontID(atoi(values[0]))
	, SessionID(atoi(values[1]))
{
	strcpy_s(OrderRef, values[2]);
}

wdOrderKey::wdOrderKey(const wdOrderKey &other)
{
	FrontID = other.FrontID;
	SessionID = other.SessionID;
	strcpy_s(OrderRef, other.OrderRef);
}

wdOrderKey &wdOrderKey::operator=(const wdOrderKey &other)
{
	FrontID = other.FrontID;
	SessionID = other.SessionID;
	strcpy_s(OrderRef, other.OrderRef);
	return *this;
}

bool wdOrderKey::operator<(const wdOrderKey &other) const
{
	if (FrontID == other.FrontID) {
		if (SessionID == other.SessionID)
			return strcmp(OrderRef, other.OrderRef) < 0;
		else
			return SessionID < other.SessionID;
	}
	else
		return FrontID < other.FrontID;
}

//wdOrder::wdOrder(TThostFtdcFrontIDType fid, TThostFtdcSessionIDType sid, const TThostFtdcOrderRefType or, wdOrderType ot, const TThostFtdcInstrumentIDType id, double p, int v, wdDirectionType d, wdOffsetFlagType o, wdOrderStatus s, const TThostFtdcTimeType time, const TThostFtdcErrorMsgType errMsg)
//	: FrontID(fid)
//	, SessionID(sid)
//	, Type(ot)
//	, Price(p)
//	, Hands(v)
//	, AvaHands(v)
//	, Dir(d)
//	, Offset(o)
//	, Status(s)
//{
//	strcpy_s(OrderRef, or);
//	strcpy_s(InstrumentID, id);
//	strcpy_s(StatusMsg, errMsg);
//	strcpy_s(InsertTime, time);
//}

wdOrder::wdOrder(char **values)
	: FrontID(atoi(values[0]))
	, SessionID(atoi(values[1]))
	, Type((wdOrderType)atoi(values[4]))
	, Dir((wdDirectionType)atoi(values[6]))
	, Offset((wdOffsetFlagType)atoi(values[7]))
	, Status((wdOrderStatus)atoi(values[8]))
	, Price(atof(values[9]))
	, Hands(atoi(values[10]))
	, AvaHands(atoi(values[11]))
	, TradedHands(atoi(values[12]))
{
	strcpy_s(OrderRef, values[2]);
	strcpy_s(OrderSysID, values[3]);
	strcpy_s(InstrumentID, values[5]);
	strcpy_s(InsertTime, values[13]);
	strcpy_s(StatusMsg, values[14]);
	strcpy_s(ExchangeID, values[15]);
}

wdOrder &wdOrder::update(const CThostFtdcInputOrderField *pInputOrder, wdOrderStatus s, const char *errMsg)
{
	if (s == E_InsertSubmitted) {
		FrontID = g_RspUserLogin.FrontID;
		SessionID = g_RspUserLogin.SessionID;
		strcpy_s(OrderRef, pInputOrder->OrderRef);
	}

	strcpy_s(InstrumentID, pInputOrder->InstrumentID);
	Dir = (pInputOrder->Direction == THOST_FTDC_D_Buy ? E_Buy : E_Sell);
	if (boost::equals(pInputOrder->CombOffsetFlag, "0")) { //Open
		Offset = E_Open;
	}
	else if (boost::equals(pInputOrder->CombOffsetFlag, "1")) { //Close
		Offset = E_Close;
	}
	else if (boost::equals(pInputOrder->CombOffsetFlag, "3")) { //CloseToday
		Offset = E_CloseToday;
	}
	Status = s;
	if (s == E_InsertTrash || s == E_Unknown)
		Type = E_Trash;
	Price = pInputOrder->LimitPrice;
	Hands = pInputOrder->VolumeTotalOriginal;
	AvaHands = Hands;
	TradedHands = 0;
	strcpy_s(InsertTime, GetLocalTime().c_str());
	strcpy_s(StatusMsg, errMsg);
	
	return *this;
}

wdOrder &wdOrder::update(const CThostFtdcOrderField *pOrder)
{
	FrontID = pOrder->FrontID;
	SessionID = pOrder->SessionID;
	strcpy_s(OrderRef, pOrder->OrderRef);

	strcpy_s(OrderSysID, pOrder->OrderSysID);
	strcpy_s(InstrumentID, pOrder->InstrumentID);
	Dir = (pOrder->Direction == THOST_FTDC_D_Buy ? E_Buy : E_Sell);
	if (boost::equals(pOrder->CombOffsetFlag, "0")) { //Open
		Offset = E_Open;
	}
	else if (boost::equals(pOrder->CombOffsetFlag, "1")) { //Close
		Offset = E_Close;
	}
	else if (boost::equals(pOrder->CombOffsetFlag, "3")) { //CloseToday
		Offset = E_CloseToday;
	}

	switch (pOrder->OrderStatus)
	{
	case THOST_FTDC_OST_AllTraded:
		Status = E_AllTraded;
		break;
	case THOST_FTDC_OST_PartTradedQueueing:
		Status = E_PartTradedQueueing;
		break;
	case THOST_FTDC_OST_PartTradedNotQueueing:
		Status = E_PartTradedNotQueueing;
		break;
	case THOST_FTDC_OST_Canceled:
		Status = E_Canceled;
		break;
	case THOST_FTDC_OST_NoTradeQueueing:
	case THOST_FTDC_OST_NoTradeNotQueueing:
		Status = E_WaitTrade;
		break;
	default:
		{
			switch (pOrder->OrderSubmitStatus)
			{
			case THOST_FTDC_OSS_InsertSubmitted:
				Status = E_InsertSubmitted;
				break;
			case THOST_FTDC_OSS_CancelSubmitted:
				Status = E_CancelSubmitted;
				break;
			case THOST_FTDC_OSS_InsertRejected:
				{
					Status = E_InsertTrash;
					Type = E_Trash;
				}
				break;
			case THOST_FTDC_OSS_CancelRejected:
				{
					Status = E_CancelTrash;
				}
				break;
			default:
				{
					Status = E_Unknown;
					Type = E_Trash;
				}
				break;
			}
		}
		break;
	}

	Price = pOrder->LimitPrice;
	Hands = pOrder->VolumeTotalOriginal;
	AvaHands = pOrder->VolumeTotal;
	TradedHands = pOrder->VolumeTraded;	
	strcpy_s(InsertTime, pOrder->InsertTime);
	strcpy_s(StatusMsg, pOrder->StatusMsg);
	strcpy_s(ExchangeID, pOrder->ExchangeID);

	return *this;
}

wdOrder &wdOrder::update(const CThostFtdcInputOrderActionField *orderAction, const char *errMsg)
{
	Status = E_CancelTrash;
	strcpy_s(InsertTime, GetLocalTime().c_str());
	strcpy_s(StatusMsg, errMsg);
	return *this;
}

wdOrder &wdOrder::update(const CThostFtdcOrderActionField *orderAction, const char *errMsg)
{
	Status = E_CancelTrash;
	strcpy_s(InsertTime, orderAction->ActionTime);
	strcpy_s(StatusMsg, errMsg);
	return *this;
}

wdOrder::operator CThostFtdcInputOrderActionField()
{
	CThostFtdcInputOrderActionField InputOrderActionField = {0};
	///经纪公司代码
	strcpy_s(InputOrderActionField.BrokerID, g_RspUserLogin.BrokerID);
	///投资者代码
	strcpy_s(InputOrderActionField.InvestorID, g_RspUserLogin.UserID);
	///报单引用 大商所、郑商所在报单未到达交易所时，OrderRef撤单会失败
	strcpy_s(InputOrderActionField.OrderRef, OrderRef);
	///前置编号
	InputOrderActionField.FrontID = FrontID;
	///会话编号
	InputOrderActionField.SessionID = SessionID;
	///交易所代码
	strcpy_s(InputOrderActionField.ExchangeID, ExchangeID);
	///报单编号
	strcpy_s(InputOrderActionField.OrderSysID, OrderSysID);
	///操作标志
	InputOrderActionField.ActionFlag = THOST_FTDC_AF_Delete;
	///合约代码
	strcpy_s(InputOrderActionField.InstrumentID, InstrumentID);
	return InputOrderActionField;
}

wdTradeTicket &wdTradeTicket::update(const CThostFtdcTradeField *pTrade)
{
	strcpy_s(TradeID, pTrade->TradeID);
	strcpy_s(OrderSysID, pTrade->OrderSysID);
	strcpy_s(InstrumentID, pTrade->InstrumentID);
	Dir = (pTrade->Direction == THOST_FTDC_D_Buy ? E_Buy : E_Sell);
	if (pTrade->OffsetFlag == THOST_FTDC_OF_Open) //Open
		Offset = E_Open;
	else if (pTrade->OffsetFlag == THOST_FTDC_OF_Close) //Close
		Offset = E_Close;
	else if (pTrade->OffsetFlag == THOST_FTDC_OF_CloseToday) //CloseToday
		Offset = E_CloseToday;

	Price = pTrade->Price;
	Hands = pTrade->Volume;
	TradeType = pTrade->TradeType;
	strcpy_s(TradeTime, pTrade->TradeTime);
	strcpy_s(ExchangeID, pTrade->ExchangeID);
	HedgeFlag = pTrade->HedgeFlag;

	return *this;
}

wdPositionKey::wdPositionKey(const TThostFtdcInstrumentIDType inst, TThostFtdcDirectionType d)
{
	strcpy_s(InstrumentID, inst);
	Dir = (d == THOST_FTDC_D_Buy ? E_Buy : E_Sell);
}

bool wdPositionKey::operator<(const wdPositionKey &other) const
{
	int i;
	if ((i = strcmp(InstrumentID, other.InstrumentID)) == 0) {
		return Dir < other.Dir;
	}
	else {
		return i < 0;
	}
}

void wdPosition::update(const CThostFtdcTradeField *pTrade)
{
	strcpy_s(InstrumentID, pTrade->InstrumentID);
	Dir = (pTrade->Direction == THOST_FTDC_D_Buy ? E_Buy : E_Sell);

	switch (pTrade->OffsetFlag)
	{
	case THOST_FTDC_OF_Open:
		PosAvgPrice = (PosAvgPrice * TPos + pTrade->Price * pTrade->Volume) / (TPos + pTrade->Volume);
		TPos += pTrade->Volume;
		break;
	case THOST_FTDC_OF_Close:
	case THOST_FTDC_OF_CloseToday:
		PosAvgPrice = (PosAvgPrice * TPos - pTrade->Price * pTrade->Volume) / (TPos - pTrade->Volume);
		TPos -= pTrade->Volume;
	default:
		break;
	}
}

void wdPosition::update(const CThostFtdcInvestorPositionField *posi)
{
	strcpy_s(InstrumentID, posi->InstrumentID);
	Dir = (posi->PosiDirection == THOST_FTDC_PD_Long ? E_Buy : E_Sell);

	int volumeMulti = CCTPTdApi::instance()->GetVolumeMultiple(posi->InstrumentID);
	
	// By《综合交易平台API开发FAQ 9/14》:总持仓=当前时候的昨持仓+今持仓
	TPos = posi->Position;
	APos = posi->Position - posi->ShortFrozen;
	//OPos = posi->YdPosition;
	//NPos = posi->TodayPosition;
	PosAvgPrice = posi->PositionCost / (volumeMulti>0?volumeMulti:1);
}

wdLimitPrice::wdLimitPrice(double UpperLimitPrice, double LowerLimitPrice)
{
	this->UpperLimitPrice = UpperLimitPrice;
	this->LowerLimitPrice = LowerLimitPrice;
}

void wdInstrument::update(const CThostFtdcInstrumentField *inst)
{
	strcpy_s(ProductID, inst->ProductID);
	strcpy_s(InstrumentID, inst->InstrumentID);
	strcpy_s(InstrumentName, inst->InstrumentName);
	strcpy_s(ExchangeID, inst->ExchangeID);
	VolumeMultiple = inst->VolumeMultiple;
	PriceTick = inst->PriceTick;
	ProductClass = inst->ProductClass;
	strcpy_s(ExpireDate, inst->ExpireDate);
}

void wdInstrument::update(const CThostFtdcInstrumentMarginRateField *marginRate)
{
	LongMarginRatioByMoney = marginRate->LongMarginRatioByMoney;
	ShortMarginRatioByMoney = marginRate->ShortMarginRatioByMoney;
}

void wdInstrument::update(const CThostFtdcInstrumentCommissionRateField *commi)
{
	OpenRatioByMoney = commi->OpenRatioByMoney;
	CloseRatioByMoney = commi->CloseRatioByMoney;
}

void wdInstrument::update(const CThostFtdcInstrumentStatusField *status)
{
	InstrumentStatus = status->InstrumentStatus;
}

void wdInstrument::update(const CThostFtdcDepthMarketDataField *dept)
{
	LimitPrice.UpperLimitPrice = dept->UpperLimitPrice;
	LimitPrice.LowerLimitPrice = dept->LowerLimitPrice;
}