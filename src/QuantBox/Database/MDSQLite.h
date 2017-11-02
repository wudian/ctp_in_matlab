#ifndef _MD_SQLITE_H_
#define _MD_SQLITE_H_

#include <map>
#include <string>
#include <memory>
#include "sqlitebase.h"
#include "Types.h"

class CCTPRspMsgQueue;
struct wdTick;
struct wdKLine;
class CCTPRspMsgItem;

class MDSQLite : public SQLiteBase
{
public:
	MDSQLite(void);
	virtual ~MDSQLite(void);

	virtual bool SQLite_Init(void);
	virtual bool SQLite_Create_Tables();	// Tick表和K线表
	virtual void SQLite_Finalize();

	virtual void SQLite_MarketData_Insert(const wdTick &tick);
	
	virtual void SubscribeHistory(const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod, const char *beginTime, const char *endTime);
	
	std::map<std::string, wdKLine> &GetPeriod_KLine(const char *szInstrumentID) { return m_mapHistoryInstKLine[szInstrumentID]; }
private:
	std::string GetTableName(const std::string &period);

	void SQLite_Tick_Insert(const wdTick *tick);
	void SQLite_K_Line_Insert(wdKLine &kline);

	void AddPeriods(const std::list<std::string> &listInstrumentIDs, const std::list<std::string> &listPeriod);

	
private:
	std::map<std::string, std::map<std::string, wdKLine> >		m_mapInstKLine;	

	std::map<std::string, std::map<std::string, bool> >			m_mapHasSubscribe;
	std::map<std::string, std::map<std::string, wdKLine> >		m_mapHistoryInstKLine;
};

#endif