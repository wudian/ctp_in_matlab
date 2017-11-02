using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading;

namespace QuantBoxCSharp
{
    public class CTPMdApi
    {
        public event fnOnConnect     OnConnect_1;
        public event fnOnDisconnect  OnDisconnect_1;
        public event fnOnRspError    OnRspError_1;
        public event fnOnTick   OnRtnDepthMarketData_Tick_1;
        public event fnOnKLine  OnRtnDepthMarketData_KLine_1;
        public event fnOnTick   OnHistoryTick_1;
        public event fnOnKLine  OnHistoryKLine_1;
        

        public CTPMdApi()
        {            
        }

        public void Connect()
        {
            MdApi.MD_Connect();
        }

        public void CTP_RegMD()
        {
            MdApi.CTP_RegMDOnConnect(OnConnect_1);
            MdApi.CTP_RegMDOnDisconnect(OnDisconnect_1);
            MdApi.CTP_RegMDOnRspError(OnRspError_1);
            MdApi.CTP_RegOnRtnDepthMarketData_Tick(OnRtnDepthMarketData_Tick_1);
            MdApi.CTP_RegOnRtnDepthMarketData_KLine(OnRtnDepthMarketData_KLine_1);
            MdApi.CTP_RegOnHistory_Tick(OnHistoryTick_1);
            MdApi.CTP_RegOnHistory_KLine(OnHistoryKLine_1);            
        }
    }
}
