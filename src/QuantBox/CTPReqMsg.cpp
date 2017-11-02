
#include "CTPReqMsg.h"
#include <string.h>
#include <stdio.h>
#include "Enums.h"
#include "logger.h"
#include "CTP/ThostFtdcUserApiStruct.h"
#include "GlobalVars.h"

CCTPReqMsgItem::CCTPReqMsgItem(E_CTPReqType type)
	: m_type(type)
	, InputOrderField(nullptr)
{
	switch (m_type)
	{
	case E_InputOrderField:
		{
			InputOrderField = new CThostFtdcInputOrderField;
			memset(InputOrderField, 0, sizeof(CThostFtdcInputOrderField));
		}
		break;
	case E_InputOrderActionField:
		{
			InputOrderActionField = new CThostFtdcInputOrderActionField;
			memset(InputOrderActionField, 0, sizeof(CThostFtdcInputOrderActionField));
		}
		break;
	case E_InputQuoteField:
		{
			InputQuoteField = new CThostFtdcInputQuoteField;
			memset(InputQuoteField, 0, sizeof(CThostFtdcInputQuoteField));
		}
		break;
	case E_InputQuoteActionField:
		{
			InputQuoteActionField = new CThostFtdcInputQuoteActionField;
			memset(InputQuoteActionField, 0, sizeof(CThostFtdcInputQuoteActionField));
		}		
		break;
	case E_ReqAuthenticateField:
		{
			ReqAuthenticateField = new CThostFtdcReqAuthenticateField;
			memset(ReqAuthenticateField, 0, sizeof(CThostFtdcReqAuthenticateField));
		}
		break;
	case E_ReqUserLoginField:
		{
			ReqUserLoginField = new CThostFtdcReqUserLoginField;
			memset(ReqUserLoginField, 0, sizeof(CThostFtdcReqUserLoginField));
		}
		break;
	case E_SettlementInfoConfirmField:
		{
			QrySettlementInfoConfirmField = new CThostFtdcQrySettlementInfoConfirmField;
			memset(QrySettlementInfoConfirmField, 0, sizeof(CThostFtdcQrySettlementInfoConfirmField));
		}
		break;
	case E_QrySettlementInfoField:
		{
			QrySettlementInfoField = new CThostFtdcQrySettlementInfoField;
			memset(QrySettlementInfoField, 0, sizeof(CThostFtdcQrySettlementInfoField));
		}
		break;
	case E_QrySettlementInfoConfirmField:
		{
			SettlementInfoConfirmField = new CThostFtdcSettlementInfoConfirmField;
			memset(SettlementInfoConfirmField, 0, sizeof(CThostFtdcSettlementInfoConfirmField));
		}
		break;
	case E_QryInstrumentField:
		{
			QryInstrumentField = new CThostFtdcQryInstrumentField;
			memset(QryInstrumentField, 0, sizeof(CThostFtdcQryInstrumentField));
		}
		break;
	case E_QryTradingAccountField:
		{
			QryTradingAccountField = new CThostFtdcQryTradingAccountField;
			memset(QryTradingAccountField, 0, sizeof(CThostFtdcQryTradingAccountField));
		}
		break;
	case E_QryInvestorPositionField:
		{
			QryInvestorPositionField = new CThostFtdcQryInvestorPositionField;
			memset(QryInvestorPositionField, 0, sizeof(CThostFtdcQryInvestorPositionField));
		}
		break;
	case E_QryInvestorPositionDetailField:
		{
			QryInvestorPositionDetailField = new CThostFtdcQryInvestorPositionDetailField;
			memset(QryInvestorPositionDetailField, 0, sizeof(CThostFtdcQryInvestorPositionDetailField));
		}
		break;
	case E_QryInstrumentCommissionRateField:
		{
			QryInstrumentCommissionRateField = new CThostFtdcQryInstrumentCommissionRateField;
			memset(QryInstrumentCommissionRateField, 0, sizeof(CThostFtdcQryInstrumentCommissionRateField));
		}
		break;
	case E_QryInstrumentMarginRateField:
		{
			QryInstrumentMarginRateField = new CThostFtdcQryInstrumentMarginRateField;
			memset(QryInstrumentMarginRateField, 0, sizeof(CThostFtdcQryInstrumentMarginRateField));
		}
		break;
	case E_QryDepthMarketDataField:
		{
			QryDepthMarketDataField = new CThostFtdcQryDepthMarketDataField;
			memset(QryDepthMarketDataField, 0, sizeof(CThostFtdcQryDepthMarketDataField));
		}
		break;
	case E_QryOrder:
		{
			QryOrderField = new CThostFtdcQryOrderField;
			memset(QryOrderField, 0, sizeof(CThostFtdcQryOrderField));
		}
		break;
	case E_QryTrade:
		{
			QryTradeField = new CThostFtdcQryTradeField;
			memset(QryTradeField, 0, sizeof(CThostFtdcQryTradeField));
		}
		break;
	default:
		break;
	}
}


