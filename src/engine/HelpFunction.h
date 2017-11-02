#ifndef HELP_FUNCTION_H
#define HELP_FUNCTION_H

#include "engine.h"


typedef std::vector<mwSize> MATRIXDIMENSION;
// 用于lua/c++、matlab中多维数组的转换
typedef MATRIXDIMENSION MATRIXINDEX;//举例：如果MATRIXINDEX中为2、3
typedef std::vector<MATRIXDIMENSION> MATRIXINDEXLIST;//举例：那么MATRIXINDEXLIST就应该为00、01、02、10、11、12
typedef MATRIXINDEXLIST::const_iterator ConstIteratorOfIndexList;



void getIndexList(const MATRIXDIMENSION &dimensions, MATRIXINDEXLIST &indexList); // indexList中的坐标的递增是以靠右先增的顺序

double getDoubleFromMatlabNumeric(const mxArray* mx, mwIndex i);



#endif