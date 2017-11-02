#include "MatlabEngine.h"
#include <windows.h>
#include <map>
#include <thread>
#include <iostream>
#include <chrono>
//#include <boost/progress.hpp>
#include "HelpFunction.h"

MatlabEngine *MatlabEngine::m_myself = NULL;
std::map<std::thread::id, Engine *> m_thread_engine;

MatlabEngine *MatlabEngine::instance()
{
	std::thread::id thread_id = std::this_thread::get_id();
	if (NULL == m_thread_engine[thread_id]) {
		m_thread_engine[thread_id] = engOpen(NULL);  // engOpenSingleUse(NULL, NULL, NULL);
		//engSetVisible(m_thread_engine[thread_id], 0);
	}
	
	if (NULL == m_myself)
		m_myself = new MatlabEngine();
	return m_myself;
}

MatlabEngine::MatlabEngine(void)
{
	//m_engine = engOpen(NULL); // 开启引擎
 //	if (NULL == m_engine)
	//	m_last_error = "fail to open engine";
}


MatlabEngine::~MatlabEngine(void)
{
	//engClose(m_thread_engine.begin()->second);
	for (std::map<std::thread::id, Engine *>::const_iterator it = m_thread_engine.begin();
		it != m_thread_engine.end(); ++it) {
			engClose(it->second);
	}
}

bool MatlabEngine::CallMATLAB(const char *script_) 
{
	Engine *engine = m_thread_engine[std::this_thread::get_id()];
	if (NULL == engine) {
		m_last_error = "Engine == NULL";
		return false;
	}

	std::string mScript = (std::string)"clear temp_errMsg;\r\n" + "try \r\n" + script_
		+ "\r\n catch temp_exp \r\n temp_errMsg = temp_exp.message; \r\n end";

	if (0 != engEvalString(engine, mScript.c_str())) { // 错误出在引擎
		m_last_error = "the engine session is no longer running or the engine pointer is invalid or NULL";
		return false;
	}

	SmartPointerMxArray mx = engGetVariable(engine, "temp_errMsg");
	if (!mx.isMxArrayNull()) { // 执行脚本时发生错误，并抛出了异常
		char *str = mxArrayToString(mx);
		m_last_error = str;
		mxFree(str);
		return false;
	}

	return true;
}

void MatlabEngine::GetMATLABVar(const char *name_, SmartPointerMxArray &mx_)
{
	Engine *engine = m_thread_engine[std::this_thread::get_id()];
	if (NULL == engine) {
		m_last_error = "Engine == NULL";
		return;
	}
	mx_ = engGetVariable(engine, name_);
}

bool MatlabEngine::SetMATLABVar(const char *name_, const mxArray *var_)
{
	Engine *engine = m_thread_engine[std::this_thread::get_id()];
	if (NULL == engine) {
		m_last_error = "Engine == NULL";
		return false;
	}
	if (0 != engPutVariable(engine, name_, var_)) { // 失败
		return false;
	}
	return true;
}

// 用于测试matlab engine的效率
void MatlabEngine::thread_fun_1(std::queue<double> &close_1_, std::condition_variable &condition_1, std::mutex &mutex_)
{
	//boost::progress_timer t;

	if (!MatlabEngine::instance()->CallMATLAB("cd F:/MATLAB_INVESTIGATE/Win32;")) {
		std::cout << MatlabEngine::instance()->get_last_error() << std::endl;
		return;
	}

	while (1) {
		double last_price_1 = 0.;
		{
			std::unique_lock<std::mutex>  lock(mutex_);
			if (close_1_.empty()) {
				// Notice that the lock is passed to wait: wait will atomically add the thread to the set of threads 
				// waiting on the condition variable, and unlock the mutex. When the thread is woken, the mutex will
				// be locked again before the call to wait returns.
				if (!condition_1.wait_until(lock, std::chrono::system_clock::now()+std::chrono::milliseconds(3)))
					break;
			}

			last_price_1 = close_1_.front(); // 取最新价格
			close_1_.pop();
		}
		
		SmartPointerMxArray mx_action;
		{
			//boost::progress_timer t;
			// 将最新价格塞入engine中
			SmartPointerMxArray mx_last_price_1 = mxCreateDoubleScalar(last_price_1);
			if (!MatlabEngine::instance()->SetMATLABVar("last_price_1", mx_last_price_1)) {
				std::cout << MatlabEngine::instance()->get_last_error() << std::endl;
				continue;
			}

			if (!MatlabEngine::instance()->CallMATLAB("action_1 = MA_CROSS(last_price_1);")) {
				std::cout << MatlabEngine::instance()->get_last_error() << std::endl;
				continue;
			}

			MatlabEngine::instance()->GetMATLABVar("action_1", mx_action);
			std::cout << std::this_thread::get_id() << "\n";
		}
		


		if (MatlabEngine::getDoubleFromMatlabNumeric(mx_action, 0) == 1)
			std::cout << "在" << last_price_1 << "买入 at thread1 engine\n";
		else if (MatlabEngine::getDoubleFromMatlabNumeric(mx_action, 0) == -1)
			std::cout << "在" << last_price_1 << "卖出 at thread1 engine\n";
		else
			;
	}
	//std::cout << "thread1 engine use" << t.elapsed() << std::endl;
}