CCTPReqMsgItem::~CCTPReqMsgItem(void)
{
	switch (m_type)
	{
	case E_InputOrderField:
		{
			if (InputOrderField) {
				delete InputOrderField;
				InputOrderField = nullptr;
			}
		}		
		break;
	case E_InputOrderActionField:
		{
			if (InputOrderActionField) {
				delete InputOrderActionField;
				InputOrderActionField = nullptr;
			}
		}	
		break;
	case E_InputQuoteField:
		{
			if (InputQuoteField) {
				delete InputQuoteField;
				InputQuoteField = nullptr;
			}
		}
		break;
	case E_InputQuoteActionField:
		{
			if (InputQuoteActionField) {
				delete InputQuoteActionField;
				InputQuoteActionField = nullptr;
			}
		}
		break;
	case E_ReqAuthenticateField:
		{
			if (ReqAuthenticateField) {
				delete ReqAuthenticateField;
				ReqAuthenticateField = nullptr;
			}
		} 
		break;
	case E_ReqUserLoginField:
		{
			if (ReqUserLoginField) {
				delete ReqUserLoginField;
				ReqUserLoginField = nullptr;
			}
		} 
		break;
	case E_SettlementInfoConfirmField:
		{
			if (SettlementInfoConfirmField) {
				delete SettlementInfoConfirmField;
				SettlementInfoConfirmField = nullptr;
			}
		} 
		break;
	case E_QrySettlementInfoField:
		{
			if (QrySettlementInfoField) {
				delete QrySettlementInfoField;
				QrySettlementInfoField = nullptr;
			}
		} 
		break;
	case E_QrySettlementInfoConfirmField:
		{
			if (SettlementInfoConfirmField) {
				delete SettlementInfoConfirmField;
				SettlementInfoConfirmField = nullptr;
			}
		} 
		break;
	case E_QryInstrumentField:
		{
			if (QryInstrumentField) {
				delete QryInstrumentField;
				QryInstrumentField = nullptr;
			}
		} 
		break;
	case E_QryTradingAccountField:
		{
			if (QryTradingAccountField) {
				delete QryTradingAccountField;
				QryTradingAccountField = nullptr;
			}
		} 
		break;
	case E_QryInvestorPositionField:
		{
			if (QryInvestorPositionField) {
				delete QryInvestorPositionField;
				QryInvestorPositionField = nullptr;
			}
		} 
		break;
	case E_QryInvestorPositionDetailField:
		{
			if (QryInvestorPositionDetailField) {
				delete QryInvestorPositionDetailField;
				QryInvestorPositionDetailField = nullptr;
			}
		} 
		break;
	case E_QryInstrumentCommissionRateField:
		{
			if (QryInstrumentCommissionRateField) {
				delete QryInstrumentCommissionRateField;
				QryInstrumentCommissionRateField = nullptr;
			}
		} 
		break;
	case E_QryInstrumentMarginRateField:
		{
			if (QryInstrumentMarginRateField) {
				delete QryInstrumentMarginRateField;
				QryInstrumentMarginRateField = nullptr;
			}
		} 
		break;
	case E_QryDepthMarketDataField:
		{
			if (QryDepthMarketDataField) {
				delete QryDepthMarketDataField;
				QryDepthMarketDataField = nullptr;
			}
		} 
		break;
	case E_QryOrder:
		{
			if (QryOrderField) {
				delete QryOrderField;
				QryOrderField = nullptr;
			}
		} 
		break;
	case E_QryTrade:
		{
			if (QryTradeField) {
				delete QryTradeField;
				QryTradeField = nullptr;
			}
		} 
		break;
	default:		
		break;
	}
}

