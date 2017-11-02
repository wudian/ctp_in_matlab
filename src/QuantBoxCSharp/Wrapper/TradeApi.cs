using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace QuantBoxCSharp.Callback
{
    public class TradeApi:BaseApi
    {
        private object locker = new object();

        private fnOnErrRtnOrderAction OnErrRtnOrderAction_1;
        private fnOnErrRtnOrderInsert OnErrRtnOrderInsert_1;
        private fnOnErrRtnQuoteAction OnErrRtnQuoteAction_1;
        private fnOnErrRtnQuoteInsert OnErrRtnQuoteInsert_1;
        private fnOnRspOrderAction OnRspOrderAction_1;
        private fnOnRspOrderInsert OnRspOrderInsert_1;
        private fnOnRspQuoteAction OnRspQuoteAction_1;
        private fnOnRspQuoteInsert OnRspQuoteInsert_1;
        private fnOnRspQryDepthMarketData OnRspQryDepthMarketData_1;
        private fnOnRspQryInstrument OnRspQryInstrument_1;
        private fnOnRspQryInstrumentCommissionRate OnRspQryInstrumentCommissionRate_1;
        private fnOnRspQryInstrumentMarginRate OnRspQryInstrumentMarginRate_1;
        private fnOnRspQryInvestorPosition OnRspQryInvestorPosition_1;
        private fnOnRspQryInvestorPositionDetail OnRspQryInvestorPositionDetail_1;
        private fnOnRspQryOrder OnRspQryOrder_1;
        private fnOnRspQryTrade OnRspQryTrade_1;
        private fnOnRspQrySettlementInfo OnRspQrySettlementInfo_1;
        private fnOnRspQryTradingAccount OnRspQryTradingAccount_1;
        private fnOnRtnInstrumentStatus OnRtnInstrumentStatus_1;
        private fnOnRtnOrder OnRtnOrder_1;
        private fnOnRtnQuote OnRtnQuote_1;
        private fnOnRtnTrade OnRtnTrade_1;

        private QuantBoxCSharp.fnOnErrRtnOrderAction OnErrRtnOrderAction_2;
        private QuantBoxCSharp.fnOnErrRtnOrderInsert OnErrRtnOrderInsert_2;
        private QuantBoxCSharp.fnOnErrRtnQuoteAction OnErrRtnQuoteAction_2;
        private QuantBoxCSharp.fnOnErrRtnQuoteInsert OnErrRtnQuoteInsert_2;
        private QuantBoxCSharp.fnOnRspOrderAction OnRspOrderAction_2;
        private QuantBoxCSharp.fnOnRspOrderInsert OnRspOrderInsert_2;
        private QuantBoxCSharp.fnOnRspQuoteAction OnRspQuoteAction_2;
        private QuantBoxCSharp.fnOnRspQuoteInsert OnRspQuoteInsert_2;
        private QuantBoxCSharp.fnOnRspQryDepthMarketData OnRspQryDepthMarketData_2;
        private QuantBoxCSharp.fnOnRspQryInstrument OnRspQryInstrument_2;
        private QuantBoxCSharp.fnOnRspQryInstrumentCommissionRate OnRspQryInstrumentCommissionRate_2;
        private QuantBoxCSharp.fnOnRspQryInstrumentMarginRate OnRspQryInstrumentMarginRate_2;
        private QuantBoxCSharp.fnOnRspQryInvestorPosition OnRspQryInvestorPosition_2;
        private QuantBoxCSharp.fnOnRspQryInvestorPositionDetail OnRspQryInvestorPositionDetail_2;
        private QuantBoxCSharp.fnOnRspQryOrder OnRspQryOrder_2;
        private QuantBoxCSharp.fnOnRspQryTrade OnRspQryTrade_2;
        private QuantBoxCSharp.fnOnRspQrySettlementInfo OnRspQrySettlementInfo_2;
        private QuantBoxCSharp.fnOnRspQryTradingAccount OnRspQryTradingAccount_2;
        private QuantBoxCSharp.fnOnRtnInstrumentStatus OnRtnInstrumentStatus_2;
        private QuantBoxCSharp.fnOnRtnOrder OnRtnOrder_2;
        private QuantBoxCSharp.fnOnRtnQuote OnRtnQuote_2;
        private QuantBoxCSharp.fnOnRtnTrade OnRtnTrade_2;


        public fnOnErrRtnOrderAction OnErrRtnOrderAction
        {
            set
            {
                OnErrRtnOrderAction_1 = value;
                OnErrRtnOrderAction_2 = OnErrRtnOrderAction_3;
                
            }
        }
        private void OnErrRtnOrderAction_3(ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo)
        {
            OnErrRtnOrderAction_1(this, ref pOrderAction, ref pRspInfo);
        }

        public fnOnErrRtnOrderInsert OnErrRtnOrderInsert
        {
            set
            {
                OnErrRtnOrderInsert_1 = value;
                OnErrRtnOrderInsert_2 = OnErrRtnOrderInsert_3;
               
            }
        }

        private void OnErrRtnOrderInsert_3(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo)
        {
            OnErrRtnOrderInsert_1(this, ref pInputOrder, ref pRspInfo);
        }

        public fnOnErrRtnQuoteAction OnErrRtnQuoteAction
        {
            set
            {
                OnErrRtnQuoteAction_1 = value;
                OnErrRtnQuoteAction_2 = OnErrRtnQuoteAction_3;
                
            }
        }

        private void OnErrRtnQuoteAction_3(ref CThostFtdcQuoteActionField pQuoteAction, ref CThostFtdcRspInfoField pRspInfo)
        {
            OnErrRtnQuoteAction_1(this, ref pQuoteAction, ref pRspInfo);
        }
    

        public fnOnErrRtnQuoteInsert OnErrRtnQuoteInsert
        {
            set
            {
                OnErrRtnQuoteInsert_1 = value;
                OnErrRtnQuoteInsert_2 = OnErrRtnQuoteInsert_3;
                
            }
        }

        private void OnErrRtnQuoteInsert_3(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo)
        {
            OnErrRtnQuoteInsert_1(this, ref pInputQuote, ref pRspInfo);
        }
    

        public fnOnRspOrderAction OnRspOrderAction
        {
            set
            {
                OnRspOrderAction_1 = value;
                OnRspOrderAction_2 = OnRspOrderAction_3;
                
            }
        }

        private void OnRspOrderAction_3(ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspOrderAction_1(this, ref pInputOrderAction, ref pRspInfo, nRequestID, bIsLast);
        }
    
        public fnOnRspOrderInsert OnRspOrderInsert
        {
            set
            {
                OnRspOrderInsert_1 = value;
                OnRspOrderInsert_2 = OnRspOrderInsert_3;
                
            }
        }

        private void OnRspOrderInsert_3(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspOrderInsert_1(this, ref pInputOrder, ref pRspInfo, nRequestID, bIsLast);
        }
    

        public fnOnRspQuoteAction OnRspQuoteAction
        {
            set
            {
                OnRspQuoteAction_1 = value;
                OnRspQuoteAction_2 = OnRspQuoteAction_3;
            }
        }

        private void OnRspQuoteAction_3(ref CThostFtdcInputQuoteActionField pInputQuoteAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQuoteAction_1(this, ref pInputQuoteAction, ref pRspInfo, nRequestID, bIsLast);
        }
    
        public fnOnRspQuoteInsert OnRspQuoteInsert
        {
            set
            {
                OnRspQuoteInsert_1 = value;
                OnRspQuoteInsert_2 = OnRspQuoteInsert_3;
            }
        }

        private void OnRspQuoteInsert_3(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQuoteInsert_1(this, ref pInputQuote, ref pRspInfo, nRequestID, bIsLast);
        }

        public fnOnRspQryDepthMarketData OnRspQryDepthMarketData
        {
            set
            {
                OnRspQryDepthMarketData_1 = value;
                OnRspQryDepthMarketData_2 = OnRspQryDepthMarketData_3;
            }
        }

        private void OnRspQryDepthMarketData_3(ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQryDepthMarketData_1(this, ref pDepthMarketData, ref pRspInfo, nRequestID, bIsLast);
        }
    
        public fnOnRspQryInstrument OnRspQryInstrument
        {
            set
            {
                OnRspQryInstrument_1 = value;
                OnRspQryInstrument_2 = OnRspQryInstrument_3;
            }
        }

        private void OnRspQryInstrument_3(ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQryInstrument_1(this, ref pInstrument, ref pRspInfo, nRequestID, bIsLast);
        }
    
        public fnOnRspQryInstrumentCommissionRate OnRspQryInstrumentCommissionRate
        {
            set
            {
                OnRspQryInstrumentCommissionRate_1 = value;
                OnRspQryInstrumentCommissionRate_2 = OnRspQryInstrumentCommissionRate_3;
            }
        }

        private void OnRspQryInstrumentCommissionRate_3(ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQryInstrumentCommissionRate_1(this, ref pInstrumentCommissionRate, ref pRspInfo, nRequestID, bIsLast);
        }

        public fnOnRspQryInstrumentMarginRate OnRspQryInstrumentMarginRate
        {
            set
            {
                OnRspQryInstrumentMarginRate_1 = value;
                OnRspQryInstrumentMarginRate_2 = OnRspQryInstrumentMarginRate_3;
            }
        }

        private void OnRspQryInstrumentMarginRate_3(ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQryInstrumentMarginRate_1(this, ref pInstrumentMarginRate, ref pRspInfo, nRequestID, bIsLast);
        }
    
        public fnOnRspQryInvestorPosition OnRspQryInvestorPosition
        {
            set
            {
                OnRspQryInvestorPosition_1 = value;
                OnRspQryInvestorPosition_2 = OnRspQryInvestorPosition_3;
            }
        }

        private void OnRspQryInvestorPosition_3(ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQryInvestorPosition_1(this, ref pInvestorPosition, ref pRspInfo, nRequestID, bIsLast);
        }

        public fnOnRspQryInvestorPositionDetail OnRspQryInvestorPositionDetail
        {
            set
            {
                OnRspQryInvestorPositionDetail_1 = value;
                OnRspQryInvestorPositionDetail_2 = OnRspQryInvestorPositionDetail_3;
            }
        }

        private void OnRspQryInvestorPositionDetail_3(ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQryInvestorPositionDetail_1(this, ref pInvestorPositionDetail, ref pRspInfo, nRequestID, bIsLast);
        }

        public fnOnRspQryOrder OnRspQryOrder
        {
            set
            {
                OnRspQryOrder_1 = value;
                OnRspQryOrder_2 = OnRspQryOrder_3;
            }
        }

        private void OnRspQryOrder_3(ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQryOrder_1(this, ref pOrder, ref pRspInfo, nRequestID, bIsLast);
        }
    
        public fnOnRspQryTrade OnRspQryTrade
        {
            set
            {
                OnRspQryTrade_1 = value;
                OnRspQryTrade_2 = OnRspQryTrade_3;
            }
        }

        private void OnRspQryTrade_3(ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQryTrade_1(this, ref pTrade, ref pRspInfo, nRequestID, bIsLast);
        }

        public fnOnRspQrySettlementInfo OnRspQrySettlementInfo
        {
            set
            {
                OnRspQrySettlementInfo_1 = value;
                OnRspQrySettlementInfo_2 = OnRspQrySettlementInfo_3;
            }
        }

        private void OnRspQrySettlementInfo_3(ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQrySettlementInfo_1(this, ref pSettlementInfo, ref pRspInfo, nRequestID, bIsLast);
        }
    
        public fnOnRspQryTradingAccount OnRspQryTradingAccount
        {
            set
            {
                OnRspQryTradingAccount_1 = value;
                OnRspQryTradingAccount_2 = OnRspQryTradingAccount_3;
            }
        }

        private void OnRspQryTradingAccount_3(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspQryTradingAccount_1(this, ref pTradingAccount, ref pRspInfo, nRequestID, bIsLast);
        }
    
        public fnOnRtnInstrumentStatus OnRtnInstrumentStatus
        {
            set
            {
                OnRtnInstrumentStatus_1 = value;
                OnRtnInstrumentStatus_2 = OnRtnInstrumentStatus_3;
            }
        }

        private void OnRtnInstrumentStatus_3(ref CThostFtdcInstrumentStatusField pInstrumentStatus)
        {
            OnRtnInstrumentStatus_1(this, ref pInstrumentStatus);
        }
    
        public fnOnRtnOrder OnRtnOrder
        {
            set
            {
                OnRtnOrder_1 = value;
                OnRtnOrder_2 = OnRtnOrder_3;
            }
        }

        private void OnRtnOrder_3(ref CThostFtdcOrderField pOrder)
        {
            OnRtnOrder_1(this, ref pOrder);
        }

        public fnOnRtnQuote OnRtnQuote
        {
            set
            {
                OnRtnQuote_1 = value;
                OnRtnQuote_2 = OnRtnQuote_3;
            }
        }

        private void OnRtnQuote_3(ref CThostFtdcQuoteField pQuote)
        {
            OnRtnQuote_1(this, ref pQuote);
        }

        public fnOnRtnTrade OnRtnTrade
        {
            set
            {
                OnRtnTrade_1 = value;
                OnRtnTrade_2 = OnRtnTrade_3;
            }
        }

        private void OnRtnTrade_3(ref CThostFtdcTradeField pTrade)
        {
            OnRtnTrade_1(this, ref pTrade);
        }

        protected override void OnConnect_3(ConnectionStatus result)
        {
            IsConnected = false;
            if (result == ConnectionStatus.Confirmed)
            {
                IsConnected = true;
            }
            OnConnect_1(this, result);
        }

        protected override void OnDisconnect_3(ref CThostFtdcRspInfoField pRspInfo, ConnectionStatus step)
        {
            if (IsConnected)
            {
                if (7 == pRspInfo.ErrorID//综合交易平台：还没有初始化
                    || 8 == pRspInfo.ErrorID)//综合交易平台：前置不活跃
                {
                    Disconnect();
                    Connect();
                }
            }

            IsConnected = false;
            OnDisconnect_1(this, ref pRspInfo, step);
        }

        public TradeApi() : base()
        {
                     
        }

        public void CTP_RegTD()
        {
            TdApi.CTP_RegTDOnConnect(OnConnect_2);
            TdApi.CTP_RegTDOnDisconnect(OnDisconnect_2);
            TdApi.CTP_RegTDOnRspError(OnRspError_2);
            TdApi.CTP_RegOnErrRtnOrderAction(OnErrRtnOrderAction_2);
            TdApi.CTP_RegOnErrRtnOrderInsert(OnErrRtnOrderInsert_2);
            TdApi.CTP_RegOnErrRtnQuoteAction(OnErrRtnQuoteAction_2);
            TdApi.CTP_RegOnErrRtnQuoteInsert(OnErrRtnQuoteInsert_2);
            TdApi.CTP_RegOnRspOrderAction(OnRspOrderAction_2);
            TdApi.CTP_RegOnRspOrderInsert(OnRspOrderInsert_2);
            TdApi.CTP_RegOnRspQuoteAction(OnRspQuoteAction_2);
            TdApi.CTP_RegOnRspQuoteInsert(OnRspQuoteInsert_2);
            TdApi.CTP_RegOnRspQryDepthMarketData(OnRspQryDepthMarketData_2);
            TdApi.CTP_RegOnRspQryInstrument(OnRspQryInstrument_2);
            TdApi.CTP_RegOnRspQryInstrumentCommissionRate(OnRspQryInstrumentCommissionRate_2);
            TdApi.CTP_RegOnRspQryInstrumentMarginRate(OnRspQryInstrumentMarginRate_2);
            TdApi.CTP_RegOnRspQryInvestorPosition(OnRspQryInvestorPosition_2);
            TdApi.CTP_RegOnRspQryInvestorPositionDetail(OnRspQryInvestorPositionDetail_2);
            TdApi.CTP_RegOnRspQryOrder(OnRspQryOrder_2);
            TdApi.CTP_RegOnRspQryTrade(OnRspQryTrade_2);
            TdApi.CTP_RegOnRspQrySettlementInfo(OnRspQrySettlementInfo_2);
            TdApi.CTP_RegOnRspQryTradingAccount(OnRspQryTradingAccount_2);
            TdApi.CTP_RegOnRtnInstrumentStatus(OnRtnInstrumentStatus_2);
            TdApi.CTP_RegOnRtnOrder(OnRtnOrder_2);
            TdApi.CTP_RegOnRtnQuote(OnRtnQuote_2);
            TdApi.CTP_RegOnRtnTrade(OnRtnTrade_2);
        }

        ~TradeApi()
        {
            Dispose();
        }

        public void Dispose()
        {
            lock (locker)
            {
                GC.SuppressFinalize(this);
            }
        }

        public void Connect()
        {
            lock (locker)
            {
                TdApi.TD_Connect();
            }
        }

        public void Disconnect()
        {
            lock (locker)
            {                
                TdApi.TD_Disconnect();
            }
        }

        public int SendOrder(
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
            TThostFtdcVolumeConditionType VolumeCondition)
        {
            return TdApi.TD_SendOrder(
               OrderRef,
               szInstrument,
               Direction,
               szCombOffsetFlag,
               szCombHedgeFlag,
               VolumeTotalOriginal,
               LimitPrice,
               OrderPriceType,
               TimeCondition,
               ContingentCondition,
               StopPrice,
               VolumeCondition);
        }

        public void CancelOrder(string Instrument, TThostFtdcDirectionType Direction, string OffsetFlag)
        {
            TdApi.TD_CancelOrder(Instrument, Direction, OffsetFlag);
        }


        public void ReqQryTradingAccount()
        {
            TdApi.TD_ReqQryTradingAccount();
        }
		
        public void ReqQryDepthMarketData(string szInstrument)
        {
            TdApi.TD_ReqQryDepthMarketData(szInstrument);
        }

        public void ReqQryInstrument(string szInstrument)
        {
            TdApi.TD_ReqQryInstrument(szInstrument);
        }

        public void ReqQryInvestorPosition(string szInstrument)
        {
            TdApi.TD_ReqQryInvestorPosition(szInstrument);
        }

        public void ReqQryInvestorPositionDetail(string szInstrument)
        {
            TdApi.TD_ReqQryInvestorPositionDetail(szInstrument);
        }

        public void ReqQryInstrumentCommissionRate(string szInstrument)
        {
            TdApi.TD_ReqQryInstrumentCommissionRate(szInstrument);
        }

        public void ReqQryInstrumentMarginRate(string szInstrument, TThostFtdcHedgeFlagType HedgeFlag)
        {
            TdApi.TD_ReqQryInstrumentMarginRate(szInstrument, HedgeFlag);
        }

        public void ReqQrySettlementInfo(string szTradingDay)
        {
            TdApi.TD_ReqQrySettlementInfo(szTradingDay);
        }

        public void ReqQryOrder(string szInstrument)
        {
            TdApi.TD_ReqQryOrder(szInstrument);
        }

        public void ReqQryTrade(string szInstrument)
        {
            TdApi.TD_ReqQryTrade(szInstrument);
        }
    }
}
