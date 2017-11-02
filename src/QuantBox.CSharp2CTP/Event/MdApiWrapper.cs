using QuantBox.CSharp2CTP.Callback;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading;

namespace QuantBox.CSharp2CTP.Event
{
    public class MdApiWrapper : IDisposable
    {
        public event OnConnectHandler OnConnect;
        public event OnDisconnectHandler OnDisconnect;
        public event OnRspErrorHandler OnRspError;

        public event OnTickHandler OnRtnDepthMarketData_Tick;
        public event OnKLineHandler OnRtnDepthMarketData_KLine;
        public event OnTickHandler OnHistoryTick;
        public event OnKLineHandler OnHistoryKLine;        
      
        private MarketDataApi m_Api;

        public MdApiWrapper()
        {
            m_Api = new MarketDataApi();

            m_Api.OnConnect = OnConnect_callback;
            m_Api.OnDisconnect = OnDisconnect_callback;
            m_Api.OnRspError = OnRspError_callback;

            m_Api.OnRtnDepthMarketData_Tick = OnRtnDepthMarketData_Tick_callback;
            m_Api.OnRtnDepthMarketData_KLine = OnRtnDepthMarketData_KLine_callback;
            m_Api.OnHistoryTick = OnHistoryTick_callback;
            m_Api.OnHistoryKLine = OnHistoryKLine_callback;           

            m_Api.CTP_RegMD();
        }

        // 析构
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private bool m_disposed = false;

        protected virtual void Dispose(bool disposing)
        {
            if (!m_disposed)
            {
                if (disposing)
                {
                    // Release managed resources
                }
                // Release unmanaged resources
                m_Api.Disconnect();
                m_Api.Dispose();
                m_disposed = true;
            }
        }

        ~MdApiWrapper()
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

        public void Subscribe(string inst, string period)
        {
            m_Api.Subscribe(inst, period);
        }

        public void Unsubscribe(string inst, string period)
        {
            m_Api.Unsubscribe(inst, period);
        }

        public void SubscribeHistory(string inst, string period, string beginTime, string endTime)
        {
            m_Api.SubscribeHistory(inst, period, beginTime, endTime);
        }

        private void OnConnect_callback(object sender,ref CThostFtdcRspUserLoginField pRspUserLogin, ConnectionStatus result)
        {
            if (null != OnConnect)
            {
                try
                {
                    OnConnect(this, new OnConnectArgs(ref pRspUserLogin, result));
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("MdApiWrapper::OnConnect_callback:" + ex.ToString());
                }
            }
        }

        private void OnDisconnect_callback(object sender,ref CThostFtdcRspInfoField pRspInfo, ConnectionStatus step)
        {
            if (null != OnDisconnect)
            {
                try
                {
                    OnDisconnect(this, new OnDisconnectArgs(ref pRspInfo, step));
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("MdApiWrapper::OnDisconnect_callback:" + ex.ToString());
                }
            }
        }

        private void OnRspError_callback(object sender,ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != OnRspError)
            {
                try
                {
                    OnRspError(this, new OnRspErrorArgs(ref pRspInfo, nRequestID, bIsLast));
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("MdApiWrapper::OnRspError_callback:" + ex.ToString());
                }
            }
        }

        private void OnHistoryTick_callback(object sender, ref Tick pTick)
        {
            try
            {
                OnHistoryTick(this, new OnTickArgs(ref pTick));
            }
            catch (System.Exception)
            {
                Thread.Sleep(5);
                try
                {
                    OnHistoryTick(this, new OnTickArgs(ref pTick));
                }
                catch (System.Exception)
                {
                    Thread.Sleep(5);
                    try
                    {
                        OnHistoryTick(this, new OnTickArgs(ref pTick));
                    }
                    catch (System.Exception)
                    {
                        Thread.Sleep(5);
                        try
                        {
                            OnHistoryTick(this, new OnTickArgs(ref pTick));
                        }
                        catch (System.Exception )
                        {
                            //MessageBox.Show("MdApiWrapper::OnRtnDepthMarketData_callback:" + ex.ToString());
                        }
                    }
                }
            }
        }

        private void OnHistoryKLine_callback(object sender, ref K_Line pKLine)
        {   
            try
            {
                OnHistoryKLine(this, new OnKLineArgs(ref pKLine));
            }
            catch (System.Exception)
            {
                Thread.Sleep(5);
                try
                {
                    OnHistoryKLine(this, new OnKLineArgs(ref pKLine));
                }
                catch (System.Exception)
                {
                    Thread.Sleep(5);
                    try
                    {
                        OnHistoryKLine(this, new OnKLineArgs(ref pKLine));
                    }
                    catch (System.Exception)
                    {
                        Thread.Sleep(5);
                        try
                        {
                            OnHistoryKLine(this, new OnKLineArgs(ref pKLine));
                        }
                        catch (System.Exception)
                        {
                            //MessageBox.Show("MdApiWrapper::OnRtnDepthMarketData_callback:" + ex.ToString());
                        }
                    }
                }
            }
        }
    

        private void OnRtnDepthMarketData_Tick_callback(object sender, ref Tick pDepthMarketData)
        {
            try
            {
                OnRtnDepthMarketData_Tick(this, new OnTickArgs(ref pDepthMarketData));
            }
            catch (System.Exception)
            {
                Thread.Sleep(5);
                try
                {
                    OnRtnDepthMarketData_Tick(this, new OnTickArgs(ref pDepthMarketData));
                }
                catch (System.Exception)
                {
                    Thread.Sleep(5);
                    try
                    {
                        OnRtnDepthMarketData_Tick(this, new OnTickArgs(ref pDepthMarketData));
                    }
                    catch (System.Exception)
                    {
                        Thread.Sleep(5);
                        try
                        {
                            OnRtnDepthMarketData_Tick(this, new OnTickArgs(ref pDepthMarketData));
                        }
                        catch (System.Exception)
                        {
                            //MessageBox.Show("MdApiWrapper::OnRtnDepthMarketData_Tick_callback:" + ex.ToString());
                        }
                    }
                }
            }
        }


        private void OnRtnDepthMarketData_KLine_callback(object sender, ref K_Line pKLine)
        {
            try
            {
                OnRtnDepthMarketData_KLine(this, new OnKLineArgs(ref pKLine));
            }
            catch (System.Exception)
            {
                Thread.Sleep(5);
                try
                {
                    OnRtnDepthMarketData_KLine(this, new OnKLineArgs(ref pKLine));
                }
                catch (System.Exception)
                {
                    Thread.Sleep(5);
                    try
                    {
                        OnRtnDepthMarketData_KLine(this, new OnKLineArgs(ref pKLine));
                    }
                    catch (System.Exception)
                    {
                        Thread.Sleep(5);
                        try
                        {
                            OnRtnDepthMarketData_KLine(this, new OnKLineArgs(ref pKLine));
                        }
                        catch (System.Exception )
                        {
                            //MessageBox.Show("MdApiWrapper::OnRtnDepthMarketData_callback:" + ex.ToString());
                        }
                    }
                }
            }
        }
    }
}
