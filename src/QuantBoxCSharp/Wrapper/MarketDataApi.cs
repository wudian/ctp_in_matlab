using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QuantBoxCSharp.Callback
{
    public class MarketDataApi : BaseApi
    {
        private object locker = new object();
        
        private fnOnTick OnRtnDepthMarketData_Tick_1;
        private fnOnKLine OnRtnDepthMarketData_KLine_1;
        private fnOnTick OnHistoryTick_1;
        private fnOnKLine OnHistoryKLine_1;
        
        private fnOnRtnForQuoteRsp OnRtnForQuoteRsp_1;

        private QuantBoxCSharp.fnOnTick OnRtnDepthMarketData_Tick_2;
        private QuantBoxCSharp.fnOnKLine OnRtnDepthMarketData_KLine_2;
        private QuantBoxCSharp.fnOnTick OnHistoryTick_2;
        private QuantBoxCSharp.fnOnKLine OnHistoryKLine_2;

        public fnOnTick OnRtnDepthMarketData_Tick
        {
            set
            {
                OnRtnDepthMarketData_Tick_1 = value;
                OnRtnDepthMarketData_Tick_2 = OnRtnDepthMarketData_Tick_3;
            }
        }

        public fnOnKLine OnRtnDepthMarketData_KLine
        {
            set
            {
                OnRtnDepthMarketData_KLine_1 = value;
                OnRtnDepthMarketData_KLine_2 = OnRtnDepthMarketData_KLine_3;
            }
        }

        public fnOnTick OnHistoryTick
        {
            set
            {
                OnHistoryTick_1 = value;
                OnHistoryTick_2 = OnHistoryTick_3;
            }
        }

        public fnOnKLine OnHistoryKLine
        {
            set
            {
                OnHistoryKLine_1 = value;
                OnHistoryKLine_2 = OnHistoryKLine_3;
            }
        }        

        private void OnRtnDepthMarketData_Tick_3(ref CTick pDepthMarketData_Tick)
        {
            OnRtnDepthMarketData_Tick_1(this, ref pDepthMarketData_Tick);
        }

        private void OnRtnDepthMarketData_KLine_3(ref CKLine pDepthMarketData_KLine)
        {
            OnRtnDepthMarketData_KLine_1(this, ref pDepthMarketData_KLine);
        }

        private void OnHistoryTick_3(ref CTick pTick)
        {
            OnHistoryTick_1(this, ref pTick);
        }

        private void OnHistoryKLine_3(ref CKLine pKLine)
        {
            OnHistoryKLine_1(this, ref pKLine);
        }
        
        protected override void OnConnect_3(ConnectionStatus result)
        {
            IsConnected = false;
            if (result == ConnectionStatus.Logined)
            {
                IsConnected = true;
            }
            OnConnect_1(this, result);
        }

        public MarketDataApi() : base()
        {
                      
        }

        public void CTP_RegMD()
        {
            MdApi.CTP_RegOnRtnDepthMarketData_Tick(OnRtnDepthMarketData_Tick_2);
            MdApi.CTP_RegOnRtnDepthMarketData_KLine(OnRtnDepthMarketData_KLine_2);
            MdApi.CTP_RegOnHistory_Tick(OnHistoryTick_2);
            MdApi.CTP_RegOnHistory_KLine(OnHistoryKLine_2);            

            MdApi.CTP_RegMDOnConnect(OnConnect_2);
            MdApi.CTP_RegMDOnDisconnect(OnDisconnect_2);
            MdApi.CTP_RegMDOnRspError(OnRspError_2);            
        }

        ~MarketDataApi()
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
                MdApi.MD_Connect();
            }            
        }

        public void Disconnect()
        {
            lock (locker)
            {
                MdApi.MD_Disconnect();
            }
        }

        public virtual void Subscribe(string inst, string period)
        {
            lock (locker)
            {
                MdApi.MD_Subscribe(inst, period);
               
            }
        }

        public virtual void Unsubscribe(string inst, string period)
        {
            lock (locker)
            {
                MdApi.MD_Unsubscribe(inst, period);
            }
        }

        public void SubscribeHistory(string inst, string period, string beginTime, string endTime)
        {
            lock (locker)
            {
                MdApi.MD_SubscribeHistory(inst, period, beginTime, endTime);
            }
        }
    }
}
