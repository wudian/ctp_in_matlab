#ifndef _SQLITE_BASE_H_
#define _SQLITE_BASE_H_


#include <list>
#include <string>
#include "Types.h"
struct sqlite3;

class SQLiteBase
{
public:
	SQLiteBase(void);
	virtual ~SQLiteBase(void);

	// SQLite数据库初始化
	virtual bool SQLite_Init(void);

	// SQLite数据库 关闭
	virtual void SQLite_Finalize() {};

	// MD部分 =======================================================================================
	virtual void SQLite_MarketData_Insert(const wdTick &tick) {}
	virtual void SubscribeHistory(const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod, const char *beginTime, const char *endTime) {}

	// TD部分 =======================================================================================
	virtual bool SQLite_Insert_TradingAccount(const CThostFtdcTradingAccountField &pTradingAccount) {return true;}
	virtual bool SQLite_Insert_InvestorPosition(const CThostFtdcInvestorPositionField &pInvestorPosition) {return true;}
	virtual bool SQLite_Insert_Order(const CThostFtdcOrderField &pOrder){return true;}
	virtual bool SQLite_Insert_Trade(const CThostFtdcTradeField &pTrade){return true;}
	

	virtual bool SQLite_Insert_AvailableOrder(const CThostFtdcOrderField &pAvailableOrder){return true;}
	virtual bool SQLite_DeletE_AvailableOrdersOrder(const CThostFtdcOrderField &pAvailableOrder){return true;}
	virtual bool SQLite_DeletE_AvailableOrdersOrder(const CThostFtdcTradeField &pTrade){return true;}
	virtual bool CancelOrder(void *pTd, const char *Instrument = nullptr,  char Direction = 0, const char *wdConnectionStatus = nullptr) {return true;}
protected:
	bool SQLite_EXEC(const char *SQL, fnOnQuerySQLite cb = nullptr, void *p = nullptr);
	// 判断某条记录是否存在
	bool SQLite_Item_Exist(const char *SQL);
	// 记录插入SQLite时的错误代码
	void SQLite_Error_Log(int res, const char *SQL, const char *errMsg);

protected:
	sqlite3						*m_sqlite3;


	char localTime_Mil[20];							// 当前时间 毫秒级 如 09:46:55.123 
	char tradeDay[10];								// 当前交易日期 如2014-01-14
	/*************** 时间处理相关函数 **************************************************************************/

	// 本地时间与交易所时间同步
	void Time_sync(CThostFtdcRspUserLoginField *pRspUserLogin);

	// 获取交易当前交易日期
	char* Get_TradingDay();

	// 获取交易当前交易时间 如 09:55:34
	char* Get_localTime_Sec();

	// 获取本地毫秒级时间 如返回123 表示当前为毫秒的123
	int Get_LocalTime_Millisec();

	// 获取本地时间的秒数
	int Get_LocalTime_Second();

	// 微妙级延时 num表示微妙
	void Delay(int num);
};

#endif