#include <vector>
#include <string>
#include "HelpFunction.h"




void getIndexList(const MATRIXDIMENSION &dimensions, MATRIXINDEXLIST &indexList)
{
	MATRIXINDEX vecEx;
	mwSize temp = 1;
	MATRIXINDEX::const_reverse_iterator it;
	for(it = dimensions.rbegin(); it != dimensions.rend();	++it) {
		temp *= *it;
		vecEx.push_back(temp);
	}

	mwSize nums = vecEx.back();
	vecEx.pop_back();
	for(mwSize i=0; i<nums; ++i) {
		MATRIXINDEX in;
		mwSize last = i;
		for (it = vecEx.rbegin();	it != vecEx.rend();	++it) {
			in.push_back(last/ *it);
			last %= *it;
		}

		in.push_back(last);
		indexList.push_back(in);
	}
}

double getDoubleFromMatlabNumeric(const mxArray* mx, mwIndex i)
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
