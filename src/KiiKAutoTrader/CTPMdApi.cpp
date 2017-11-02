#include "GVAR.h"
#include "CTPMdApi.h"
#include <qdebug.h>
#include <string>
using std::string;
using std::shared_ptr;
using std::vector;



CTPMdApi::CTPMdApi(){
	m_pApi = CThostFtdcMdApi::CreateFtdcMdApi("./ctp_temp_file/");
	connectFlag = false;
}

CTPMdApi::~CTPMdApi(){
	qDebug() << "m_pApi->Release()";
	if (m_pApi != nullptr){
		m_pApi->RegisterSpi(NULL);
		m_pApi->Release();
		m_pApi = NULL;
		instruSet.clear();	//情况已订阅的列表
	}
}

/************************************public函数**************************************************************/

void CTPMdApi::registerSpi(shared_ptr<CThostFtdcMdSpi> spi){
	ctpMdSpi = spi;
	m_pApi->RegisterSpi(ctpMdSpi.get());
}

void CTPMdApi::login(){
	if (NULL == m_pApi)
		return;
	CThostFtdcReqUserLoginField loginField = {0};
	strncpy(loginField.BrokerID, "666666", sizeof(TThostFtdcBrokerIDType));
	int res = m_pApi->ReqUserLogin(&loginField, 1);
}

void CTPMdApi::release(){
	m_pApi->Release();
	m_pApi = nullptr;
}

int CTPMdApi::subscribeData(char *ppwdTickID[], int nCount){
	return m_pApi->SubscribeMarketData(ppwdTickID, nCount);
}

int CTPMdApi::unsubscribeData(char *ppwdTickID[], int nCount){
	return m_pApi->UnSubscribeMarketData(ppwdTickID, nCount);
}

bool CTPMdApi::isConnect(){
	return connectFlag;
}

void CTPMdApi::setConnect(){
	connectFlag = true;
}

//注册前置机并初始化Api
void CTPMdApi::connectServer(){
	//注册前置机
	char address[100];
	strcpy(address, FRONT_ADDRESS.toStdString().c_str());
	m_pApi->RegisterFront(address);
	//初始化Api
	m_pApi->Init();
}

