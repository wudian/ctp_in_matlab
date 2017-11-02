#ifndef _CTP_REQ_MSG_QUEUE_H_
#define _CTP_REQ_MSG_QUEUE_H_

#include <queue>
#include <map>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "Types.h"

enum E_CTPReqType;
class CCTPReqMsgItem;
class CMyThreads;
class CThostFtdcTraderApi;

class CCTPReqMsgQueue
{
public:
	CCTPReqMsgQueue(std::atomic<unsigned int> &);
	~CCTPReqMsgQueue(void);

	//void InputQueue_Important(std::shared_ptr<CCTPReqMsgItem>);
	void InputQueue(std::shared_ptr<CCTPReqMsgItem>);

private:
	//void ProcessImportantReqs();
	void ProcessReqs();

private:
	//std::mutex										m_mutex_Important;
	//std::condition_variable							m_condition_variable_Important;
	//std::queue<std::shared_ptr<CCTPReqMsgItem> >	m_reqQueue_Important; // ÏÂµ¥¡¢³·µ¥
	//std::shared_ptr<CMyThreads>						m_pThreads_Important;

	

	std::atomic<unsigned int>						&m_nRequestID;
	
	volatile int									m_nSleep;
};

#endif