//void *CCTPReqMsgItem::GetMsgItem() const
//{
//	switch (m_type)
//	{
//	case E_InputOrderField:
//		return InputOrderField;
//		break;
//	case E_InputOrderActionField:
//		return InputOrderActionField;
//		break;
//	case E_InputQuoteField:
//		return InputQuoteField;
//		break;
//	case E_InputQuoteActionField:
//		return InputQuoteActionField;
//		break;
//	case E_ReqAuthenticateField:
//		return ReqAuthenticateField;
//		break;
//	case E_ReqUserLoginField:
//		return ReqUserLoginField;
//		break;
//	case E_SettlementInfoConfirmField:
//		return SettlementInfoConfirmField;
//		break;
//	case E_QrySettlementInfoField:
//		return QrySettlementInfoField;
//		break;
//	case E_QrySettlementInfoConfirmField:
//		return SettlementInfoConfirmField;
//		break;
//	case E_QryInstrumentField:
//		return QryInstrumentField;
//		break;
//	case E_QryTradingAccountField:
//		return QryTradingAccountField;
//		break;
//	case E_QryInvestorPositionField:
//		return QryInvestorPositionField;
//		break;
//	case E_QryInvestorPositionDetailField:
//		return QryInvestorPositionDetailField;
//		break;
//	case E_QryInstrumentCommissionRateField:
//		return QryInstrumentCommissionRateField;
//		break;
//	case E_QryInstrumentMarginRateField:
//		return QryInstrumentMarginRateField;
//		break;
//	case E_QryDepthMarketDataField:
//		return QryDepthMarketDataField;
//		break;
//	case E_QryOrder:
//		return QryOrderField;
//		break;
//	case E_QryTrade:
//		return QryTradeField;
//		break;
//	default:
//		return nullptr;
//		break;
//	}
//}


CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcReqAuthenticateField()
{
	strcpy_s(ReqAuthenticateField->BrokerID, g_tdBrokerID.c_str());
	strcpy_s(ReqAuthenticateField->UserID, g_tdInvestorId.c_str());
	strcpy_s(ReqAuthenticateField->UserProductInfo, g_tdUserProductInfo.c_str());
	strcpy_s(ReqAuthenticateField->AuthCode, g_tdAuthCode.c_str());
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcReqUserLoginField()
{
	strcpy_s(ReqUserLoginField->BrokerID, g_tdBrokerID.c_str());
	strcpy_s(ReqUserLoginField->UserID, g_tdInvestorId.c_str());
	strcpy_s(ReqUserLoginField->Password, g_tdPassword.c_str());
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcSettlementInfoConfirmField()
{
	strcpy_s(SettlementInfoConfirmField->BrokerID, g_tdBrokerID.c_str());
	strcpy_s(SettlementInfoConfirmField->InvestorID, g_tdInvestorId.c_str());
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcQrySettlementInfoField(const char *TradingDay)
{
	strcpy_s(QrySettlementInfoField->BrokerID, g_RspUserLogin.BrokerID);
	strcpy_s(QrySettlementInfoField->InvestorID, g_RspUserLogin.UserID);
	strcpy_s(QrySettlementInfoField->TradingDay, TradingDay);
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcQrySettlementInfoConfirmField()
{
	strcpy_s(QrySettlementInfoConfirmField->BrokerID, g_tdBrokerID.c_str());
	strcpy_s(QrySettlementInfoConfirmField->InvestorID, g_tdInvestorId.c_str());
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcQryDepthMarketDataField()
{
	strcpy_s(QryDepthMarketDataField->InstrumentID, "");
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcQryInstrumentField(const char *InstrumentID)
{
	if (InstrumentID)
		strcpy_s(QryInstrumentField->InstrumentID, InstrumentID);
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem ::MakeCThostFtdcQryInstrumentCommissionRateField(const char *InstrumentID)
{
	strcpy_s(QryInstrumentCommissionRateField->BrokerID, g_tdBrokerID.c_str());
	strcpy_s(QryInstrumentCommissionRateField->InvestorID, g_tdInvestorId.c_str());
	strcpy_s(QryInstrumentCommissionRateField->InstrumentID, InstrumentID);
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcQryInstrumentMarginRateField(const char *InstrumentID, TThostFtdcHedgeFlagType HedgeFlag)
{
	strcpy_s(QryInstrumentMarginRateField->BrokerID, g_tdBrokerID.c_str());
	strcpy_s(QryInstrumentMarginRateField->InvestorID, g_tdInvestorId.c_str());
	strcpy_s(QryInstrumentMarginRateField->InstrumentID, InstrumentID);
	QryInstrumentMarginRateField->HedgeFlag = HedgeFlag;
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcQryInvestorPositionField(const char *InstrumentID)
{
	strcpy_s(QryInvestorPositionField->BrokerID, g_tdBrokerID.c_str());
	strcpy_s(QryInvestorPositionField->InvestorID, g_tdInvestorId.c_str());
	strcpy_s(QryInvestorPositionField->InstrumentID, InstrumentID);
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcQryTradingAccountField()
{
	strcpy_s(QryTradingAccountField->BrokerID, g_RspUserLogin.BrokerID);
	strcpy_s(QryTradingAccountField->InvestorID, g_RspUserLogin.UserID);
	return this;
}

CCTPReqMsgItem *
CCTPReqMsgItem::MakeCThostFtdcInputOrderField(int OrderRef, const char *InstrumentID,
		char OrderPriceType, double LimitPrice, int VolumeTotalOriginal, wdDirectionType Direction, wdOffsetFlagType OffsetFlag, char TimeCondition,
		wdContingentConditionType ContingentCondition, double StopPrice)
{
	TThostFtdcDirectionType _direction;
	TThostFtdcCombOffsetFlagType _OffsetFlag = {0};
	TThostFtdcContingentConditionType _ContingentCondition;
	if (Direction == E_Buy)
		_direction = THOST_FTDC_D_Buy;
	else if (Direction == E_Sell)
		_direction = THOST_FTDC_D_Sell;
	else
		_ASSERT(false);

	if (OffsetFlag == E_Open)
		_OffsetFlag[0] = THOST_FTDC_OFEN_Open;
	else if (OffsetFlag == E_Close)
		_OffsetFlag[0] = THOST_FTDC_OFEN_Close;
	else if (OffsetFlag == E_CloseToday)
		_OffsetFlag[0] = THOST_FTDC_OFEN_CloseToday;
	else
		_ASSERT(false);

	switch (ContingentCondition)
	{
	case E_Immediately:
		_ContingentCondition = THOST_FTDC_CC_Immediately;
		break;
	case E_Touch:
		_ContingentCondition = THOST_FTDC_CC_Touch;
		break;
	case E_TouchProfit:
		_ContingentCondition = THOST_FTDC_CC_TouchProfit;
		break;
	case E_ParkedOrder:
		_ContingentCondition = THOST_FTDC_CC_ParkedOrder;
		break;
	case E_LastPriceGreaterThanStopPrice:
		_ContingentCondition = THOST_FTDC_CC_LastPriceGreaterThanStopPrice;
		break;
	case E_LastPriceGreaterEqualStopPrice:
		_ContingentCondition = THOST_FTDC_CC_LastPriceGreaterEqualStopPrice;
		break;
	case E_LastPriceLesserThanStopPrice:
		_ContingentCondition = THOST_FTDC_CC_LastPriceLesserThanStopPrice;
		break;
	case E_LastPriceLesserEqualStopPrice:
		_ContingentCondition = THOST_FTDC_CC_LastPriceLesserEqualStopPrice;
		break;
	case E_AskPriceGreaterThanStopPrice:
		_ContingentCondition = THOST_FTDC_CC_AskPriceGreaterThanStopPrice;
		break;
	case E_AskPriceGreaterEqualStopPrice:
		_ContingentCondition = THOST_FTDC_CC_AskPriceGreaterEqualStopPrice;
		break;
	case E_AskPriceLesserThanStopPrice:
		_ContingentCondition = THOST_FTDC_CC_AskPriceLesserThanStopPrice;
		break;
	case E_AskPriceLesserEqualStopPrice:
		_ContingentCondition = THOST_FTDC_CC_AskPriceLesserEqualStopPrice;
		break;
	case E_BidPriceGreaterThanStopPrice:
		_ContingentCondition = THOST_FTDC_CC_BidPriceGreaterThanStopPrice;
		break;
	case E_BidPriceGreaterEqualStopPrice:
		_ContingentCondition = THOST_FTDC_CC_BidPriceGreaterEqualStopPrice;
		break;
	case E_BidPriceLesserThanStopPrice:
		_ContingentCondition = THOST_FTDC_CC_BidPriceLesserThanStopPrice;
		break;
	case E_BidPriceLesserEqualStopPrice:
		_ContingentCondition = THOST_FTDC_CC_BidPriceLesserEqualStopPrice;
		break;
	default:
		_ContingentCondition = THOST_FTDC_CC_Immediately;
		break;
	}

	strcpy_s(InputOrderField->BrokerID, g_RspUserLogin.BrokerID);
	strcpy_s(InputOrderField->InvestorID, g_RspUserLogin.UserID);

	InputOrderField->MinVolume = 1;
	InputOrderField->ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	InputOrderField->IsAutoSuspend = 0; // 永远不自动挂起
	InputOrderField->UserForceClose = 0;
	InputOrderField->IsSwapOrder = 0;

	//合约
	if (InstrumentID)
		strcpy_s(InputOrderField->InstrumentID, InstrumentID);
	//买卖
	InputOrderField->Direction = _direction;
	//开平
	strcpy_s(InputOrderField->CombOffsetFlag, _OffsetFlag);

	//价格
	InputOrderField->OrderPriceType = OrderPriceType;
	InputOrderField->LimitPrice = LimitPrice;		

	//数量
	InputOrderField->VolumeTotalOriginal = VolumeTotalOriginal;
	///组合投机套保标志
	InputOrderField->CombHedgeFlag[0] = THOST_FTDC_HFEN_Speculation; // 投机

	//各条件
	InputOrderField->VolumeCondition = THOST_FTDC_VC_AV; // 任意数量
	InputOrderField->TimeCondition = TimeCondition;
	InputOrderField->ContingentCondition = _ContingentCondition;
	InputOrderField->StopPrice = 0;

	extern std::string g_trader_no;
	sprintf_s(InputOrderField->OrderRef, "%2s%2s%08d", g_trader_no.c_str(), "00", OrderRef);

	return this;
}


CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcInputOrderActionField(const char *OrderRef, int FrontID, int SessionID, const char *ExchangeID, const char *OrderSysID, char ActionFlag, const char *InstrumentID)
{
	///经纪公司代码
	strcpy_s(InputOrderActionField->BrokerID, g_RspUserLogin.BrokerID);
	///投资者代码
	
	strcpy_s(InputOrderActionField->InvestorID, g_RspUserLogin.UserID);
	///报单引用 大商所、郑商所在报单未到达交易所时，OrderRef撤单会失败
	if (OrderRef)
		strcpy_s(InputOrderActionField->OrderRef, OrderRef);
	///前置编号
	InputOrderActionField->FrontID = FrontID;
	///会话编号
	InputOrderActionField->SessionID = SessionID;
	///交易所代码
	if (ExchangeID)
		strcpy_s(InputOrderActionField->ExchangeID, ExchangeID);
	///报单编号
	if (OrderSysID)
		strcpy_s(InputOrderActionField->OrderSysID, OrderSysID);
	///操作标志
	InputOrderActionField->ActionFlag = ActionFlag;
	///合约代码
	if (InstrumentID)
		strcpy_s(InputOrderActionField->InstrumentID, InstrumentID);
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcQryOrderField(const char *InstrumentID)
{
	strcpy_s(QryOrderField->BrokerID, g_RspUserLogin.BrokerID);
	strcpy_s(QryOrderField->InvestorID, g_RspUserLogin.UserID);
	strcpy_s(QryOrderField->InstrumentID, InstrumentID);
	return this;
}

CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcQryTradeField(const char *InstrumentID)
{
	strcpy_s(QryTradeField->BrokerID, g_RspUserLogin.BrokerID);
	strcpy_s(QryTradeField->InvestorID, g_RspUserLogin.UserID);
	strcpy_s(QryTradeField->InstrumentID, InstrumentID);
	return this;
}