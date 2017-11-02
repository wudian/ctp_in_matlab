using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2CTP
{
    public class MdApi
    {
        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRtnDepthMarketData")]
        public static extern void CTP_RegOnRtnDepthMarketData(IntPtr pMdApi, fnOnRtnDepthMarketData pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegOnRtnForQuoteRsp")]
        public static extern void CTP_RegOnRtnForQuoteRsp(IntPtr pMdApi, fnOnRtnForQuoteRsp pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_CreateMdApi")]
        public static extern IntPtr MD_CreateMdApi();

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Connect")]
        public static extern void MD_Connect(IntPtr pMdApi, string szPath, string szAddresses, string szBrokerId, string szInvestorId, string szPassword);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Subscribe")]
        public static extern void MD_Subscribe(IntPtr pMdApi, string inst, string szExchange);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Unsubscribe")]
        public static extern void MD_Unsubscribe(IntPtr pMdApi, string inst, string szExchange);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_SubscribeQuote")]
        public static extern void MD_SubscribeQuote(IntPtr pMdApi, string inst, string szExchange);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_UnsubscribeQuote")]
        public static extern void MD_UnsubscribeQuote(IntPtr pMdApi, string inst, string szExchange);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_Disconnect")]
        public static extern void MD_Disconnect(IntPtr pMdApi);

        [DllImport(CommApi.DllFileName, EntryPoint = "MD_ReleaseMdApi")]
        public static extern void MD_ReleaseMdApi(IntPtr pMdApi);
    }
}