/*
void MatlabEngine::thread_fun_3(std::queue<double> &close_3_, boost::condition_variable &condition_3, boost::mutex &mutex_)
{
	//boost::progress_timer t;

	if (!MatlabEngine::instance()->CallMATLAB("cd F:/MATLAB_INVESTIGATE/Win32;")) {
		std::cout << MatlabEngine::instance()->get_last_error() << std::endl;
		return;
	}

	while (1) {
		double last_price_3 = 0.;
		{
			boost::mutex::scoped_lock lock(mutex_);
			if (close_3_.empty()) {

				if (!condition_3.timed_wait(lock, boost::posix_time::seconds(3)))
					break;
			}

			last_price_3 = close_3_.front(); // 取最新价格
			close_3_.pop();
		}

		SmartPointerMxArray mx_action;
		{
			boost::progress_timer t;
		
			// 将最新价格塞入engine中
			SmartPointerMxArray mx_last_price_3 = mxCreateDoubleScalar(last_price_3);
			if (!MatlabEngine::instance()->SetMATLABVar("last_price_3", mx_last_price_3)) {
				std::cout << MatlabEngine::instance()->get_last_error() << std::endl;
				continue;
			}

			if (!MatlabEngine::instance()->CallMATLAB("action_3 = MA_CROSS(last_price_3);")) {
				std::cout << MatlabEngine::instance()->get_last_error() << std::endl;
				continue;
			}

		
			MatlabEngine::instance()->GetMATLABVar("action_3", mx_action);

			std::cout << boost::this_thread::get_id() << "\t";
		}
		if (MatlabEngine::getDoubleFromMatlabNumeric(mx_action, 0) == 1)
			std::cout << "在" << last_price_3 << "买入 at thread3 engine\n";
		else if (MatlabEngine::getDoubleFromMatlabNumeric(mx_action, 0) == -1)
			std::cout << "在" << last_price_3 << "卖出 at thread3 engine\n";
		else
			;


	}
	//std::cout << "thread3 engine use" << t.elapsed() << std::endl;
}
*/

double MatlabEngine::getDoubleFromMatlabNumeric(const mxArray* mx, mwIndex i)
{
	switch (mxGetClassID(mx)) {
	case mxDOUBLE_CLASS:
		return ((double*)mxGetData(mx))[i];
	case mxSINGLE_CLASS:
		return ((float*)mxGetData(mx))[i];
	case mxINT8_CLASS:
		return ((signed char*)mxGetData(mx))[i];
	case mxUINT8_CLASS:
		return ((unsigned char*)mxGetData(mx))[i];
	case mxINT16_CLASS:
		return ((short int*)mxGetData(mx))[i];
	case mxUINT16_CLASS:
		return ((unsigned short int*)mxGetData(mx))[i];
	case mxINT32_CLASS:
		return ((int*)mxGetData(mx))[i];
	case mxUINT32_CLASS:
		return ((size_t*)mxGetData(mx))[i];
	case mxINT64_CLASS:
		return (double)(((int64_T*)mxGetData(mx))[i]);
	case mxUINT64_CLASS:
		return (double)(((uint64_T*)mxGetData(mx))[i]);
	default:
		return 0.;
	}
}

//void MatlabEngine::thread_fun_0()
//{
//	SmartPointerMxArray mx;
//	MatlabEngine::instance()->GetMATLABVar("szzs_close", mx);
//
//	mwSize nDimensions = mxGetNumberOfDimensions(mx); //always 2 : n * 1的矩阵
//	const mwSize *dimensions = mxGetDimensions(mx);
//	mwSize lines = dimensions[0];
//	for (int i = 0; i < lines; ++i) {
//		double close = getDoubleFromMatlabNumeric(mx, i);
//		g_close_1.push(close);
//		g_close_2.push(close);
//	}
//}