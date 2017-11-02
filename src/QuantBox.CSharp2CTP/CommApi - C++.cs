using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2CTP
{
    public class CommApi
    {
        public const string DllFileName = "QuantBox.dll";

        // MD
        [DllImport(CommApi.DllFileName, EntryPoint = "?RegisterCallback@CMdUserApi@@QAEXP6GXPAXPAUCThostFtdcRspUserLoginField@@W4ConnectionStatus@@@Z@Z")]
        public static extern void RegisterCallback(fnOnConnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "?RegisterCallback@CMdUserApi@@QAEXP6GXPAXPAUCThostFtdcRspInfoField@@W4ConnectionStatus@@@Z@Z")]
        public static extern void RegisterCallback(fnOnDisconnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "?RegisterCallback@CMdUserApi@@QAEXP6GXPAXPAUCThostFtdcRspInfoField@@H_N@Z@Z")]
        public static extern void RegisterCallback(fnOnRspError pCallback);

        // TD
        [DllImport(CommApi.DllFileName, EntryPoint = "?RegisterCallback@CTraderApi@@QAEXP6GXPAXPAUCThostFtdcRspUserLoginField@@W4ConnectionStatus@@@Z@Z")]
        public static extern void RegisterCallback(fnOnConnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "?RegisterCallback@CTraderApi@@QAEXP6GXPAXPAUCThostFtdcRspInfoField@@W4ConnectionStatus@@@Z@Z")]
        public static extern void RegisterCallback(fnOnDisconnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "?RegisterCallback@CTraderApi@@QAEXP6GXPAXPAUCThostFtdcSettlementInfoField@@PAUCThostFtdcRspInfoField@@H_N@Z@Z")]
        public static extern void RegisterCallback(fnOnRspError pCallback);
    }
}
