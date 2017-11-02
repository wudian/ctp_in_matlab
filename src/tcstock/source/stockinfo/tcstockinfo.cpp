#include "tcstockinfo.h"

tcStockInfo::tcStockInfo()
{
	mStockCode = "";
}

tcStockInfo::tcStockInfo(const QString &pStockCode)
{
	mStockCode = pStockCode;
}

tcStockInfo::tcStockInfo(const tcStockInfo &pInfo)
{
	mStockCode = pInfo.mStockCode;
}

QString tcStockInfo::GetStockCode()
{
	return mStockCode;
}

tcStockInfo& tcStockInfo::operator=(const tcStockInfo &pInfo)
{
	mStockCode = pInfo.mStockCode;
	return *this;
}

bool tcStockInfo::operator==(const tcStockInfo &pInfo)
{
	if (mStockCode != pInfo.mStockCode) {
		return false;
	}
	return true;
}
