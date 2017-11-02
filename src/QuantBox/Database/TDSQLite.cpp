
#include "TDSQLite.h"
#include <sstream>
#include <xutility>
#include <chrono>
#include <boost/algorithm/string.hpp>
#include <SQLite3/sqlite3.h>
#include "toolkit.h"
#include "CTPTdApi.h"
#include "CTPReqMsg.h"
enum wdTradeType;
#include "GlobalVars.h"

using namespace std;

TDSQLite::TDSQLite(void) : m_sqlite3(nullptr)
{
}


TDSQLite::~TDSQLite(void)
{
	if (m_sqlite3)
		sqlite3_close(m_sqlite3);
}

bool TDSQLite::SQLite_Init(void)
{
	// 创建内存数据库
	extern string g_tdDBPath;
	int res = sqlite3_open(g_tdDBPath.c_str(), &m_sqlite3); // :memory:
	if (res)
	{
		_SQLite_Error_Log(res, "", sqlite3_errmsg(m_sqlite3));
		sqlite3_close(m_sqlite3);
		m_sqlite3 = nullptr;
		return false;
	}

	if (!_SQLite_Create_Tables())
		return false;

	return true;
}

bool TDSQLite::_SQLite_Create_Tables()
{
	const char *SQL_InvestorPosition = // 持仓
		"create table if not exists T_Position("
		"InstrumentID varchar(31),	Dir int,					TPos int,					APos int,					PosAvgPrice double,"
		"primary key(InstrumentID, Dir)); delete from T_Position;";

	const char *SQL_Order =	// 报单
		"create table if not exists T_Order("
		"FrontID int,				SessionID int,				OrderRef varchar(13),		OrderSysID varchar(21),		Type int,"
		"InstrumentID varchar(31),	Dir int,					Offset int,					Status int,					Price double,"
		"Hands int,					AvaHands int,				TradedHands int,			InsertTime varchar(9),		StatusMsg varchar(81),"
		"ExchangeID varchar(9),		primary key(FrontID, SessionID,OrderRef )); delete from T_Order;";

	const char *SQL_Trade = // 成交
		"create table if not exists T_Trade("
		"TradeID varchar(21),		OrderSysID varchar(21),		InstrumentID varchar(31),	Dir int,					Offset int,"
		"Price double,				Hands int,					TradeType char(1),			TradeTime varchar(9),		ExchangeID varchar(9),"
		"HedgeFlag char(1),			primary key(TradeID)); delete from T_Trade;";
								
	if (!_SQLite_EXEC(SQL_InvestorPosition) || !_SQLite_EXEC(SQL_Order) || !_SQLite_EXEC(SQL_Trade))
		return false;
	return true;
}

void TDSQLite::SQLite_Finalize()
{
	if (!m_sqlite3)
		sqlite3_close(m_sqlite3);
}

bool TDSQLite::SQLite_Insert_Position(const wdPosition &poi)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into %s values("
		"'%s',%d,%d,%d,%g);",
		g_Table_Position,
		poi.InstrumentID, poi.Dir, poi.TPos, poi.APos, poi.PosAvgPrice);

	if (!_SQLite_EXEC(sql))
		return false;
	return true;
}

