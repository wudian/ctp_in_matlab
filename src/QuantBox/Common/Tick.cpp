#include "Tick.h"
#include "CTP\ThostFtdcUserApiStruct.h"
#include "toolkit.h"

CTick::CTick()
	: LastPrice(0.)
	, BidPrice1(0.)
	, BidVolume1(0)
	, AskPrice1(0.)
	, AskVolume1(0)
	, Volume(0)
	, Turnover(0.)
	, OpenInterest(0.)
	, HighestPrice(0.)
	, LowestPrice(0.)
{
	strcpy_s(InstrumentID, "");
	strcpy_s(ExchangeTime, "");
	strcpy_s(LocalTime, "");
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



CTick::~CTick(void)
{
}

CTick &CTick::operator=(const CTick &tick)
{
	strncpy(this->InstrumentID, tick.InstrumentID, sizeof(this->InstrumentID));
	strncpy(this->ExchangeTime, tick.ExchangeTime, sizeof(this->ExchangeTime));
	strncpy(this->LocalTime, tick.LocalTime, sizeof(this->LocalTime));
	this->LastPrice = tick.LastPrice;
	this->BidPrice1 = tick.BidPrice1;
	this->BidVolume1 = tick.BidVolume1;
	this->AskPrice1 = tick.AskPrice1;
	this->AskVolume1 = tick.AskVolume1;
	this->Volume = tick.Volume;
	this->Turnover = tick.Turnover;
	this->OpenInterest = tick.OpenInterest;
	this->HighestPrice = tick.HighestPrice;
	this->LowestPrice = tick.LowestPrice;
	return *this;
}