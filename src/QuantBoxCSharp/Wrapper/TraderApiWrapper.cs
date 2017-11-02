using QuantBoxCSharp.Callback;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Text;

namespace QuantBoxCSharp
{
    public class TraderApiWrapper : IDisposable
    {
        public event OnConnectHandler OnConnect;
        public event OnDisconnectHandler OnDisconnect;
        public event OnErrRtnOrderActionHandler OnErrRtnOrderAction;
        public event OnErrRtnOrderInsertHandler OnErrRtnOrderInsert;
        public event OnRspErrorHandler OnRspError;
        public event OnRspOrderActionHandler OnRspOrderAction;
        public event OnRspOrderInsertHandler OnRspOrderInsert;
        public event OnRspQryDepthMarketDataHandler OnRspQryDepthMarketData;
        public event OnRspQryInstrumentHandler OnRspQryInstrument;
        public event OnRspQryInstrumentCommissionRateHandler OnRspQryInstrumentCommissionRate;
        public event OnRspQryInstrumentMarginRateHandler OnRspQryInstrumentMarginRate;
        public event OnRspQryInvestorPositionHandler OnRspQryInvestorPosition;
        public event OnRspQryInvestorPositionDetailHandler OnRspQryInvestorPositionDetail;
        public event OnRspQrySettlementInfoHandler OnRspQrySettlementInfo; // 查结算
        public event OnRspQryOrderHandler OnRspQryOrder; // 查委托
        public event OnRspQryTradeHandler OnRspQryTrade; // 查成交
        public event OnRspQryTradingAccountHandler OnRspQryTradingAccount;
        public event OnRtnInstrumentStatusHandler OnRtnInstrumentStatus;
        public event OnRtnOrderHandler OnRtnOrder;
        public event OnRtnTradeHandler OnRtnTrade;
       
        private TradeApi m_Api;

        public TraderApiWrapper()
        {            
            m_Api = new TradeApi();

            m_Api.OnConnect = OnConnect_callback;
            m_Api.OnDisconnect = OnDisconnect_callback;
            m_Api.OnRspError = OnRspError_callback;

            m_Api.OnErrRtnOrderAction = OnErrRtnOrderAction_callback;
            m_Api.OnErrRtnOrderInsert = OnErrRtnOrderInsert_callback;
            m_Api.OnRspOrderAction = OnRspOrderAction_callback;
            m_Api.OnRspOrderInsert = OnRspOrderInsert_callback;
            m_Api.OnRspQryDepthMarketData = OnRspQryDepthMarketData_callback;
            m_Api.OnRspQryInstrument = OnRspQryInstrument_callback;
            m_Api.OnRspQryInstrumentCommissionRate = OnRspQryInstrumentCommissionRate_callback;
            m_Api.OnRspQryInstrumentMarginRate = OnRspQryInstrumentMarginRate_callback;
            m_Api.OnRspQryInvestorPosition = OnRspQryInvestorPosition_callback;
            m_Api.OnRspQryInvestorPositionDetail = OnRspQryInvestorPositionDetail_callback;
            m_Api.OnRspQryOrder = OnRspQryOrder_callback;
            m_Api.OnRspQryTrade = OnRspQryTrade_callback;
            m_Api.OnRspQryTradingAccount = OnRspQryTradingAccount_callback;
            m_Api.OnRtnInstrumentStatus = OnRtnInstrumentStatus_callback;
            m_Api.OnRtnOrder = OnRtnOrder_callback;
            m_Api.OnRtnTrade = OnRtnTrade_callback;

            m_Api.CTP_RegTD();
        }

