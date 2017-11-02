using System;
using System.Runtime.InteropServices;
using System.Text;

namespace QuantBox.CSharp2CTP
{
    public class TraderApi
    {
        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnErrRtnOrderAction")]
        public static extern void CTP_RegOnErrRtnOrderAction(fnOnErrRtnOrderAction pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnErrRtnOrderInsert")]
        public static extern void CTP_RegOnErrRtnOrderInsert(fnOnErrRtnOrderInsert pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnErrRtnQuoteAction")]
        public static extern void CTP_RegOnErrRtnQuoteAction(fnOnErrRtnQuoteAction pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnErrRtnQuoteInsert")]
        public static extern void CTP_RegOnErrRtnQuoteInsert(fnOnErrRtnQuoteInsert pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspOrderAction")]
        public static extern void CTP_RegOnRspOrderAction(fnOnRspOrderAction pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspOrderInsert")]
        public static extern void CTP_RegOnRspOrderInsert(fnOnRspOrderInsert pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQuoteAction")]
        public static extern void CTP_RegOnRspQuoteAction(fnOnRspQuoteAction pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQuoteInsert")]
        public static extern void CTP_RegOnRspQuoteInsert(fnOnRspQuoteInsert pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQryDepthMarketData")]
        public static extern void CTP_RegOnRspQryDepthMarketData(fnOnRspQryDepthMarketData pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQryInstrument")]
        public static extern void CTP_RegOnRspQryInstrument(fnOnRspQryInstrument pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQryInstrumentCommissionRate")]
        public static extern void CTP_RegOnRspQryInstrumentCommissionRate(fnOnRspQryInstrumentCommissionRate pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQryInstrumentMarginRate")]
        public static extern void CTP_RegOnRspQryInstrumentMarginRate(fnOnRspQryInstrumentMarginRate pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQryInvestorPosition")]
        public static extern void CTP_RegOnRspQryInvestorPosition(fnOnRspQryInvestorPosition pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQryInvestorPositionDetail")]
        public static extern void CTP_RegOnRspQryInvestorPositionDetail(fnOnRspQryInvestorPositionDetail pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQryOrder")]
        public static extern void CTP_RegOnRspQryOrder(fnOnRspQryOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQryTrade")]
        public static extern void CTP_RegOnRspQryTrade(fnOnRspQryTrade pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQrySettlementInfo")]
        public static extern void CTP_RegOnRspQrySettlementInfo(fnOnRspQrySettlementInfo pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRspQryTradingAccount")]
        public static extern void CTP_RegOnRspQryTradingAccount(fnOnRspQryTradingAccount pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRtnInstrumentStatus")]
        public static extern void CTP_RegOnRtnInstrumentStatus(fnOnRtnInstrumentStatus pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRtnOrder")]
        public static extern void CTP_RegOnRtnOrder(fnOnRtnOrder pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRtnQuote")]
        public static extern void CTP_RegOnRtnQuote(fnOnRtnQuote pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRtnTrade")]
        public static extern void CTP_RegOnRtnTrade(fnOnRtnTrade pCallback);


       

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_Connect")]
        public static extern void TD_Connect();

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_SendOrder")]
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

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_CancelOrder")]
        public static extern void TD_CancelOrder(string Instrument, TThostFtdcDirectionType Direction, string OffsetFlag);

        

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_Disconnect")]
        public static extern void TD_Disconnect();       

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryInvestorPosition")]
        public static extern void TD_ReqQryInvestorPosition(string szInstrument);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryInvestorPositionDetail")]
        public static extern void TD_ReqQryInvestorPositionDetail(string szInstrument);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryTradingAccount")]
        public static extern void TD_ReqQryTradingAccount();

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryInstrument")]
        public static extern void TD_ReqQryInstrument(string szInstrument);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryInstrumentCommissionRate")]
        public static extern void TD_ReqQryInstrumentCommissionRate(string szInstrument);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryInstrumentMarginRate")]
        public static extern void TD_ReqQryInstrumentMarginRate(string szInstrument, TThostFtdcHedgeFlagType HedgeFlag);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryDepthMarketData")]
        public static extern void TD_ReqQryDepthMarketData(string szInstrument);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQrySettlementInfo")]
        public static extern void TD_ReqQrySettlementInfo(string szTradingDay);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryOrder")]
        public static extern void TD_ReqQryOrder(string szInstrument);

        [DllImport(CommApi.DllFileName, EntryPoint = "TD_ReqQryTrade")]
        public static extern void TD_ReqQryTrade(string szInstrument);

        
    }
}
