using System;

namespace QuantBoxCSharp
{
    public delegate void fnOnConnect(ConnectionStatus result);
    public delegate void fnOnDisconnect(ref CThostFtdcRspInfoField pRspInfo, ConnectionStatus step);
    public delegate void fnOnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

    //public delegate void fnOnRtnDepthMarketData(ref CTick pDepthMarketData);
    public delegate void fnOnTick(ref CTick pTick);
    public delegate void fnOnKLine(ref CKLine pKLine);
    //public delegate void fnOnRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pForQuoteRsp);

    public delegate void fnOnErrRtnOrderAction(ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo);
    public delegate void fnOnErrRtnOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo);
    public delegate void fnOnErrRtnQuoteAction(ref CThostFtdcQuoteActionField pQuoteAction, ref CThostFtdcRspInfoField pRspInfo);
    public delegate void fnOnErrRtnQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo);
    public delegate void fnOnRspOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInstrument(ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInstrumentCommissionRate(ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInstrumentMarginRate(ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInvestorPosition(ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInvestorPositionDetail(ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryOrder(ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryTrade(ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQrySettlementInfo(ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQuoteAction(ref CThostFtdcInputQuoteActionField pInputQuoteAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRtnInstrumentStatus(ref CThostFtdcInstrumentStatusField pInstrumentStatus);
    public delegate void fnOnRtnOrder(ref CThostFtdcOrderField pOrder);
    public delegate void fnOnRtnQuote(ref CThostFtdcQuoteField pQuote);
    public delegate void fnOnRtnTrade(ref CThostFtdcTradeField pTrade);
}
