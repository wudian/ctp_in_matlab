#ifndef _CTP_COMMON_API_
#define _CTP_COMMON_API_

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>

class CCTPRspMsgQueue;
enum wdConnectionStatus;
class CppMysql;
class TDSQLite;

class CCTPCommonApi
{
protected:
	CCTPCommonApi();
	virtual ~CCTPCommonApi();

	std::shared_ptr<TDSQLite>			m_sqliteDB;

	std::shared_ptr<CppMysql>			m_pMysql;	

	std::shared_ptr<CCTPRspMsgQueue>	m_msgQueue;				//缓存队列

	std::atomic<unsigned int>			m_nRequestID;			//请求ID, 保持自增

	wdConnectionStatus					m_status;				//连接状态
	std::mutex							m_mutex_Status;
	std::condition_variable				m_cvStatus;
};

#endif