#include "defines.h"

#include <string.h>
#include "toolkit.h"
#include "TradeData.h"
#include "CTPLastInfos.h"

CLimitPrice::CLimitPrice(double UpperLimitPrice, double LowerLimitPrice)
{
	this->UpperLimitPrice = UpperLimitPrice;
	this->LowerLimitPrice = LowerLimitPrice;
}

CTick::CTick()
{
	strcpy_s(InstrumentID, "");
	strcpy_s(ExchangeTime, NORMAL_TIME);
	strcpy_s(LocalTime, NORMAL_TIME);
}

CTick::CTick(char InstrumentID[31], char ExchangeTime[25], char LocalTime[25], double LastPrice, double BidPrice1, int BidVolume1,
	  double AskPrice1, int AskVolume1, int Volume, double Turnover, double OpenInterest, double HighestPrice, double LowestPrice)
{
	strncpy(this->InstrumentID, InstrumentID, sizeof(this->InstrumentID));
	strncpy(this->ExchangeTime, ExchangeTime, sizeof(this->ExchangeTime));
	strncpy(this->LocalTime, LocalTime, sizeof(this->LocalTime));
	this->LastPrice = LastPrice;
	this->BidPrice1 = BidPrice1;
	this->BidVolume1 = BidVolume1;
	this->AskPrice1 = AskPrice1;
	this->AskVolume1 = AskVolume1;
	this->Volume = Volume;
	this->Turnover = Turnover;
	this->OpenInterest = OpenInterest;
	this->HighestPrice = HighestPrice;
	this->LowestPrice = LowestPrice;
}

CTick::CTick(const CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	strncpy(this->InstrumentID, pDepthMarketData->InstrumentID, sizeof(this->InstrumentID));
	strncpy(this->ExchangeTime, GetTickExchangeTime(pDepthMarketData).c_str(), sizeof(this->ExchangeTime));
	strncpy(this->LocalTime, GetTickLocalTime().c_str(), sizeof(this->LocalTime));
	this->LastPrice = pDepthMarketData->LastPrice;
	if (pDepthMarketData->BidPrice1 > pDepthMarketData->UpperLimitPrice)
		this->BidPrice1 = pDepthMarketData->LastPrice;
	else
		this->BidPrice1 = pDepthMarketData->BidPrice1;
	this->BidVolume1 = pDepthMarketData->BidVolume1;
	if (pDepthMarketData->AskPrice1 > pDepthMarketData->UpperLimitPrice)
		this->AskPrice1 = pDepthMarketData->LastPrice;
	else
		this->AskPrice1 = pDepthMarketData->AskPrice1;
	this->AskVolume1 = pDepthMarketData->AskVolume1;
	this->Volume = pDepthMarketData->Volume;
	if (wdCTPLastInfos::instance()->isCZCE(pDepthMarketData->InstrumentID))
		this->Turnover = pDepthMarketData->Turnover * wdCTPLastInfos::instance()->GetInstrument(pDepthMarketData->InstrumentID).VolumeMultiple;
	else
		this->Turnover = pDepthMarketData->Turnover;
	this->OpenInterest = pDepthMarketData->OpenInterest;
	this->HighestPrice = pDepthMarketData->HighestPrice;
	this->LowestPrice = pDepthMarketData->LowestPrice;
}

CKLine::CKLine(void)
{
	this->OpenPrice = 0.;
	this->HighestPrice = 0.;
	this->LowestPrice = 0.;
	this->ClosePrice = 0.;
	this->Volume = 0;
	this->OpenInterest = 0.;
	this->LastVolume = 0;
	this->LastOpenInterest = 0.;
	strcpy_s(InstrumentID, "");
	strcpy_s(ExchangeTime, NORMAL_TIME);
}

CKLine::CKLine(const char *InstrumentID, const char *Period)
{
	this->OpenPrice = 0.;
	this->HighestPrice = 0.;
	this->LowestPrice = 0.;
	this->ClosePrice = 0.;
	this->Volume = 0;
	this->OpenInterest = 0.;
	this->LastVolume = 0;
	this->LastOpenInterest = 0.;
	strcpy_s(this->InstrumentID, InstrumentID);
	strcpy_s(this->ExchangeTime, NORMAL_TIME);
	strcpy_s(this->Period, Period);
}