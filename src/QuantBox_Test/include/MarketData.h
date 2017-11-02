#ifndef _MARKET_DATA_H_
#define _MARKET_DATA_H_

#include "Types.h"

struct CThostFtdcDepthMarketDataField;

//! tick数据
struct QUANTBOX_API wdTick
{
	///合约代码
	char	InstrumentID[31];
	///交易所时间戳
	char	ExchangeTime[25];	
	///本地时间
	char	LocalTime[25];
	///最新价
	double	LastPrice;
	///申买价一
	double	BidPrice1;
	///申买量一
	int		BidVolume1;
	///申卖价一
	double	AskPrice1;
	///申卖量一
	int		AskVolume1;
	///数量
	int		Volume;
	///成交金额
	double	Turnover;
	///持仓量
	double	OpenInterest;
	///最高价
	double	HighestPrice;
	///最低价
	double	LowestPrice;

	wdTick();

	wdTick(char InstrumentID[31], char ExchangeTime[25], char LocalTime[25], double LastPrice, double BidPrice1, int BidVolume1,
		double AskPrice1, int AskVolume1, int Volume, double Turnover, double OpenInterest, double HighestPrice, double LowestPrice);

	wdTick(const CThostFtdcDepthMarketDataField *pDepthMarketData);
};

//! K线数据
struct QUANTBOX_API wdKLine
{
	///合约代码
	char	InstrumentID[31];
	///交易所时间
	char	ExchangeTime[25];	
	///开
	double	OpenPrice;
	///高
	double	HighestPrice;
	///低
	double	LowestPrice;
	///收
	double	ClosePrice;	
	///最后一个tick的累计成交量； Volume - LastVolume 得到本根K线的成交量
	int		Volume;
	///持仓量
	double	OpenInterest;	
	///周期
	char	Period[5];
	///上一根k线最后一个tick的累计成交量
	int		LastVolume;
	///上一个持仓量
	double	LastOpenInterest;

	wdKLine(void);

	wdKLine(const char *InstrumentID, const char *Period);
};

#endif