
#include "KLine.h"
#include "Types.h"

CKLine::CKLine(void)
{
	strcpy_s(InstrumentID, "");
	strcpy_s(ExchangeTime, NORMAL_TIME);
}

CKLine::~CKLine(void)
{
}
