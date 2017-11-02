using System;
using System.Runtime.InteropServices;
using System.Text;

namespace QuantBoxCSharp
{
    public class TdApi
    {
        // 交易API
        [DllImport("QuantBox.dll", EntryPoint = "TD_Connect")]
        public static extern void TD_Connect();

        [DllImport("QuantBox.dll", EntryPoint = "TD_SendOrder")]
        public static extern int TD_SendOrder(
            int OrderRef,
            string szInstrument,
            TThostFtdcDirectionType Direction,
            string szCombOffsetFlag,
            string szCombHedgeFlag,
            int VolumeTotalOriginal,
            double LimitPrice,
            TThostFtdcOrderPriceTypeType OrderPriceType,
            TThostFtdcTimeConditionType TimeCondition,
            TThostFtdcContingentConditionType ContingentCondition,
            double StopPrice,
            TThostFtdcVolumeConditionType VolumeCondition);

        [DllImport("QuantBox.dll", EntryPoint = "TD_CancelOrder")]
        public static extern void TD_CancelOrder(string Instrument, TThostFtdcDirectionType Direction, string OffsetFlag);

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQryInvestorPosition")]
        public static extern void TD_ReqQryInvestorPosition(string szInstrument);

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQryInvestorPositionDetail")]
        public static extern void TD_ReqQryInvestorPositionDetail(string szInstrument);

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQryTradingAccount")]
        public static extern void TD_ReqQryTradingAccount();

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQryInstrument")]
        public static extern void TD_ReqQryInstrument(string szInstrument);

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQryInstrumentCommissionRate")]
        public static extern void TD_ReqQryInstrumentCommissionRate(string szInstrument);

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQryInstrumentMarginRate")]
        public static extern void TD_ReqQryInstrumentMarginRate(string szInstrument, TThostFtdcHedgeFlagType HedgeFlag);

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQryDepthMarketData")]
        public static extern void TD_ReqQryDepthMarketData(string szInstrument);

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQrySettlementInfo")]
        public static extern void TD_ReqQrySettlementInfo(string szTradingDay);

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQryOrder")]
        public static extern void TD_ReqQryOrder(string szInstrument);

        [DllImport("QuantBox.dll", EntryPoint = "TD_ReqQryTrade")]
        public static extern void TD_ReqQryTrade(string szInstrument);

        [DllImport("QuantBox.dll", EntryPoint = "TD_Disconnect")]
        public static extern void TD_Disconnect();       

        
        // 注册交易回调
        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegTDOnConnect")]
        public static extern void CTP_RegTDOnConnect(fnOnConnect pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegTDOnDisconnect")]
        public static extern void CTP_RegTDOnDisconnect(fnOnDisconnect pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegTDOnRspError")]
        public static extern void CTP_RegTDOnRspError(fnOnRspError pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnErrRtnOrderAction")]
        public static extern void CTP_RegOnErrRtnOrderAction(fnOnErrRtnOrderAction pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnErrRtnOrderInsert")]
        public static extern void CTP_RegOnErrRtnOrderInsert(fnOnErrRtnOrderInsert pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnErrRtnQuoteAction")]
        public static extern void CTP_RegOnErrRtnQuoteAction(fnOnErrRtnQuoteAction pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnErrRtnQuoteInsert")]
        public static extern void CTP_RegOnErrRtnQuoteInsert(fnOnErrRtnQuoteInsert pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspOrderAction")]
        public static extern void CTP_RegOnRspOrderAction(fnOnRspOrderAction pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspOrderInsert")]
        public static extern void CTP_RegOnRspOrderInsert(fnOnRspOrderInsert pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQuoteAction")]
        public static extern void CTP_RegOnRspQuoteAction(fnOnRspQuoteAction pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQuoteInsert")]
        public static extern void CTP_RegOnRspQuoteInsert(fnOnRspQuoteInsert pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQryDepthMarketData")]
        public static extern void CTP_RegOnRspQryDepthMarketData(fnOnRspQryDepthMarketData pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQryInstrument")]
        public static extern void CTP_RegOnRspQryInstrument(fnOnRspQryInstrument pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQryInstrumentCommissionRate")]
        public static extern void CTP_RegOnRspQryInstrumentCommissionRate(fnOnRspQryInstrumentCommissionRate pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQryInstrumentMarginRate")]
        public static extern void CTP_RegOnRspQryInstrumentMarginRate(fnOnRspQryInstrumentMarginRate pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQryInvestorPosition")]
        public static extern void CTP_RegOnRspQryInvestorPosition(fnOnRspQryInvestorPosition pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQryInvestorPositionDetail")]
        public static extern void CTP_RegOnRspQryInvestorPositionDetail(fnOnRspQryInvestorPositionDetail pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQryOrder")]
        public static extern void CTP_RegOnRspQryOrder(fnOnRspQryOrder pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQryTrade")]
        public static extern void CTP_RegOnRspQryTrade(fnOnRspQryTrade pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQrySettlementInfo")]
        public static extern void CTP_RegOnRspQrySettlementInfo(fnOnRspQrySettlementInfo pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRspQryTradingAccount")]
        public static extern void CTP_RegOnRspQryTradingAccount(fnOnRspQryTradingAccount pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRtnInstrumentStatus")]
        public static extern void CTP_RegOnRtnInstrumentStatus(fnOnRtnInstrumentStatus pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRtnOrder")]
        public static extern void CTP_RegOnRtnOrder(fnOnRtnOrder pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRtnQuote")]
        public static extern void CTP_RegOnRtnQuote(fnOnRtnQuote pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRtnTrade")]
        public static extern void CTP_RegOnRtnTrade(fnOnRtnTrade pCallback);
    }
}
