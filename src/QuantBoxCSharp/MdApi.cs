using System;
using System.Runtime.InteropServices;

namespace QuantBoxCSharp
{
    public class MdApi
    {
        // 行情API
        [DllImport("QuantBox.dll", EntryPoint = "MD_Connect")]
        public static extern void MD_Connect();      

        [DllImport("QuantBox.dll", EntryPoint = "MD_Subscribe")]
        public static extern void MD_Subscribe(string inst, string period);

        [DllImport("QuantBox.dll", EntryPoint = "MD_Unsubscribe")]
        public static extern void MD_Unsubscribe(string inst, string period);

        [DllImport("QuantBox.dll", EntryPoint = "MD_SubscribeHistory")] // 订阅历史数据
        public static extern void MD_SubscribeHistory(string inst, string period, string beginTime, string endTime);        

        [DllImport("QuantBox.dll", EntryPoint = "MD_Disconnect")]
        public static extern void MD_Disconnect();


        // 注册行情回调
        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegMDOnConnect")]
        public static extern void CTP_RegMDOnConnect(fnOnConnect pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegMDOnDisconnect")]
        public static extern void CTP_RegMDOnDisconnect(fnOnDisconnect pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegMDOnRspError")]
        public static extern void CTP_RegMDOnRspError(fnOnRspError pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRtnDepthMarketData_Tick")]
        public static extern void CTP_RegOnRtnDepthMarketData_Tick(fnOnTick pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnRtnDepthMarketData_KLine")]
        public static extern void CTP_RegOnRtnDepthMarketData_KLine(fnOnKLine pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnHistory_Tick")]
        public static extern void CTP_RegOnHistory_Tick(fnOnTick pCallback);

        [DllImport("QuantBox.dll", EntryPoint = "CTP_RegOnHistory_KLine")]
        public static extern void CTP_RegOnHistory_KLine(fnOnKLine pCallback);
    }
}
