#ifndef _DEFINE_H_
#define _DEFINE_H_

#define		QUANTBOX_SEPS			",;"
#define		UNIQUE_REQUEST_ID		-1
#define		NORMAL_TIME				"00000000-00:00:00.000"		
#define		MYSQL_DB_NAME			"ctp"

#define		LOG_NORMAL				BOOST_LOG_SEV(my_logger::get(), normal)
#define		LOG_WARNING				BOOST_LOG_SEV(my_logger::get(), warning)
#define		LOG_ERROR				BOOST_LOG_SEV(my_logger::get(), error)

/*
struct wdLimitPrice : public wdLimitPrice
{
	wdLimitPrice(double UpperLimitPrice, double LowerLimitPrice);
};

struct wdTick : public wdTick
{
	wdTick();

	wdTick(char InstrumentID[31], char ExchangeTime[25], char LocalTime[25], double LastPrice, double BidPrice1, int BidVolume1,
		double AskPrice1, int AskVolume1, int Volume, double Turnover, double OpenInterest, double HighestPrice, double LowestPrice);

	wdTick(const CThostFtdcDepthMarketDataField *pDepthMarketData);
};

struct wdKLine : public wdKLine
{
	wdKLine(void);

	wdKLine(const char *InstrumentID, const char *Period);
};
*/
#endif