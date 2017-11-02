#ifndef tcstockdataitemmdl_h

#define tcstockdataitemmdl_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QStandardItemModel>

#include "tcmarket.h"

/*! \brief tcStockDataItemModel
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	编辑 tcStockData 用的ItemModel，被 tcStockDataInfoDialog 所使用。
*/
class tcStockDataItemModel : public QStandardItemModel
{
	Q_OBJECT

public:
	tcStockDataItemModel(QObject *pParent);

	bool GetGroupList(QStringList &pStringList);

	/*!
		here the pGroupIndex means the favourite group's index or market's index that user selected.
		pGroupIndex < 0 means the favourite group's index, > 0 means the market's index.
	*/
	void CreateStockList(int pGroupIndex, const QString &pStockCodeFilter, const QString &pStockNameFilter);

	void LoadStockData(const QDate &pDate);

	const tcStockDailyData* ReadData(int pRow);

	bool WriteData(int pRow, tcStockDailyData* pStockDailyData);

private:
	tcStockInfoList mViewStockInfoList;

	QDate mEditDate;

};

#endif //tcstockdateitemmdl_h

