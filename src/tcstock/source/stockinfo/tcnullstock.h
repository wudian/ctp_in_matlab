#ifndef tcnullstock_h

#define tcnullstock_h

#include <QtCore/QVariant>
#include <QtCore/QObject>

#include "tcstock.h"

/*! \brief tcNullStock
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2007.03.20
 	
	该类不产生任何实际效用，作为一个空的股票信息对象而存在。
	为了使 tcStockInfo 类通过重载的 -> 操作符访问 tcStock 时，避免范围到不存在的数据，该情况下，tcStockInfo 将返回一个该类的静态全局对象。
*/
class tcNullStock : public tcStock
{
	Q_OBJECT

public:
	tcNullStock();

	virtual const tcStockDailyData* ReadData(const QDate &pDate);

	virtual bool ReadData(const QDate &pDate, tcStockDailyData *pStockDailyData);

	virtual bool ReadData(const QDate &pStartDate, int pDayCount, tcStockDailyData *pData);

	virtual bool WriteData(const QDate &pDate, tcStockDailyData *pStockDailyData);

	virtual QString GetStockName();

	virtual QString GetDescription();

	static tcNullStock NullStock;

};

inline const tcStockDailyData* tcNullStock::ReadData(const QDate &pDate)
{
	return NULL;
}

inline bool tcNullStock::ReadData(const QDate &pDate, tcStockDailyData *pStockDailyData)
{
	return false;
}

inline bool tcNullStock::ReadData(const QDate &pStartDate, int pDayCount, tcStockDailyData *pData)
{
	return false;
}

inline bool tcNullStock::WriteData(const QDate &pDate, tcStockDailyData *pStockDailyData)
{
	return false;
}

#endif //tcnullstock_h
