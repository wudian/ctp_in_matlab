#ifndef _CPP_MYSQL_H_
#define _CPP_MYSQL_H_

#include <map>
#include <list>
#include <string>
#include "mysql.h"
#include "CTP/ThostFtdcTraderApi.h"

struct wdTick;
struct wdKLine;

class CppMysql
{
public:
	CppMysql(void);
	~CppMysql(void);

	bool Mysql_Init();
	void Mysql_Finalize();

	// MD部分 =======================================================================================
	void Mysql_MarketData_Insert(const wdTick &tick);
	void SubscribeHistory(const char *beginTime, const char *endTime, const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod);

	// TD部分========================================================================================
	bool Mysql_Insert_TradingAccount(const CThostFtdcTradingAccountField &pTradingAccount);
	bool Mysql_Insert_InvestorPosition(const CThostFtdcInvestorPositionField &pInvestorPosition);
	bool Mysql_Insert_Instrument(const CThostFtdcInstrumentField &pInstrument);
	bool Mysql_Insert_Order(const CThostFtdcOrderField &pOrder);
	bool Mysql_Insert_Trade(const CThostFtdcTradeField &pTrade);

	bool Mysql_Insert_AvailableOrder(const CThostFtdcOrderField &pAvailableOrder);
	bool Mysql_DeletE_AvailableOrdersOrder(const CThostFtdcOrderField &pAvailableOrder);
	bool Mysql_DeletE_AvailableOrdersOrder(const CThostFtdcTradeField &pTrade);
	bool CancelOrder(const char *Instrument = nullptr,  TThostFtdcDirectionType Direction = 0, const TThostFtdcCombOffsetFlagType CombOffsetFlag = nullptr);

private:
	void _Mysql_Tick_Insert(const wdTick &tick);
	void _Mysql_KLine_Insert(wdKLine &kline);
	bool _Mysql_Create_Tables();
	std::string _GetTableName(const std::string &period);

	enum SQL_TYPE {
		E_HISTORY_MD,
		E_CANCEL_ORDER,
		E_OTHER
	};
	bool _Mysql_EXEC(const char *sql, SQL_TYPE t = E_OTHER);
	bool _Mysql_HistoryMd_Handler(MYSQL_RES *result);
	bool _Mysql_CancelOrder_Handler(MYSQL_RES *result);

	MYSQL		*m_pSql;
};

#endif