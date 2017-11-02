#include "SmartPointer.h"

SmartPointerMxArray::SmartPointerMxArray() 
{
	m_mx = NULL;
}

SmartPointerMxArray::SmartPointerMxArray(mxArray *mx) 
{
	m_mx = mx;
}

SmartPointerMxArray::~SmartPointerMxArray() 
{
	if(m_mx) 
		mxDestroyArray(m_mx);
}

SmartPointerMxArray &SmartPointerMxArray::operator=(mxArray *mx) 
{
	if(m_mx)
		mxDestroyArray(m_mx); 
	m_mx = mx; 
	return *this;
}

bool SmartPointerMxArray::isMxArrayNull()
{
	return NULL == m_mx;
}

SmartPointerMxArray::operator mxArray*() 
{
	return m_mx;
}

SmartPointerMwSize::SmartPointerMwSize() 
{
	m_size = NULL;
}

SmartPointerMwSize::SmartPointerMwSize(const std::vector<mwSize> &vecSiz) 
{
	m_size = new mwSize[vecSiz.size()];
	mwSize *p = m_size;
	std::vector<mwSize>::const_iterator it = vecSiz.begin();
	while (it != vecSiz.end())
		*p++ = *it++;
}

SmartPointerMwSize::~SmartPointerMwSize()
{
	if (m_size)
		delete []m_size;
}

SmartPointerMwSize::operator mwSize*() 
{
	return m_size;
}