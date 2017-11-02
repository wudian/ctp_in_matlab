#ifndef SMART_POINTER_MXARRAY_H
#define SMART_POINTER_MXARRAY_H

#include <vector>
#include <engine.h>

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

class ENGINE_API SmartPointerMxArray {
	mxArray *m_mx;
public:
	SmartPointerMxArray();
	SmartPointerMxArray(mxArray *mx);
	~SmartPointerMxArray();
	SmartPointerMxArray &operator=(mxArray *mx);
	operator mxArray*();
	bool isMxArrayNull();
private:
	SmartPointerMxArray(const SmartPointerMxArray &);
};

class SmartPointerMwSize {
	mwSize *m_size;
public:
	SmartPointerMwSize();
	SmartPointerMwSize(const std::vector<mwSize> &vecSiz);
	~SmartPointerMwSize();
	operator mwSize*();
private:
	SmartPointerMwSize(const SmartPointerMwSize &);
};

#endif // SMART_POINTER_MXARRAY_H