using System;

namespace QuantBox.CSharp2CTP.Callback
{
    public delegate void fnOnConnect(object sender, ref CThostFtdcRspUserLoginField pRspUserLogin, ConnectionStatus result);
    public delegate void fnOnDisconnect(object sender, ref CThostFtdcRspInfoField pRspInfo, ConnectionStatus step);
    public delegate void fnOnRspError(object sender, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

    public delegate void fnOnTick(object sender, ref Tick pTick);
    public delegate void fnOnKLine(object sender, ref K_Line pKLine);

    public delegate void fnOnRtnDepthMarketData(object sender, ref Tick pDepthMarketData);
    public delegate void fnOnRtnForQuoteRsp(object sender, ref CThostFtdcForQuoteRspField pForQuoteRsp);

    public delegate void fnOnErrRtnOrderAction(object sender, ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo);
    public delegate void fnOnErrRtnOrderInsert(object sender, ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo);
    public delegate void fnOnErrRtnQuoteAction(object sender, ref CThostFtdcQuoteActionField pQuoteAction, ref CThostFtdcRspInfoField pRspInfo);
    public delegate void fnOnErrRtnQuoteInsert(object sender, ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo);
    public delegate void fnOnRspOrderAction(object sender, ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspOrderInsert(object sender, ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryDepthMarketData(object sender, ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInstrument(object sender, ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInstrumentCommissionRate(object sender, ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInstrumentMarginRate(object sender, ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInvestorPosition(object sender, ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryInvestorPositionDetail(object sender, ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryOrder(object sender, ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryTrade(object sender, ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQrySettlementInfo(object sender, ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQryTradingAccount(object sender, ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQuoteAction(object sender, ref CThostFtdcInputQuoteActionField pInputQuoteAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRspQuoteInsert(object sender, ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
    public delegate void fnOnRtnInstrumentStatus(object sender, ref CThostFtdcInstrumentStatusField pInstrumentStatus);
    public delegate void fnOnRtnOrder(object sender, ref CThostFtdcOrderField pOrder);
    public delegate void fnOnRtnQuote(object sender, ref CThostFtdcQuoteField pQuote);
    public delegate void fnOnRtnTrade(object sender, ref CThostFtdcTradeField pTrade);
}
