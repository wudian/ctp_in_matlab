using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace QuantBoxCSharp
{
    public class MdWrapper
    {
        public MdWrapper()
        {
            MdApi.CTP_RegOnRtnDepthMarketData_Tick(OnRtnDepthMarketData_Tick);
            MdApi.CTP_RegOnRtnDepthMarketData_KLine(OnRtnDepthMarketData_KLine);
            MdApi.CTP_RegOnHistory_Tick(OnHistoryTick);
            MdApi.CTP_RegOnHistory_KLine(OnHistoryKLine);

            MdApi.CTP_RegMDOnConnect(OnMdConnect);
            MdApi.CTP_RegMDOnDisconnect(OnMdDisconnect);
            MdApi.CTP_RegMDOnRspError(OnMdRspError); 
        }

        public event OnConnectHandler MdConnect;
        public event OnDisconnectHandler MdDisconnect;
        public event OnRspErrorHandler MdRspError;

        public event OnTickHandler RtnDepthMarketData_Tick;    
        public event OnKLineHandler RtnDepthMarketData_KLine;
        public event OnTickHandler HistoryTick;
        public event OnKLineHandler HistoryKLine;

        private object locker = new object();

        private void OnMdConnect(ref CThostFtdcRspUserLoginField pRspUserLogin, ConnectionStatus result)
        {
            if (null != MdConnect)
            {
                try
                {
                    MdConnect(this, new OnConnectArgs(ref pRspUserLogin, result));
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("MdApiWrapper::OnConnect_callback:" + ex.ToString());
                }
            }
        }

        private void OnMdDisconnect(ref CThostFtdcRspInfoField pRspInfo, ConnectionStatus step)
        {
            if (null != MdDisconnect)
            {
                try
                {
                    MdDisconnect(this, new OnDisconnectArgs(ref pRspInfo, step));
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("MdApiWrapper::OnDisconnect_callback:" + ex.ToString());
                }
            }
        }

        private void OnMdRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            if (null != MdRspError)
            {
                try
                {
                    MdRspError(this, new OnRspErrorArgs(ref pRspInfo, nRequestID, bIsLast));
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("MdApiWrapper::OnRspError_callback:" + ex.ToString());
                }
            }
        }

        private void OnRtnDepthMarketData_Tick(ref CTick pTick)
        {
            try
            {
                RtnDepthMarketData_Tick(this, new OnTickArgs(ref pTick));
            }
            catch (System.Exception ex)
            {
                Thread.Sleep(5);
                try
                {
                    RtnDepthMarketData_Tick(this, new OnTickArgs(ref pTick));
                }
                catch (System.Exception)
                {
                    Thread.Sleep(5);
                    try
                    {
                        RtnDepthMarketData_Tick(this, new OnTickArgs(ref pTick));
                    }
                    catch (System.Exception)
                    {
                        Thread.Sleep(5);
                        try
                        {
                            RtnDepthMarketData_Tick(this, new OnTickArgs(ref pTick));
                        }
                        catch (System.Exception)
                        {
                            MessageBox.Show("MdApiWrapper::OnRtnDepthMarketData_Tick_callback:" + ex.ToString());
                        }
                    }
                }
            }
        }

        private void OnRtnDepthMarketData_KLine(ref CKLine pKLine)
        {
            try
            {
                RtnDepthMarketData_KLine(this, new OnKLineArgs(ref pKLine));
            }
            catch (System.Exception)
            {
                Thread.Sleep(5);
                try
                {
                    RtnDepthMarketData_KLine(this, new OnKLineArgs(ref pKLine));
                }
                catch (System.Exception)
                {
                    Thread.Sleep(5);
                    try
                    {
                        RtnDepthMarketData_KLine(this, new OnKLineArgs(ref pKLine));
                    }
                    catch (System.Exception)
                    {
                        Thread.Sleep(5);
                        try
                        {
                            RtnDepthMarketData_KLine(this, new OnKLineArgs(ref pKLine));
                        }
                        catch (System.Exception)
                        {
                            //MessageBox.Show("MdApiWrapper::OnRtnDepthMarketData_callback:" + ex.ToString());
                        }
                    }
                }
            }
        }

        private void OnHistoryTick(ref CTick pTick)
        {
            try
            {
                HistoryTick(this, new OnTickArgs(ref pTick));
            }
            catch (System.Exception)
            {
                Thread.Sleep(5);
                try
                {
                    HistoryTick(this, new OnTickArgs(ref pTick));
                }
                catch (System.Exception)
                {
                    Thread.Sleep(5);
                    try
                    {
                        HistoryTick(this, new OnTickArgs(ref pTick));
                    }
                    catch (System.Exception)
                    {
                        Thread.Sleep(5);
                        try
                        {
                            HistoryTick(this, new OnTickArgs(ref pTick));
                        }
                        catch (System.Exception)
                        {
                            //MessageBox.Show("MdApiWrapper::OnRtnDepthMarketData_callback:" + ex.ToString());
                        }
                    }
                }
            }
        }

        private void OnHistoryKLine(ref CKLine pKLine)
        {
            try
            {
                HistoryKLine(this, new OnKLineArgs(ref pKLine));
            }
            catch (System.Exception)
            {
                Thread.Sleep(5);
                try
                {
                    HistoryKLine(this, new OnKLineArgs(ref pKLine));
                }
                catch (System.Exception)
                {
                    Thread.Sleep(5);
                    try
                    {
                        HistoryKLine(this, new OnKLineArgs(ref pKLine));
                    }
                    catch (System.Exception)
                    {
                        Thread.Sleep(5);
                        try
                        {
                            HistoryKLine(this, new OnKLineArgs(ref pKLine));
                        }
                        catch (System.Exception)
                        {
                            //MessageBox.Show("MdApiWrapper::OnRtnDepthMarketData_callback:" + ex.ToString());
                        }
                    }
                }
            }
        }
    }
}
