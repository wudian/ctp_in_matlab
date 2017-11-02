#include "MyThreads.h"
#include <xutility>

CMyThreads::CMyThreads(int nThreadNums, std::function<void (void)> _Fun,
					   std::function<void (void)> _FunFormer, std::function<void (void)> _FunLater)
	: m_nThreadNums(nThreadNums)
	, m_b_is_finish(false)
	, m_Fun(_Fun)
	, m_FunFormer(_FunFormer)
	, m_FunLater(_FunLater)
{
}

CMyThreads::~CMyThreads()
{
	for (std::thread *_Thrd : m_Elts) {
		destroy(_Thrd);
	}
}

void CMyThreads::start()
{
	for (int i = 0; i < m_nThreadNums; ++i) {
		std::thread *_Thrd = new std::thread(&CMyThreads::run, this);		
		m_Elts.push_back(_Thrd);
	}
}

void CMyThreads::terminate()
{
	m_b_is_finish = true;

	for (std::thread *_Thrd : m_Elts) {
		join(_Thrd);
		destroy(_Thrd);
	}
	m_Elts.clear();
}

void CMyThreads::run()
{
	if (nullptr != m_FunFormer)
		m_FunFormer();
	while (!m_b_is_finish)
	{
		m_Fun();
	}
	if (nullptr != m_FunLater)
		m_FunLater();
}
