#ifndef tcstockdatacache_h

#define tcstockdatacache_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QDate>

#include "tcstockdata.h"

/*! \brief tcStockDataCache
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	对 tcStockData 类的简单再封装，使其能支持使用频度的计数，
	tcStockDataCache 类需要根据该频度来动态释放掉一些不使用的对象。
*/
class tcStockDataCacheItem : public tcStockData
{
	Q_OBJECT

public:
	tcStockDataCacheItem(const QDir &pBasePath, const QString &pStockCode, int pYear);

	~tcStockDataCacheItem();

	/*!
		get the current reference count.
	*/
	int GetRefCount();

	/*!
		increase the reference count.
	*/
	int IncRefCount();

	/*!
		reset the reference count.
	*/
	void ResetRefCount();

private:
	int mRefCount;

};

/*! \brief tcStockDataCache
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	管理某个 tcMarket 下所有股票的日数据 tcStockDataCacheItem，
	自动根据使用频度来释放一些旧的数据内存。
	tcStock 类通过直接访问该类来取得其相应的数据。
*/
class tcStockDataCache : public QObject
{
	Q_OBJECT

public:
	tcStockDataCache(const QDir &pBasePath);

	~tcStockDataCache();

	/*!
		read the specified stock's data.
	*/
	tcStockDailyData* ReadData(const QString &pStockCode, const QDate &pDate);

	bool ReadData(const QString &pStockCode, const QDate &pDate, tcStockDailyData *pStockDailyData);

	bool ReadData(const QString &pStockCode, const QDate &pStartDate, int pDayCount, tcStockDailyData *pData);

	/*!
		write the specified stock's data.
	*/
	bool WriteData(const QString &pStockCode, const QDate &pDate, tcStockDailyData *pStockDailyData);

	/*!
		check and save all stock data into file.
	*/
	bool SaveAllStockData();

protected:
	/*!
		check if the cache size over MAX_CACHEITEM_COUNT, and try to free some.
	*/
	void CheckFreeCache();

private:
	QDir mBasePath;

	QMap<QString, tcStockDataCacheItem*> mStockDataMap;

	int mMaxRefCount;

};

inline tcStockDailyData* tcStockDataCache::ReadData(const QString &pStockCode, const QDate &pDate)
{
	QString keyname = "%1_%2";
	keyname = keyname.arg(pStockCode).arg(pDate.year());
	tcStockDataCacheItem *dataitem;
	if (mStockDataMap.contains(keyname)) {
		dataitem = mStockDataMap[keyname];
	}
	else {
		CheckFreeCache();
		dataitem = new tcStockDataCacheItem(mBasePath, pStockCode, pDate.year());
		mStockDataMap.insert(keyname, dataitem);
	}
	if (dataitem->IncRefCount() > mMaxRefCount) {
		mMaxRefCount = dataitem->GetRefCount();
	}
	return dataitem->ReadData(pDate);
}

inline bool tcStockDataCache::ReadData(const QString &pStockCode, const QDate &pDate, tcStockDailyData *pStockDailyData)
{
	QString keyname = "%1_%2";
	keyname = keyname.arg(pStockCode).arg(pDate.year());
	tcStockDataCacheItem *dataitem;
	if (mStockDataMap.contains(keyname)) {
		dataitem = mStockDataMap[keyname];
	}
	else {
		CheckFreeCache();
		dataitem = new tcStockDataCacheItem(mBasePath, pStockCode, pDate.year());
		mStockDataMap.insert(keyname, dataitem);
	}
	if (dataitem->IncRefCount() > mMaxRefCount) {
		mMaxRefCount = dataitem->GetRefCount();
	}
	return dataitem->ReadData(pDate, pStockDailyData);
}

inline bool tcStockDataCache::ReadData(const QString &pStockCode, const QDate &pStartDate, int pDayCount, tcStockDailyData *pData)
{
	pData->OpenPrice = 0;
	pData->ClosePrice = 0;
	pData->MaxPrice = 0;
	pData->MinPrice = 0;
	pData->TotalPrice = 0;
	pData->Quantity = 0;

	QDate date = pStartDate;
	int i, year = 0;
	tcStockDataCacheItem *dataitem = NULL;
	for (i=0; i<pDayCount; i++) {
		if (year != date.year() || dataitem == NULL) {
			year = date.year();
			QString keyname = "%1_%2";
			keyname = keyname.arg(pStockCode).arg(year);
			if (mStockDataMap.contains(keyname)) {
				dataitem = mStockDataMap[keyname];
			}
			else {
				CheckFreeCache();
				dataitem = new tcStockDataCacheItem(mBasePath, pStockCode, year);
				mStockDataMap.insert(keyname, dataitem);
			}
			if (dataitem->IncRefCount() > mMaxRefCount) {
				mMaxRefCount = dataitem->GetRefCount();
			}
		}
		tcStockDailyData *data = dataitem->ReadData(date);

		if (pData->OpenPrice == 0.0 && data->OpenPrice != 0.0) {
			pData->OpenPrice = data->OpenPrice;
		}
		if (data->ClosePrice != 0.0) {
			pData->ClosePrice = data->ClosePrice;
		}
		if (pData->MaxPrice < data->MaxPrice) {
			pData->MaxPrice = data->MaxPrice;
		}
		if (data->MinPrice != 0.0 && (data->MinPrice < pData->MinPrice || pData->MinPrice == 0.0)) {
			pData->MinPrice = data->MinPrice;
		}
		pData->TotalPrice += data->TotalPrice;
		pData->Quantity += data->Quantity;

		date = date.addDays(1);
	}
	return true;
}

inline bool tcStockDataCache::WriteData(const QString &pStockCode, const QDate &pDate, tcStockDailyData *pStockDailyData)
{
	QString keyname = "%1_%2";
	keyname = keyname.arg(pStockCode).arg(pDate.year());
	tcStockDataCacheItem *dataitem;
	if (mStockDataMap.contains(keyname)) {
		dataitem = mStockDataMap[keyname];
	}
	else {
		CheckFreeCache();
		dataitem = new tcStockDataCacheItem(mBasePath, pStockCode, pDate.year());
		mStockDataMap.insert(keyname, dataitem);
	}
	if (dataitem->IncRefCount() > mMaxRefCount) {
		mMaxRefCount = dataitem->GetRefCount();
	}
	return dataitem->WriteData(pDate, pStockDailyData);
}

#endif //tcstockdatacache_h

