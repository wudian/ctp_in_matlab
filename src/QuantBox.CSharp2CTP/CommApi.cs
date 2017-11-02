using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2CTP
{
    public class CommApi
    {
        public const string DllFileName = "QuantBox.dll";

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_ReadConfigFile")]
        public static extern void CTP_ReadConfigFile(string path);
              

  
        // MD
        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegMDOnConnect")]
        public static extern void CTP_RegMDOnConnect(fnOnConnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegMDOnDisconnect")]
        public static extern void CTP_RegMDOnDisconnect(fnOnDisconnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegMDOnRspError")]
        public static extern void CTP_RegMDOnRspError(fnOnRspError pCallback);

        // TD
        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegTDOnConnect")]
        public static extern void CTP_RegTDOnConnect(fnOnConnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegTDOnDisconnect")]
        public static extern void CTP_RegTDOnDisconnect(fnOnDisconnect pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "CTP_RegTDOnRspError")]
        public static extern void CTP_RegTDOnRspError(fnOnRspError pCallback);
    }
}
