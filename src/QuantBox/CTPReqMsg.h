#ifndef _CTP_REQ_MSG_H_
#define _CTP_REQ_MSG_H_

#include <memory>
#include "CTP/ThostFtdcUserApiStruct.h"
#include "Types.h"

// CTP交易请求的类型
enum E_CTPReqType
{
	E_InputOrderField,						// 下单
	E_InputOrderActionField,				// 撤单
	E_InputQuoteField,
	E_InputQuoteActionField,

	E_ReqAuthenticateField,
	E_ReqUserLoginField,
	E_SettlementInfoConfirmField,

	E_QrySettlementInfoField,
	E_QrySettlementInfoConfirmField,
	E_QryInstrumentField,	
	E_QryTradingAccountField,
	E_QryInvestorPositionField,
	E_QryInvestorPositionDetailField,
	E_QryInstrumentCommissionRateField,
	E_QryInstrumentMarginRateField,
	E_QryDepthMarketDataField,
	E_QryOrder,								// 查委托
	E_QryTrade								// 查成交
};

class CCTPReqMsgItem
{
public:
	CCTPReqMsgItem(E_CTPReqType type);
	~CCTPReqMsgItem(void);

	E_CTPReqType get_type() const { return m_type; }

	CCTPReqMsgItem *MakeCThostFtdcReqAuthenticateField();
	CCTPReqMsgItem *MakeCThostFtdcReqUserLoginField();
	CCTPReqMsgItem *MakeCThostFtdcSettlementInfoConfirmField();

	// 下单
	CCTPReqMsgItem *CCTPReqMsgItem::MakeCThostFtdcInputOrderField(int OrderRef, const char *InstrumentID,
		char OrderPriceType, double LimitPrice, int VolumeTotalOriginal, wdDirectionType Direction, wdOffsetFlagType OffsetFlag, char TimeCondition,
		wdContingentConditionType ContingentCondition = E_Immediately, double StopPrice = 0.);

	// 撤单
	CCTPReqMsgItem *MakeCThostFtdcInputOrderActionField(const char *OrderRef, int FrontID, int SessionID, const char *ExchangeID, const char *OrderSysID, char ActionFlag, const char *InstrumentID);

	CCTPReqMsgItem *MakeCThostFtdcQrySettlementInfoField(const char *TradingDay);
	CCTPReqMsgItem *MakeCThostFtdcQrySettlementInfoConfirmField();
	CCTPReqMsgItem *MakeCThostFtdcQryDepthMarketDataField();
	CCTPReqMsgItem *MakeCThostFtdcQryInstrumentField(const char *InstrumentID);
	CCTPReqMsgItem *MakeCThostFtdcQryInstrumentCommissionRateField(const char *InstrumentID);
	CCTPReqMsgItem *MakeCThostFtdcQryInstrumentMarginRateField(const char *InstrumentID, TThostFtdcHedgeFlagType HedgeFlag);
	CCTPReqMsgItem *MakeCThostFtdcQryInvestorPositionField(const char *InstrumentID = nullptr);
	CCTPReqMsgItem *MakeCThostFtdcQryTradingAccountField();
	CCTPReqMsgItem *MakeCThostFtdcQryOrderField(const char *InstrumentID);
	CCTPReqMsgItem *MakeCThostFtdcQryTradeField(const char *InstrumentID);
	
	operator CThostFtdcInputOrderField*() { return InputOrderField; }
	operator CThostFtdcInputOrderActionField*() { return InputOrderActionField; }
	operator CThostFtdcInputQuoteField*() { return InputQuoteField; }
	operator CThostFtdcInputQuoteActionField*() { return InputQuoteActionField; }
	operator CThostFtdcReqAuthenticateField*() { return ReqAuthenticateField; }
	operator CThostFtdcReqUserLoginField*() { return ReqUserLoginField; }
	operator CThostFtdcSettlementInfoConfirmField*() { return SettlementInfoConfirmField; }
	operator CThostFtdcQrySettlementInfoField*() { return QrySettlementInfoField; }
	operator CThostFtdcQrySettlementInfoConfirmField*() { return QrySettlementInfoConfirmField; }
	operator CThostFtdcQryDepthMarketDataField*() { return QryDepthMarketDataField; }
	operator CThostFtdcQryInstrumentField*() { return QryInstrumentField; }
	operator CThostFtdcQryInstrumentCommissionRateField*() { return QryInstrumentCommissionRateField; }
	operator CThostFtdcQryInstrumentMarginRateField*() { return QryInstrumentMarginRateField; }
	operator CThostFtdcQryInvestorPositionField*() { return QryInvestorPositionField; }
	operator CThostFtdcQryInvestorPositionDetailField*() { return QryInvestorPositionDetailField; }
	operator CThostFtdcQryTradingAccountField*() { return QryTradingAccountField; }
	operator CThostFtdcQryOrderField*() { return QryOrderField; }
	operator CThostFtdcQryTradeField*() { return QryTradeField; }

private:
	E_CTPReqType									m_type;
	union{
		CThostFtdcInputOrderField					*InputOrderField;
		CThostFtdcInputOrderActionField				*InputOrderActionField;
		CThostFtdcInputQuoteField					*InputQuoteField;
		CThostFtdcInputQuoteActionField				*InputQuoteActionField;

		CThostFtdcReqAuthenticateField				*ReqAuthenticateField;
		CThostFtdcReqUserLoginField					*ReqUserLoginField;
		CThostFtdcSettlementInfoConfirmField		*SettlementInfoConfirmField;

		CThostFtdcQrySettlementInfoField			*QrySettlementInfoField;
		CThostFtdcQrySettlementInfoConfirmField		*QrySettlementInfoConfirmField;
		CThostFtdcQryDepthMarketDataField			*QryDepthMarketDataField;
		CThostFtdcQryInstrumentField				*QryInstrumentField;
		CThostFtdcQryInstrumentCommissionRateField	*QryInstrumentCommissionRateField;
		CThostFtdcQryInstrumentMarginRateField		*QryInstrumentMarginRateField;
		CThostFtdcQryInvestorPositionField			*QryInvestorPositionField;
		CThostFtdcQryInvestorPositionDetailField    *QryInvestorPositionDetailField;
		CThostFtdcQryTradingAccountField			*QryTradingAccountField;		
		CThostFtdcQryOrderField						*QryOrderField;
		CThostFtdcQryTradeField						*QryTradeField;
	};
};

#endif