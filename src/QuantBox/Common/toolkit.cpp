#include "toolkit.h"
#include <stdlib.h>
#include <direct.h>
#include <mutex>
#include <condition_variable>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "MarketData.h"

using namespace std;


void GetOnFrontDisconnectedMsg(CThostFtdcRspInfoField* pRspInfo)
{
	if(NULL == pRspInfo)
		return;

	switch(pRspInfo->ErrorID)
	{
	case 0x1001:
		strcpy(pRspInfo->ErrorMsg,"0x1001 网络读失败");
		break;
	case 0x1002:
		strcpy(pRspInfo->ErrorMsg,"0x1002 网络写失败");
		break;
	case 0x2001:
		strcpy(pRspInfo->ErrorMsg,"0x2001 接收心跳超时");
		break;
	case 0x2002:
		strcpy(pRspInfo->ErrorMsg,"0x2002 发送心跳失败");
		break;
	case 0x2003:
		strcpy(pRspInfo->ErrorMsg,"0x2003 收到错误报文");
		break;
	default:
		sprintf(pRspInfo->ErrorMsg,"%x 未知错误");
		break;
	}
}

bool isStrNULL(const char *str)
{
	if (str == nullptr)
		return true;
	return isStdStrNULL(str);
}

bool isStdStrNULL(const std::string &str)
{
	return boost::algorithm::trim_copy(str) == "";
}

// 是否可用报单
bool IsAvailableOrder(const CThostFtdcOrderField *pOrder)
{
	return ((pOrder->OrderStatus != THOST_FTDC_OST_PartTradedNotQueueing) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_Canceled) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_AllTraded));
}

// 是否属于所有报单
bool IsAllOrder(const CThostFtdcOrderField *pOrder)
{
	return ((pOrder->OrderStatus != THOST_FTDC_OST_Canceled) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_AllTraded));
}

string GetTickExchangeTime(const CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	char ret[25];
	sprintf_s(ret, "%8s-%8s.%03d", pDepthMarketData->TradingDay, pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec);
	return ret;
}

string GetTickLocalTime()
{
	/*char ret[25];
	SYSTEMTIME stime;
	GetLocalTime( &stime );
	sprintf_s(ret, "%04d%02d%02d-%02d:%02d:%02d.%03d", stime.wYear, stime.wMonth, stime.wDay,stime.wHour,stime.wMinute,stime.wSecond,stime.wMilliseconds);*/
	string res = boost::posix_time::to_iso_string(boost::posix_time::microsec_clock::local_time());
	res.replace(8, 1, "-");
	res.insert(11, ":");
	res.insert(14, ":");
	res.erase(21);
	return res;
}

std::string GetLocalTime()
{
	string res = boost::posix_time::to_iso_string(boost::posix_time::microsec_clock::local_time());
	res = res.substr(9, 6);
	res.insert(2, ":");
	res.insert(5, ":");
	return res;
}

int GetSeconds(string period)
{
	int i = string::npos;
	if ((i = period.find('s')) != string::npos)
		return atoi(period.erase(i,1).c_str());
	else if ((i = period.find('m')) != string::npos)
		return 60 * atoi(period.erase(i,1).c_str());
	else if ((i = period.find('h')) != string::npos)
		return 3600 * atoi(period.erase(i,1).c_str());
	else
		return 0;
}

int GetTimeNum(const string &time) 
{
	if (isStdStrNULL(time))
		return 0;
	return 3600 * atoi( (time.substr(9, 2)).c_str() )
		+ 60 * atoi( (time.substr(12, 2)).c_str() )
		+ atoi( (time.substr(15, 2)).c_str() );
}

string GetKLineExchangeTime(const wdTick &tick, int period)
{
	int timeNum = GetTimeNum(tick.ExchangeTime);
	int n = timeNum % period;
	timeNum -= n;
	string ret = tick.ExchangeTime;
	int h = timeNum / 3600;
	int m = (timeNum % 3600) / 60;
	int s = timeNum % 60;
	char time[10] = {0};
	sprintf_s(time, "%02d:%02d:%02d", h, m, s);
	ret.replace(9, 8, time);
	return ret;
}

bool IsInTradeTime_Check_KLine(const std::string &Instrument_ID, const std::string &KLine_Time)
{
	// KLine_Time格式:	20140926-10:25:31.000
	// 中金所:			09:14:00~11:31:00 13:00:00~15:16:00
	// 大连郑州上海:		08:59:00~10:16:00 10:30:00~11:31:00 13:30:00~15:01:00
	int index_value = GetTimeNum(KLine_Time);
	bool Is_FFEX = Instrument_ID.substr(0, 2) == "IF";

	if( Is_FFEX )
	{
		return (index_value > GetTimeNum("00000000-09:14:00.000") && index_value < GetTimeNum("00000000-11:31:00.000")) ||
			(index_value > GetTimeNum("00000000-13:00:00.000") && index_value < GetTimeNum("00000000-15:16:00.000"));
	}
	else
	{
		return (index_value > GetTimeNum("00000000-08:59:00.000") && index_value < GetTimeNum("00000000-10:16:00.000")) ||
			(index_value > GetTimeNum("00000000-10:30:00.000") && index_value < GetTimeNum("00000000-11:31:00.000")) ||
			(index_value > GetTimeNum("00000000-13:30:00.000") && index_value < GetTimeNum("00000000-15:01:00.000"));
	}
}
