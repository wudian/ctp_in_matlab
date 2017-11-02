using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2CTP
{
    public class MdApi
    {

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRtnDepthMarketData_Tick")]
        public static extern void CTP_RegOnRtnDepthMarketData_Tick(fnOnTick pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRtnDepthMarketData_KLine")]
        public static extern void CTP_RegOnRtnDepthMarketData_KLine(fnOnKLine pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnHistory_Tick")]
        public static extern void CTP_RegOnHistory_Tick(fnOnTick pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnHistory_KLine")]
        public static extern void CTP_RegOnHistory_KLine(fnOnKLine pCallback);


        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Subscribe")]
        public static extern void MD_Subscribe(string inst, string period);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Unsubscribe")]
        public static extern void MD_Unsubscribe(string inst, string period);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_SubscribeHistory")] // 订阅历史数据
        public static extern void MD_SubscribeHistory(string inst, string period, string beginTime, string endTime);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRtnForQuoteRsp")]
        public static extern void CTP_RegOnRtnForQuoteRsp(fnOnRtnForQuoteRsp pCallback);


        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Connect")]
        public static extern void MD_Connect();

        
        [DllImport(CommApi.DllFileName, EntryPoint = "MD_SubscribeQuote")]
        public static extern void MD_SubscribeQuote(string inst, string szExchange);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_UnsubscribeQuote")]
        public static extern void MD_UnsubscribeQuote(string inst, string szExchange);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Disconnect")]
        public static extern void MD_Disconnect();
    }
}
