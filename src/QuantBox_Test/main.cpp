
#include <iostream>
#include "QuantBoxApi.h"
#include "MarketData.h"

using namespace std;

void __stdcall OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << (pRspInfo != nullptr ? pRspInfo->ErrorMsg:"") << endl;
}

void __stdcall OnMdConnect(wdConnectionStatus step)
{
	if (step == E_logined)
		cout << "行情登陆成功\n";
}

void __stdcall OnTdConnect(wdConnectionStatus step)
{	
	if (step  == E_confirmed)
		cout << "交易登陆成功\n";
}

void __stdcall OnMdDisconnect(CThostFtdcRspInfoField *pRspInfo, wdConnectionStatus step)
{
	cout << "行情断开："<< (pRspInfo != nullptr ? pRspInfo->ErrorMsg:"") <<endl;
}

void __stdcall OnTdDisconnect(CThostFtdcRspInfoField *pRspInfo, wdConnectionStatus step)
{
	cout << "交易断开："<<(pRspInfo != nullptr ? pRspInfo->ErrorMsg:"")<<endl;
}

void __stdcall OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << pTradingAccount->BrokerID << "\t" << pTradingAccount->PreCredit << endl;
}

void __stdcall OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << pInvestorPosition->InstrumentID << "\t" << pInvestorPosition->PosiDirection << "\t" << pInvestorPosition->PositionDate << "\t"
		<< pInvestorPosition->YdPosition << "\t" << pInvestorPosition->Position << "\t" <<  pInvestorPosition->OpenVolume << endl;
}


void __stdcall OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << pInvestorPosition->InstrumentID << "\t" << pInvestorPosition->Volume << endl;
}


void __stdcall OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << pInstrument->InstrumentName << "\t" << pInstrument->ProductID << "\t" << pInstrument->OpenDate << endl;
}

void __stdcall OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cout << "OnRspQryOrder\t" << pOrder->NotifySequence << "\t" << pOrder->SequenceNo << "\t" << pOrder->RelativeOrderSysID<< endl;
}

void __stdcall OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	cout << "OnErrRtnOrderAction" << endl;
}

void __stdcall OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
	cout << "OnErrRtnOrderInsert" << (pRspInfo != nullptr ? pRspInfo->ErrorMsg:"") << "\t" <<pInputOrder->InstrumentID << "\t"<<pInputOrder->OrderRef <<endl;
}

void __stdcall OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspOrderAction" << endl;
}

void __stdcall OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspOrderInsert" << endl;
}

void __stdcall OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	cout << "OnRtnOrder\t" << pOrder->InstrumentID << "\t" << pOrder->OrderSubmitStatus << "\t" << pOrder->OrderStatus << "\t" << pOrder->StatusMsg << endl;
}

void __stdcall OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	cout << "OnRtnTrade\t" << pTrade->SequenceNo << "\t" << pTrade->TradeDate << pTrade->TradeTime << endl;
}

void __stdcall OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cout << "OnRspQryDepthMarketData" << pDepthMarketData->LastPrice << endl;
}

void __stdcall OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cout << "OnRspQryTrade\t" << pTrade->SequenceNo << "\t" << pTrade->TradeDate << pTrade->TradeTime << endl;
}

void __stdcall OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << "OnRspQrySettlementInfo" << pSettlementInfo->SettlementID << pSettlementInfo->TradingDay << endl;
}

#include "Recorder.h"

void __stdcall OnRtnDepthMarketData(wdTick *pDepthMarketData)
{

	Recorder.record(pDepthMarketData);


	std::vector<wdTick> vecLastTicks;
	GetLastTicks("IF1410", 20, vecLastTicks);
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
	
}

void main(int argc, char* argv[])
{
	CTP_RegMDOnConnect(OnMdConnect);
	CTP_RegMDOnDisconnect(OnMdDisconnect);
	CTP_RegMDOnRspError(OnRspError);

	CTP_RegOnRtnDepthMarketData_Tick(OnRtnDepthMarketData);
	CTP_RegOnRtnDepthMarketData_KLine(OnRtnDepthMarketData_KLine);
	CTP_RegOnHistory_Tick(OnRtnDepthMarketData);
	CTP_RegOnHistory_KLine(OnRtnDepthMarketData_KLine);
	
	CTP_RegTDOnConnect(OnTdConnect);
	CTP_RegTDOnDisconnect(OnTdDisconnect);
	CTP_RegTDOnRspError(OnRspError);

	MD_Connect();
	TD_Connect();

	MD_Subscribe("IF1410", "tick");
	


	system("pause");
	
}