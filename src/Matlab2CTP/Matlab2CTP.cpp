#include "mex.h"
#include <iostream>
#include "CTPMsgQueue.h"
#include "MdUserApi.h"
#include "TraderApi.h"
#include <thread>

using namespace std;



void __stdcall OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << pRspInfo->ErrorMsg << endl;
}

void  __stdcall OnConnect(CThostFtdcRspUserLoginField *pRspUserLogin,ConnectionStatus step)
{
	cout<< "nReason  "<< step<< endl;
}
//
void __stdcall OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	mxArray *x = mxCreateString("wudianwudian");
	mexCallMATLAB(0,NULL,1,&x,"disp");
}

void __stdcall OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << pTradingAccount->BrokerID << "\t" << pTradingAccount->PreCredit << endl;
}

void __stdcall OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << pInvestorPosition->InstrumentID << "\t" << pInvestorPosition->PosiDirection << endl;
}

void __stdcall OnRspQryInstrument(void* pTraderApi, CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cout << pInstrument->InstrumentName << "\t" << pInstrument->ProductID << "\t" << pInstrument->OpenDate << endl;
}

//void __stdcall OnRspQryDepthMarketData(void* pTraderApi, CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cout<< pDepthMarketData->InstrumentID<< "\t" << pDepthMarketData->UpdateTime<< endl;
//}

void my_thread()
{
	mxArray *x = mxCreateDoubleScalar(5.);
	mexCallMATLAB(0,NULL,1,&x,"disp");  
	mxDestroyArray(x);
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	thread t(my_thread);
	t.join();
	//system("pause");
	return;

	/*
	CCTPMsgQueue *pMDMsgQueue = new CCTPMsgQueue();
	pMDMsgQueue->RegisterCallback(OnConnect);
	pMDMsgQueue->RegisterCallback(OnRtnDepthMarketData);
	pMDMsgQueue->StartThread();
	CMdUserApi *pMd = new CMdUserApi();
	pMd->RegisterMsgQueue(pMDMsgQueue);
	pMd->Connect("d:\\","tcp://asp-sim2-md1.financial-trading-platform.com:26213","2030","123456","888888");
	pMd->Subscribe("IF1406,IF1407,IF1412,IF1409");
	*/
}



/*
int _tmain(int argc, _TCHAR* argv[])
{
	

	CCTPMsgQueue *pTDMsgQueue = new CCTPMsgQueue();
	pTDMsgQueue->RegisterCallback(OnConnect);
	pTDMsgQueue->RegisterCallback(OnRspError);
	pTDMsgQueue->RegisterCallback(OnRspQryTradingAccount);
	pTDMsgQueue->RegisterCallback(OnRspQryInvestorPosition);
	pTDMsgQueue->RegisterCallback(OnRspQryInstrument);
	pTDMsgQueue->RegisterCallback(OnRtnDepthMarketData);
	pTDMsgQueue->StartThread();
	CTraderApi *pTd = new CTraderApi();
	pTd->RegisterMsgQueue(pTDMsgQueue);
	//pTd->Connect("d:\\","tcp://asp-sim2-front1.financial-trading-platform.com:26205","2030","123456","888888",THOST_TERT_RESTART,"","");
	pTd->Connect("d:\\","tcp://ctpmn1-front1.citicsf.com:51205","1017","00000015","123456",THOST_TERT_RESTART,"","");
	int i = 0;
	while (cin >> i)
	{
		switch (i)
		{
		case 1:
			pTd->ReqQryDepthMarketData("IF1406,IF1409");
			break;
		case 2:
			pTd->ReqQryInstrument("");
			break;
		case 3:
			pTd->ReqQryInstrument("");
			break;
		default:
			return 0;
		}
	}
	
	
	
	//system("pause");
	return 0;
}
*/
