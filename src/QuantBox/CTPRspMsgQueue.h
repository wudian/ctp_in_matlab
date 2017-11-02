#ifndef _CTP_RSP_MSG_QUEUE_H_
#define _CTP_RSP_MSG_QUEUE_H_

#include <map>
#include <future>
#include <list>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "Types.h"

class CCTPRspMsgItem;
struct wdKLine;
class TDSQLite;
class CMyThreads;
class CppMysql;
enum wdSystemType;

class CCTPRspMsgQueue
{
public:
	CCTPRspMsgQueue(wdSystemType, TDSQLite *pSqliteDB = nullptr);
	~CCTPRspMsgQueue(void);

	void InputQueue(const std::shared_ptr<CCTPRspMsgItem> &);
	
private:
	void _RunInThreadFormer();
	void _RunInThread();
	void _RunInThreadLater();

	void _SQLite_OnOrder(const std::shared_ptr<CCTPRspMsgItem> &);
	void _SQLite_OnTrade(const std::shared_ptr<CCTPRspMsgItem> &);


	void _Output_OnRtnDepthMarketData(const std::shared_ptr<CCTPRspMsgItem> &);
	void _Output_OnHistoryTick(const std::shared_ptr<CCTPRspMsgItem> &);
	void _Output_OnHistoryKLine(const std::shared_ptr<CCTPRspMsgItem> &);

private:
	wdSystemType									m_type; // 行情 or 交易
	std::queue<std::shared_ptr<CCTPRspMsgItem> >	m_queue;		
	std::mutex										m_mutex; // 保护 m_queue
	std::condition_variable							m_conditionVariable;
	std::shared_ptr<CMyThreads>						m_pThreads;

#ifdef MD_SERVER // 服务器
	std::map<std::thread::id, CppMysql>				m_mapMysql;
#endif

	TDSQLite										*m_pSqliteDB;
};

#endif