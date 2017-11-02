#ifndef MATLAB_ENGINE_H
#define MATLAB_ENGINE_H

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <engine.h>
#include "SmartPointer.h"


class ENGINE_API MatlabEngine
{
public:
	static MatlabEngine *instance();
	~MatlabEngine(void);

	bool CallMATLAB(const char *script_);
	void GetMATLABVar(const char *name_, SmartPointerMxArray &mx_);
	bool SetMATLABVar(const char *name_, const mxArray *var_);
	std::string get_last_error() { return m_last_error; }

	// 用于测试matlab engine的效率
	void thread_fun_1(std::queue<double> &, std::condition_variable &, std::mutex &);
	//void thread_fun_3(std::queue<double> &, std::condition_variable &, std::mutex &);

	static double getDoubleFromMatlabNumeric(const mxArray* mx, mwIndex i);
protected:
	MatlabEngine(void);

private:
	static MatlabEngine *m_myself;
	std::string m_last_error;
};

#endif // MATLAB_ENGINE_H