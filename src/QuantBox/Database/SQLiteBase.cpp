
#include "SQLiteBase.h"
#include <stdlib.h>
#include <stdio.h>
#include <io.h> 
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <windows.h>
#include "toolkit.h"
#include "SQLite3/sqlite3.h"
#include "CTPCommonApi.h"
#include "defines.h"
using namespace std;


SQLiteBase::SQLiteBase(void) : m_sqlite3(nullptr)
{
}


SQLiteBase::~SQLiteBase(void)
{
	if (m_sqlite3)
		sqlite3_close(m_sqlite3);
}

bool SQLiteBase::SQLite_Init(void)
{
	return true;
}

bool SQLiteBase::SQLite_EXEC(const char *SQL, fnOnQuerySQLite cb, void *p)
{
	int res = 0;
	char *errMsg = nullptr;
	if (m_sqlite3)
	{
		while( 1 )
		{
			res = sqlite3_exec(m_sqlite3, SQL, cb, p, &errMsg);
			if( SQLITE_OK !=  res)
			{
				if( strstr(errMsg, "database is locked") )
				{
					Sleep(1);
					continue;
				}
				else
				{
					SQLite_Error_Log(res, SQL, errMsg);
					sqlite3_free(errMsg);
					return false;
				}
				break;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		SQLite_Error_Log(res, SQL, "SQLite is closed");
		return false;
	}
	
	
	sqlite3_free(errMsg);
	return true;
}

bool SQLiteBase::SQLite_Item_Exist(const char *SQL)
{
	bool ret = false;
	char **pazResult = nullptr;
	int pnRow, pnColumn;
	char *pzErrmsg = nullptr;

	int res = sqlite3_get_table(m_sqlite3, SQL, &pazResult, &pnRow, &pnColumn, &pzErrmsg);
	if (SQLITE_OK != res) {
		sqlite3_free_table(pazResult);
		SQLite_Error_Log(res, SQL, pzErrmsg);
		sqlite3_free(pzErrmsg);
		return false;
	}
	for (int i=0;i<pnColumn;++i){
		printf("%s\t",pazResult[i]);
	}
	if (nullptr != pazResult)
		ret = true;
	sqlite3_free_table(pazResult);	
	sqlite3_free(pzErrmsg);
	return ret;
}

void SQLiteBase::SQLite_Error_Log(int res, const char *SQL, const char *errMsg)
{
	LOG_ERROR << "err_id(" << res << ") SQL(" << SQL << ") errMsg(" << errMsg << ")";
}




/*************** 时间处理相关函数 **************************************************************************/

// 本地时间与交易所时间同步
void SQLiteBase::Time_sync(CThostFtdcRspUserLoginField *pRspUserLogin)
{
	// 时间同步 
	SYSTEMTIME stime; 			
	GetLocalTime( &stime );
	int iYear = 0, iMonth = 0, iDay = 0, iHour = 0, iMinute = 0, iSecond = 0;
	string day_time(pRspUserLogin->FFEXTime);	// 与中金所时间同步

	iHour	= atoi( (day_time.substr(0, 2)).c_str() );
	iMinute	= atoi( (day_time.substr(3, 2)).c_str() );
	iSecond	= atoi( (day_time.substr(6, 2)).c_str() );

	stime.wHour = iHour;
	stime.wMinute = iMinute;
	stime.wSecond = iSecond;
	stime.wMilliseconds = 0;
	SetLocalTime(&stime);

}

// 获取交易当前交易日期
char* SQLiteBase::Get_TradingDay()
{
	time_t now;
	time( &now );
	strftime(tradeDay, sizeof(tradeDay)+1, "%Y-%_-%d", localtime(&now));
	return tradeDay;
}

// 获取交易当前交易时间 如 09:55:34
char* SQLiteBase::Get_localTime_Sec()
{
	time_t now;
	time( &now );
	strftime(localTime_Mil, sizeof(localTime_Mil)+1, "%H:%M:%S", localtime(&now));
	return localTime_Mil;
}

// 获取本地时间的秒数
int SQLiteBase::Get_LocalTime_Second()
{
	SYSTEMTIME stime;
	GetLocalTime( &stime );
	return stime.wSecond;  // 返回当前秒数
}

// 获取本地毫秒级时间 如返回123 表示当前为毫秒的123
int SQLiteBase::Get_LocalTime_Millisec()
{
	SYSTEMTIME stime;
	GetLocalTime( &stime );
	return stime.wMilliseconds;  // 返回当前毫秒
	//printf("现在的时间是：%d点%d分%d秒%d毫秒\n",stime.wHour,stime.wMinute,stime.wSecond,stime.wMilliseconds);
	//return (double)stime.wSecond + (double)stime.wMilliseconds/1000
}

// 微妙级延时 num表示微妙
void SQLiteBase::Delay(int num)
{
	LARGE_INTEGER litmp;
	LONGLONG QPart1,QPart2;
	double dfMinus, dfFreq, dfTim;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;		// 获得计数器的时钟频率
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;				// 获得初始值
	do
	{
		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;			// 获得中止值
		dfMinus = (double)(QPart2-QPart1);
		dfTim = dfMinus / dfFreq;			// 获得对应的时间值，单位为秒
	}while(dfTim < (double)num/1000000 );
}