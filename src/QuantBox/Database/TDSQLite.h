#ifndef _TD_SQLITE_H_
#define _TD_SQLITE_H_

#include "Types.h"
#include "TradeData.h"
struct sqlite3;

class TDSQLite
{
public:
	TDSQLite(void);
	~TDSQLite(void);

	bool SQLite_Init(void);
	void SQLite_Finalize();

	bool SQLite_Insert_Order(const wdOrder &pOrder);
	bool SQLite_Insert_Trade(const wdTradeTicket &pTrade);
	bool SQLite_Insert_Position(const wdPosition &);

	bool CancelOrder(const char *Instrument, wdDirectionType Direction = E_Direction_Default, wdOffsetFlagType OffsetFlag = E_OffsetFlag_Default);


private:
	bool _SQLite_Create_Tables();
	bool _SQLite_EXEC(const char *SQL, fnOnQuerySQLite cb = nullptr, void *p = nullptr);
	void _SQLite_Error_Log(int res, const char *SQL, const char *errMsg); // 记录插入SQLite时的错误代码

	sqlite3		*m_sqlite3;
};

#endif