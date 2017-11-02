#include "tcstockdatacache.h"

#define MAX_CACHEITEM_COUNT 500

tcStockDataCacheItem::tcStockDataCacheItem(const QDir &pBasePath, const QString &pStockCode, int pYear)
	: tcStockData(pBasePath, pStockCode, pYear)
{
	mRefCount = 0;
}

tcStockDataCacheItem::~tcStockDataCacheItem()
{
}

int tcStockDataCacheItem::GetRefCount()
{
	return mRefCount;
}

int tcStockDataCacheItem::IncRefCount()
{
	return ++mRefCount;
}

void tcStockDataCacheItem::ResetRefCount()
{
	mRefCount = 0;
}



tcStockDataCache::tcStockDataCache(const QDir &pBasePath)
{
	mBasePath = pBasePath.absolutePath() + "/data";
	mMaxRefCount = 0;
}

tcStockDataCache::~tcStockDataCache()
{
	foreach (tcStockDataCacheItem *item, mStockDataMap) {
		delete item;
	}
	mStockDataMap.clear();
}

bool tcStockDataCache::SaveAllStockData()
{
	bool haveerror = false;
	foreach(tcStockDataCacheItem *item, mStockDataMap) {
		if (! item->CheckSaveData()) {
			haveerror = true;
		}
	}
	return (! haveerror);
}

void tcStockDataCache::CheckFreeCache()
{
	if (mStockDataMap.count() <= MAX_CACHEITEM_COUNT) {
		return;
	}
	mMaxRefCount = mMaxRefCount / 2;
	QMap<QString, tcStockDataCacheItem*>::iterator itr = mStockDataMap.begin();
	while (itr != mStockDataMap.end()) {
		tcStockDataCacheItem *item = itr.value();
		if (item->GetRefCount() < mMaxRefCount) {
			itr = mStockDataMap.erase(itr);
			delete item;
		}
		else {
			item->ResetRefCount();
			++itr;
		}
	}
}
