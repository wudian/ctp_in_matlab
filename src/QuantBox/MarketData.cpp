
#include "MarketData.h"
#include <string.h>
#include "toolkit.h"
#include "defines.h"

wdTick::wdTick()
{
	strcpy_s(InstrumentID, "");
	strcpy_s(ExchangeTime, NORMAL_TIME);
	strcpy_s(LocalTime, NORMAL_TIME);
}

wdTick::wdTick(char InstrumentID[31], char ExchangeTime[25], char LocalTime[25], double LastPrice, double BidPrice1, int BidVolume1,
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

wdTick::wdTick(const CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	strncpy(this->InstrumentID, pDepthMarketData->InstrumentID, sizeof(this->InstrumentID));
	strncpy(this->ExchangeTime, GetTickExchangeTime(pDepthMarketData).c_str(), sizeof(this->ExchangeTime));
	strncpy(this->LocalTime, GetTickLocalTime().c_str(), sizeof(this->LocalTime));
	this->LastPrice = pDepthMarketData->LastPrice;
	this->BidPrice1 = pDepthMarketData->BidPrice1;
	this->BidVolume1 = pDepthMarketData->BidVolume1;
	this->AskPrice1 = pDepthMarketData->AskPrice1;
	this->AskVolume1 = pDepthMarketData->AskVolume1;
	this->Volume = pDepthMarketData->Volume;
	this->Turnover = pDepthMarketData->Turnover;
	this->OpenInterest = pDepthMarketData->OpenInterest;
	this->HighestPrice = pDepthMarketData->HighestPrice;
	this->LowestPrice = pDepthMarketData->LowestPrice;
}

wdKLine::wdKLine(void)
	: OpenPrice(0.)
	, HighestPrice(0.)
	, LowestPrice(0.)
	, ClosePrice(0.)
	, LastVolume(0)
	, Volume(0)
	, OpenInterest(0.)	
{
	strcpy_s(InstrumentID, "");
	strcpy_s(ExchangeTime, NORMAL_TIME);
}

wdKLine::wdKLine(const char *InstrumentID, const char *Period)
	: OpenPrice(0.)
	, HighestPrice(0.)
	, LowestPrice(0.)
	, ClosePrice(0.)
	, LastVolume(0)
	, Volume(0)
	, OpenInterest(0.)	
{
	strcpy_s(this->InstrumentID, InstrumentID);
	strcpy_s(this->ExchangeTime, NORMAL_TIME);
	strcpy_s(this->Period, Period);
}