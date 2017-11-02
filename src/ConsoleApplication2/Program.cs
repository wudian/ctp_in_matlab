using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using QuantBoxCSharp;
//using QuantBox.CSharp2CTP;
//using QuantBox.CSharp2CTP.Event;
using System.Threading;

namespace ConsoleApplication2
{
    class Program
    {
        public static void OnConnect(object sender, OnConnectArgs e)
        {
            Console.WriteLine("{0}", e.result);
        }

        public static void OnRtnDepthMarketData_Tick(object sender, OnTickArgs e)
        {
            Console.WriteLine("{0} {1}", e.pTick.InstrumentID, e.pTick.ExchangeTime);
        }
        public static void OnRtnDepthMarketData_KLine(object sender, OnKLineArgs e)
        {
            Console.WriteLine("{0} {1}", e.pKLine.InstrumentID, e.pKLine.ExchangeTime);
        }

        public static void OnHistoryTick(object sender, OnTickArgs e)
        {
            Console.WriteLine("{0}: {1}", e.pTick.InstrumentID, e.pTick.ExchangeTime);
        }
        public static void OnHistoryKLine(object sender, OnKLineArgs e)
        {
            Console.WriteLine("{0} {1}", e.pKLine.InstrumentID, e.pKLine.ExchangeTime);
        }

        static void Main(string[] args)
        {
            //Thread.Sleep(10000);
           

            MdApiWrapper md = new MdApiWrapper();
            md.OnConnect += new OnConnectHandler(OnConnect);
            md.OnRtnDepthMarketData_Tick += new OnTickHandler(OnRtnDepthMarketData_Tick);
            md.OnRtnDepthMarketData_KLine += new OnKLineHandler(OnRtnDepthMarketData_KLine);
            md.OnHistoryTick += new OnTickHandler(OnHistoryTick);
            md.OnHistoryKLine += new OnKLineHandler(OnHistoryKLine);

            TraderApiWrapper td = new TraderApiWrapper();
            td.Connect();
            md.Connect();


            //md.SubscribeHistory("IF1408", BarLength.Tick1, "20140804 10:00:00", "20140804 11:00:00");
            //md.Subscribe("a1409,a1411,SR407,SR409,SR411,a14ru07,v1409,rb1409,wr1409,c1409,a1503,b1409,y1409,l1409,m1409,p1409,CF409,TA409,ME409,PM409,FG409,OI409,WH409,RI409,j1409,zn1409,cu1409,v1407,rb1407,wr1407,c1407,a1501,b1407,y1407,l1407,m1407,p1407,CF407,TA407,ME407,PM407,FG407,OI407,WH407,RI407,j1407,au1407,zn1410,TC407,TC408,TC409,ag1409,pb1409,al1409,fu1409,ru1409,cu1410,v1410,rb1410,wr1410,l1410,p1410,TA410,ME410,ag1410,FG410,j1410,pb1410,au1410,al1410,fu1410,ru1410,i1410,TC410,i1407,i1408,i1409,zn1407,cu1407,ag1407,pb1407,al1407,ru1407,bu1409,bu1412,bu1503,bu1506,bu1509,zn1411,cu1411,v1411,rb1411,wr1411,c1411,a1505,zn1408,cu1408,v1408,rb1408,wr1408,y1408,l1408,m1408,p1408,TA408,ME408,ag1408,FG408,j1408,pb1408,au1408,al1408,fu1408,ru1408,au1502,zn1503,cu1503,v1503,rb1503,wr1503,c1503,a1509,b1503,y1503,l1503,i1503,TC503,bu1603,m1503,p1503,CF503,SR503,TA503,ME503,PM503,v1504,rb1504,wr1504,l1504,i1504,TC504,bu1410,p1504,TA504,ME504,ag1504,FG504,j1504,pb1504,au1504,al1504,fu1504,ru1504,zn1505,cu1505,IF1407,b1411,y1411,l1411,i1411,TC411,m1411,p1411,CF411,TA411,ME411,PM411,ag1411,FG411,OI411,WH411,RI411,j1411,pb1411,al1411,fu1411,ru1411,SR501,v1505,rb1505,wr1505,c1505,a1511,b1505,y1505,l1505,i1505,TC505,bu1411,m1505,p1505,CF505,SR505,SR507,SR509,SR511,TA505,ME505,v1412,rb1412,wr1412,y1412,l1412,i1412,TC412,m1412,p1412,TA412,ME412,FG412,j1412,au1412,zn1412,cu1412,bu1512,ag1412,pb1412,al1412,fu1412,zn1502,cu1502,bu1408,ag1502,pb1502,al1502,ag1503,FG503,OI503,WH503,RI503,j1503,pb1503,au1503,al1503,fu1503,ru1503,zn1504,cu1504,IF1412,zn1501,cu1501,IF1409,v1501,rb1501,wr1501,c1501,a1507,b1501,y1501,l1501,i1501,TC501,bu1407,m1501,p1501,CF501,TA501,ME501,PM501,ag1501,FG501,OI501,WH501,RI501,j1501,pb1501,au1501,al1501,fu1501,ru1501,v1502,rb1502,wr1502,l1502,i1502,TC502,p1502,TA502,ME502,FG502,j1502,PM505,ag1505,FG505,OI505,WH505,RI505,j1505,pb1505,au1505,al1505,fu1505,ru1505,IF1408,v1506,rb1506,wr1506,l1506,i1506,TC506,p1506,TA506,ME506,FG506,j1506,au1506,zn1506,cu1506,bu1606,ag1506,pb1506,al1506,fu1506,ru1506,fu1507", "");

            //Thread.Sleep(10000);
            //try
            //{
            //    string s = td.QueryTrade("", TThostFtdcDirectionType.NIL, TThostFtdcOffsetFlagType.NIL);
            //    Console.WriteLine(s);
            //}
            //catch (System.Exception ex)
            //{
            //    string s = ex.ToString();
            //    Console.WriteLine(s);
            //}
            
            while (true)
                ;
        }
    }
}
