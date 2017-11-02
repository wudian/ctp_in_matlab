#ifndef _TOOLKIT_H_
#define _TOOLKIT_H_

#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include "logger.h"
#include "Types.h"
#include "CTP\ThostFtdcUserApiStruct.h"



//根据OnFrontDisconnected(int nReason)的值填上错误消息
void GetOnFrontDisconnectedMsg(CThostFtdcRspInfoField* pRspInfo);


bool isStrNULL(const char *str);
bool isStdStrNULL(const std::string &str);


// 是否可用报单
bool IsAvailableOrder(const CThostFtdcOrderField *pOrder);
// 是否属于所有报单
bool IsAllOrder(const CThostFtdcOrderField *pOrder);


std::string GetTickExchangeTime(const CThostFtdcDepthMarketDataField *pDepthMarketData);

std::string GetTickLocalTime();

// 获取当前的 时:分:秒
std::string GetLocalTime();

int GetSeconds(std::string period);

int GetTimeNum(const std::string &time);

std::string GetKLineExchangeTime(const wdTick &tick, int period);

// 判断K线时间是否在交易时间内 
// 中金所:		09:14:00~11:31:00 13:00:00~15:16:00
// 大连郑州上海:	08:59:00~10:16:00 10:30:00~11:31:00 13:30:00~15:01:00
bool IsInTradeTime_Check_KLine(const std::string &Instrument_ID, const std::string &KLine_Time);

#endif