using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using QuantBoxCSharp;
using System.Threading;

namespace ConsoleApplication4
{
    class Program
    {

        public static void OnConnect(ref CThostFtdcRspUserLoginField pRspUserLogin, ConnectionStatus result)
        {
            Console.WriteLine("{0}", result);
        }

        public static void OnRtnDepthMarketData_Tick(ref CTick pTick)
        {
            Console.WriteLine("{0} {1}", pTick.InstrumentID, pTick.ExchangeTime);
        }

        static void Main(string[] args)
        {
            MdApi.CTP_ReadConfigFile("F:\\CTP-MATLAB\\bin\\ConfigFile.xml");

            MdApi.CTP_RegMDOnConnect(OnConnect);
            MdApi.CTP_RegOnRtnDepthMarketData_Tick(OnRtnDepthMarketData_Tick);
            MdApi.MD_Connect();
            TdApi.TD_Connect();

            while (true)
            { 
            }
        }
    }
}
