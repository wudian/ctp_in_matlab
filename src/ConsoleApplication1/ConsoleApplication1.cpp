
// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include "math.h"
#include "QuantBoxApi.h"
#include <map>
#include <string>
#include <queue>
#include <thread>
#include <boost/format.hpp>
#include <future>
//#include "MatlabEngine.h"
#include "gtest/gtest.h"
#include "MarketData.h"
#include "Enums.h"

using namespace std;
using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

map<string, mutex> g_mutex;
map<string, queue<double> > g_close;
map<string, condition_variable> condition;



void __stdcall OnConnect(wdConnectInfo *co)
{
	if (co->type ==  E_MD) {
		if (co->status == E_unconnected)
			cout << "行情断开 " << co->ErrorMsg << "\n";
		else if (co->status == E_logined)
			cout << "行情登陆成功\n";
	}
	else {
		if (co->status == E_unconnected)
			cout << "交易断开 " << co->ErrorMsg << "\n";
		else if (co->status == E_confirmed)
			cout << "交易登陆成功\n";
	}
	
}


void __stdcall OnRspQryInstrument(wdInstrument *inst)
{
	cout << "查合约:";
}

void __stdcall OnRspQrySettlementInfo(const char *pSettlementInfo)
{
	cout << pSettlementInfo << endl;
}


class QuickTest : public testing::Test {
protected:
	// Remember that SetUp() is run immediately before a test starts.
	// This is a good place to record the start time.
	virtual void SetUp() {
		start_time_ = time(NULL);

		
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	// check if the test was too slow.
	virtual void TearDown() {
		// Gets the time when the test finishes
		const time_t end_time = time(NULL);

		
		// Asserts that the test took no more than ~5 seconds.  Did you
		// know that you can use assertions in SetUp() and TearDown() as
		// well?
		//EXPECT_TRUE(end_time - start_time_ <= 5) << "The test took too long.";
	}

	// The UTC time (in seconds) when the test starts
	time_t start_time_;
};

TEST_F(QuickTest, Connect)
{
//#if 0
//	pMd->Connect("d:\\","tcp://asp-sim2-md1.financial-trading-platform.com:26213","2030","123456","888888");
//#elif 0 // 南华期货
//	pMd->Connect("d:\\","tcp://115.238.106.252:41213","1008","","");
//#elif 0 // 中信证券 范俊华
//	pMd->Connect("d:\\","tcp://ctpfz1-front1.citicsf.com:51205","5040","","");
//#elif 1
//	pMd->Connect("d:\\","tcp://ctpmn1-front1.citicsf.com:51213","1017","",""); //123456 888888
//#else // 小林
//	pMd->Connect("d:\\","tcp://203.110.179.220:41213","5040","",""); //91200168 123456
//#endif
//
//#if 0
//	pTd->Connect("d:\\","tcp://asp-sim2-front1.financial-trading-platform.com:26205","2030","123456","888888",THOST_TERT_RESTART,"","");
//#elif 0 // 南华期货
//	pTd->Connect("d:\\","tcp://115.238.106.252:41205","1008","90087415","173515",THOST_TERT_RESTART,"","");
//#else
//	pTd->Connect("d:\\","tcp://ctpmn1-front1.citicsf.com:51205","1017","00000015","123456",THOST_TERT_QUICK,"","");
//#endif
}

TEST_F(QuickTest, Subscribe)
{
}


void __stdcall OnRtnDepthMarketData(wdTick *pDepthMarketData)
{
	std::vector<wdTick> vecLastTicks;
	GetLastTick("IF1411", 20, vecLastTicks);
	cout << "有" << vecLastTicks.size() << "个数据\n";
	for (auto it = vecLastTicks.begin(); it != vecLastTicks.end();++it){
		cout<< it->InstrumentID<< " Tick数据\t"
		<< it->ExchangeTime<< "\t"
		<< it->LocalTime<< "\t"
		<< it->LastPrice<< " "
		<< it->BidPrice1<< "\t"
		<< it->BidVolume1<< "\t"
		<< it->AskPrice1<< "\t"
		<< it->AskVolume1<< "\t"
		<< it->Volume<< "\t"
		<< it->Turnover<<"\t"
		<< it->OpenInterest<< "\n\n\n";
		}
}

void __stdcall OnRtnDepthMarketData_KLine(wdKLine *pKLine)
{
	cout << pKLine->InstrumentID << " K线\t"
		<<pKLine->Period<<"\t"
		<<pKLine->ExchangeTime<< "\t" 		
		<< pKLine->Volume << "\t"
		<< pKLine->OpenInterest<< "\n\n";
}


void __stdcall OnRtnOrder(wdOrder *pOrder)
{
	//cout << "委托回报:" << pOrder->InsertTime << "\t" << pOrder->OrderSysID << "\t" << pOrder->OrderRef << "\t" << pOrder->OrderSubmitStatus << "\t" << pOrder->OrderStatus << "\t" << pOrder->StatusMsg << endl;
}

void __stdcall OnRtnTrade(wdTradeTicket *pTrade)
{
	//cout << "成交回报:" << pTrade->TradeTime << "\t" << pTrade->OrderSysID << "\t" << pTrade->OrderRef << endl;
}



void __stdcall OnRspQryInvestorPosition(wdPosition *)
{
	/*cout << "OnRspQryInvestorPosition" << pInvestorPosition->InstrumentID << "\t" << pInvestorPosition->PosiDirection << "\t" << pInvestorPosition->PositionDate << "\t"
		<< pInvestorPosition->YdPosition << "\t" << pInvestorPosition->Position << "\t" <<  pInvestorPosition->OpenVolume << endl;*/
}

void __stdcall OnRspError(const char *errMsg)
{
	cout << errMsg << endl;
}


void main(int argc, char* argv[])
{
	CTP_RegOnConnect(OnConnect);
	CTP_RegOnRspError(OnRspError);

	CTP_RegOnRtnDepthMarketData_Tick(OnRtnDepthMarketData);
	CTP_RegOnRtnDepthMarketData_KLine(OnRtnDepthMarketData_KLine);
	CTP_RegOnHistory_Tick(OnRtnDepthMarketData);
	CTP_RegOnHistory_KLine(OnRtnDepthMarketData_KLine);


	//CTP_RegOnRspQryInstrument(OnRspQryInstrument);
	CTP_RegOnRspQryOrder(OnRtnOrder);
	CTP_RegOnRspQryTrade(OnRtnTrade);
	CTP_RegOnRspQryInvestorPosition(OnRspQryInvestorPosition);

	MD_Connect();
	TD_Connect();
	
	system("pause");
	//MD_Subscribe("IF1411", "tick");
	//MD_SubscribeHistory("20141010-14:59:00.000", "20141010-15:00:00.000", "IF1410", "tick");
	//system("pause");
	
	/*TD_SendLimitOrder("IF1412", 2437.2, 10, E_Buy, E_Open);

	TD_SendLimitOrder("IF1412", 2437.8, 5, E_Sell, E_Close);*/

	cout<<endl;
	system("pause");
	/*
#if 0
	if (!MatlabEngine::instance()->CallMATLAB("cd C:/Users/think/Downloads/CTP-master/CSharp-CTP/bin; BEGIN; Subscribe(instruments);")) {
		std::cerr << MatlabEngine::instance()->get_last_error() << std::endl;
		return -1;
	}
	system("pause");
	if (!MatlabEngine::instance()->CallMATLAB("Unsubscribe(instruments);")) {
		std::cerr << MatlabEngine::instance()->get_last_error() << std::endl;
		return -1;
	}
	return 0;
#endif
	*/
}