bool TDSQLite::SQLite_Insert_Order(const wdOrder &pOrder)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into %s values("
		"%d,%d,'%s','%s',%d,"
		"'%s',%d,%d,%d,%g,"
		"%d,%d,%d,'%s','%s',"
		"'%s');",
		g_Table_Order,
		pOrder.FrontID, pOrder.SessionID, pOrder.OrderRef, pOrder.OrderSysID, pOrder.Type,
		pOrder.InstrumentID, pOrder.Dir, pOrder.Offset, pOrder.Status, pOrder.Price, 
		pOrder.Hands, pOrder.AvaHands, pOrder.TradedHands, pOrder.InsertTime, pOrder.StatusMsg, 
		pOrder.ExchangeID);
	/*switch (pOrder.Status)
	{
	case E_InsertSubmitted:
	sprintf_s(sql, "replace into %s values("
	"%d,%d,'%s','%s',%d,"
	"'%s',%d,%d,%d,%g,"
	"%d,%d,%d,'%s','%s',"
	"'%s');",
	g_Table_Order,
	pOrder.FrontID, pOrder.SessionID, pOrder.OrderRef, pOrder.OrderSysID, pOrder.Type,
	pOrder.InstrumentID, pOrder.Dir, pOrder.Offset, pOrder.Status, pOrder.Price, 
	pOrder.Hands, pOrder.AvaHands, pOrder.TradedHands, pOrder.InsertTime, pOrder.StatusMsg, 
	pOrder.ExchangeID);
	break;
	case E_InsertTrash:
	case E_CancelSubmitted:
	case E_CancelTrash:
	sprintf_s(sql, "replace into %s(FrontID, SessionID, OrderRef, InsertTime, StatusMsg) values("
	"%d,%d,'%s','%s','%s');",
	g_Table_Order,
	pOrder.FrontID, pOrder.SessionID, pOrder.OrderRef, pOrder.InsertTime, pOrder.StatusMsg);
	break;
	case E_PartTradedQueueing:
	case E_PartTradedNotQueueing:
	case E_AllTraded:
	case E_Canceled:
	sprintf_s(sql, "replace into %s(FrontID, SessionID, OrderRef, OrderSysID, AvaHands, TradedHands, InsertTime, StatusMsg, ExchangeID) values("
	"%d,%d,'%s','%s',%d,"
	"%d,'%s','%s','%s');",
	g_Table_Order,
	pOrder.FrontID, pOrder.SessionID, pOrder.OrderRef, pOrder.OrderSysID, pOrder.AvaHands, 
	pOrder.TradedHands, pOrder.InsertTime, pOrder.StatusMsg, pOrder.ExchangeID);
	break;
	default:
	return true;
	}*/
	
	if (!_SQLite_EXEC(sql))
		return false;
	return true;
}

bool TDSQLite::SQLite_Insert_Trade(const wdTradeTicket &pTrade)
{
	char sql[1024] = {0};
	sprintf_s(sql, "replace into %s values("
		"'%s','%s','%s',%d,%d,"
		"%g,%d,'%c','%s','%s',"
		"'%c');",
		g_Table_Trade,
		pTrade.TradeID, pTrade.OrderSysID,pTrade.InstrumentID,pTrade.Dir,pTrade.Offset,
		pTrade.Price,pTrade.Hands,pTrade.TradeType,pTrade.TradeTime,pTrade.ExchangeID,
		pTrade.HedgeFlag);
	
	if (!_SQLite_EXEC(sql))
		return false;
	return true;
}

static int SQLite_ReqOrderAction_Callback(void *param, int num, char **values, char **colName)
{
	CCTPTdApi::instance()->CancelOrder(wdOrder(values));
	return 0;
}

bool TDSQLite::CancelOrder(const char *Instrument, wdDirectionType Direction, wdOffsetFlagType OffsetFlag)
{
	char sql[1024] = {0};
	char inst[64] = {0}; 
	char direct[64] = {0};
	char offset[64] = {0};
	if (!isStrNULL(Instrument))
		sprintf_s(inst, "t.InstrumentID = '%s' and", Instrument);
	if (Direction != E_Direction_Default)
		sprintf_s(direct, "t.Dir = %d and", Direction);
	if (OffsetFlag != E_OffsetFlag_Default)
		sprintf_s(offset, "t.Offset = %d and", OffsetFlag);

	sprintf_s(sql, "select * from %s t where t.Status not in (3,4,5) and %s %s %s;", 
		g_Table_Order, inst, direct, offset);

	std::string temp = sql;
	boost::algorithm::erase_last(temp, "and");

	if (!_SQLite_EXEC(temp.c_str(), SQLite_ReqOrderAction_Callback))
		return false;

	return true;
}


bool TDSQLite::_SQLite_EXEC(const char *SQL, fnOnQuerySQLite cb, void *p)
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
					std::this_thread::sleep_for(std::chrono::seconds(1));
					continue;
				}
				else
				{
					_SQLite_Error_Log(res, SQL, errMsg);
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
		_SQLite_Error_Log(res, SQL, "SQLite is closed");
		return false;
	}


	sqlite3_free(errMsg);
	return true;
}

void TDSQLite::_SQLite_Error_Log(int res, const char *SQL, const char *errMsg)
{
	LOG_ERROR << "err_id(" << res << ") SQL(" << SQL << ") errMsg(" << errMsg << ")";
}