        private bool m_disposed = false;

        
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!m_disposed)
            {
                if (disposing)
                {
                    // Free other state (managed objects).
                }
                // Free your own state (unmanaged objects).
                // Set large fields to null.
                Disconnect();
                m_disposed = true;
            }
            //base.Dispose(disposing);
        }

        // Use C# destructor syntax for finalization code.
        ~TraderApiWrapper()
        {
            Dispose(true);
        }

        public void Connect()
        {
            m_Api.Connect();
        }

        public void Disconnect()
        {
            m_Api.Disconnect();
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
            return m_Api.SendOrder(
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
            m_Api.CancelOrder(Instrument, Direction, OffsetFlag);
        }

       

        public void ReqQryTradingAccount()
        {
            m_Api.ReqQryTradingAccount();
        }

        public void ReqQryDepthMarketData(string szInstrument)
        {
            m_Api.ReqQryDepthMarketData(szInstrument);
        }

        public void ReqQryInvestorPosition(string szInstrument)
        {
            m_Api.ReqQryInvestorPosition(szInstrument);
        }

        public void ReqQryInvestorPositionDetail(string szInstrument)
        {
            m_Api.ReqQryInvestorPositionDetail(szInstrument);
        }

        public void ReqQryInstrument(string szInstrument)
        {
            m_Api.ReqQryInstrument(szInstrument);
        }

        public void ReqQryInstrumentCommissionRate(string szInstrument)
        {
            m_Api.ReqQryInstrumentCommissionRate(szInstrument);
        }

        public void ReqQryInstrumentMarginRate(string szInstrument, TThostFtdcHedgeFlagType HedgeFlag)
        {
            m_Api.ReqQryInstrumentMarginRate(szInstrument, HedgeFlag);
        }

        public void ReqQrySettlementInfo(string szTradingDay)
        {
            m_Api.ReqQrySettlementInfo(szTradingDay);
        }

        public void ReqQryOrder(string szInstrument)
        {
            m_Api.ReqQryOrder(szInstrument);
        }

        public void ReqQryTrade(string szInstrument)
        {
            m_Api.ReqQryTrade(szInstrument);
        }
        
        private void OnConnect_callback(object sender, ConnectionStatus result)
        {
            if (null != OnConnect)
            {
                try
                {
                    OnConnect(this, new OnConnectArgs(result));
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("TraderApiWrapper::OnConnect_callback:" + ex.ToString());
                }
            }
        }

        private void OnDisconnect_callback(object sender, ref CThostFtdcRspInfoField pRspInfo, ConnectionStatus step)
        {  
            if (null != OnDisconnect)
            {                
                try
                {
                    OnDisconnect(this, new OnDisconnectArgs( ref pRspInfo, step));
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("TraderApiWrapper::OnDisconnect_callback:" + ex.ToString());
                }
            }
        }

        private void OnErrRtnOrderAction_callback(object sender,ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo)
        {
            if (null != OnErrRtnOrderAction)
            {
                OnErrRtnOrderAction(this, new OnErrRtnOrderActionArgs(ref pOrderAction, ref pRspInfo));
            }
        }

        private void OnErrRtnOrderInsert_callback(object sender,ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo)
        {
            if (null != OnErrRtnOrderInsert)
            {
                OnErrRtnOrderInsert(this, new OnErrRtnOrderInsertArgs(ref pInputOrder, ref pRspInfo));
            }
        }

        private void OnRspError_callback(object sender, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspError)
            {
                OnRspError(this,new OnRspErrorArgs(ref pRspInfo,nRequestID,bIsLast));
            }
        }

        private void OnRspOrderAction_callback(object sender,ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspOrderAction)
            {
                OnRspOrderAction(this, new OnRspOrderActionArgs(ref pInputOrderAction, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRspOrderInsert_callback(object sender,ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspOrderInsert)
            {
                OnRspOrderInsert(this, new OnRspOrderInsertArgs(ref pInputOrder, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRspQryDepthMarketData_callback(object sender,ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQryDepthMarketData)
            {
                OnRspQryDepthMarketData(this, new OnRspQryDepthMarketDataArgs(ref pDepthMarketData, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRspQryInstrument_callback(object sender,ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQryInstrument)
            {
                OnRspQryInstrument(this, new OnRspQryInstrumentArgs(ref pInstrument, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRspQryInstrumentCommissionRate_callback(object sender,ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQryInstrumentCommissionRate)
            {
                OnRspQryInstrumentCommissionRate(this, new OnRspQryInstrumentCommissionRateArgs(ref pInstrumentCommissionRate, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRspQryInstrumentMarginRate_callback(object sender,ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQryInstrumentMarginRate)
            {
                OnRspQryInstrumentMarginRate(this, new OnRspQryInstrumentMarginRateArgs(ref pInstrumentMarginRate, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRspQryInvestorPosition_callback(object sender,ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQryInvestorPosition)
            {
                OnRspQryInvestorPosition(this, new OnRspQryInvestorPositionArgs(ref pInvestorPosition, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRspQryInvestorPositionDetail_callback(object sender,ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQryInvestorPositionDetail)
            {
                OnRspQryInvestorPositionDetail(this, new OnRspQryInvestorPositionDetailArgs(ref pInvestorPositionDetail, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRspQrySettlementInfo_callback(object sender,ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQrySettlementInfo)
            {
                OnRspQrySettlementInfo(this, new OnRspQrySettlementInfoArgs(ref pSettlementInfo, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRspQryOrder_callback(object sender,ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQryOrder)
            {
                try
                {
                    OnRspQryOrder(this, new OnRspQryOrderArgs(ref pOrder, ref pRspInfo, nRequestID, bIsLast));
                }
                catch (Exception ex)
                {
                    MessageBox.Show("TraderApiWrapper::OnRspQryOrder_callback:" + ex.ToString());
                }
            }
        }

        private void OnRspQryTrade_callback(object sender,ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQryTrade)
            {
                try
                {
                    OnRspQryTrade(this, new OnRspQryTradeArgs(ref pTrade, ref pRspInfo, nRequestID, bIsLast));
                }
                catch (Exception ex)
                {
                    MessageBox.Show("TraderApiWrapper::OnRspQryTrade_callback:" + ex.ToString());
                }
            }
        }

        private void OnRspQryTradingAccount_callback(object sender,ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspQryTradingAccount)
            {
                OnRspQryTradingAccount(this, new OnRspQryTradingAccountArgs(ref pTradingAccount, ref pRspInfo, nRequestID, bIsLast));
            }
        }

        private void OnRtnInstrumentStatus_callback(object sender,ref CThostFtdcInstrumentStatusField pInstrumentStatus)
        {
            if (null != OnRtnInstrumentStatus)
            {
                OnRtnInstrumentStatus(this, new OnRtnInstrumentStatusArgs(ref pInstrumentStatus));
            }
        }

        private void OnRtnOrder_callback(object sender,ref CThostFtdcOrderField pOrder)
        {
            if (null != OnRtnOrder)
            {
                OnRtnOrder(this, new OnRtnOrderArgs(ref pOrder));
            }
        }

        private void OnRtnTrade_callback(object sender,ref CThostFtdcTradeField pTrade)
        {
            if (null != OnRtnTrade)
            {
                OnRtnTrade(this, new OnRtnTradeArgs(ref pTrade));
            }
        }
    }
}
