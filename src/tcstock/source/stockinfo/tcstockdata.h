#ifndef tcstockdata_h

#define tcstockdata_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QDate>

#define DAYS_OF_YEAR 366

typedef struct {
	long OpenPrice;
	long ClosePrice;
	long MaxPrice;
	long MinPrice;
	long TotalPrice;
	long Quantity;
	long _Reserved1;	//not used in current version
	long _Reserved2;
	long _Reserved3;
	long _Reserved4;
} tcStockDailyData;

/*! \brief tcStockData
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	负责存取股票的每日数据，每个对象对应一个股票一年内的所有日数据。
	该类由 tcStockDataCache 来统一管理，tcStock 类通过 tcStockDataCache 类来间接取得股票数据。
*/
class tcStockData : public QObject
{
	Q_OBJECT

public:
	tcStockData(const QDir &pBasePath, const QString &pStockCode, int pYear);

	~tcStockData();

	/*!
		read the data from data file.
	*/
	tcStockDailyData* ReadData(const QDate &pDate);

	bool ReadData(const QDate &pDate, tcStockDailyData *pStockDailyData);

	/*!
		write data into data file.
	*/
	bool WriteData(const QDate &pDate, tcStockDailyData *pStockDailyData);

	/*!
		Check if need to save the data into file, and save it directly.
	*/
	bool CheckSaveData();

	QString GetStockCode();

	int GetYear();

protected:
	void LoadFromFile();

	bool SaveToFile();

	void ResetData();

private:
	tcStockDailyData mDailyData[DAYS_OF_YEAR];

	bool mIsModified;

	QDir mBasePath;

	QString mStockCode;

	int mYear;

};

inline tcStockDailyData* tcStockData::ReadData(const QDate &pDate)
{
	tcStockDailyData *data = &mDailyData[pDate.dayOfYear()-1];
	return data;
}

inline bool tcStockData::ReadData(const QDate &pDate, tcStockDailyData *pStockDailyData)
{
	memcpy(pStockDailyData, &mDailyData[pDate.dayOfYear()-1], sizeof(tcStockDailyData));
	return true;
}

inline bool tcStockData::WriteData(const QDate &pDate, tcStockDailyData *pStockDailyData)
{
	memcpy(&mDailyData[pDate.dayOfYear()-1], pStockDailyData, sizeof(tcStockDailyData));
	mIsModified = true;
	return true;
}

#endif //tcstockdata_h
