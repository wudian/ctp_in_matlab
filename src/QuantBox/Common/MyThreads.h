#ifndef _MY_THREADS_H_
#define _MY_THREADS_H_

#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <memory>

class CMyThreads
{
public:
	CMyThreads(int nThreadNums, std::function<void (void)> _Fun, 
		std::function<void (void)> _FunFormer = nullptr, std::function<void (void)> _FunLater = nullptr);
	~CMyThreads();

	void start();
	void terminate();

private:
	void run();

	CMyThreads(const CMyThreads &);
	CMyThreads & operator=(const CMyThreads &);

private:
	int								m_nThreadNums;
	std::atomic<bool>				m_b_is_finish;
	std::function<void (void)>		m_Fun;
	std::function<void (void)>		m_FunFormer;
	std::function<void (void)>		m_FunLater;
	std::mutex						m_Mtx;
	std::vector<std::thread *>		m_Elts;

	static void destroy(std::thread *_Thrd)
	{	// delete a pointer to thread
		delete _Thrd;
	}

	static inline void join(std::thread *_Thrd)
	{	// join a thread
		_Thrd->join();
	}
};

#endif
