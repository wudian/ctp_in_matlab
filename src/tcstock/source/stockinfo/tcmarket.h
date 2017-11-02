#ifndef tcmarket_h

#define tcmarket_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include "tcstockinfo.h"
#include "tcstockinfolst.h"

/*! \brief tcMarket
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.02
 	
	股市定义类，负责加载和管理该股市下的所有股票信息。
*/
class tcMarket : public QObject
{
	Q_OBJECT

public:
	tcMarket();

	~tcMarket();

	bool LoadFromXml(const QDomElement &pElement);

	bool SaveToXml(QDomDocument &pDoc, QDomElement &pElement);

	bool AppendStock(const QString &pStockCode, const QString &pStockName, tcStockInfo &pStockInfo);

	bool AppendStock(QWidget *pParent, tcStockInfo &pStockInfo);

	bool ModifyStock(QWidget *pParent, int pStockIndex, tcStockInfo &pStockInfo);

	bool RemoveStock(QWidget *pParent, int pStockIndex);

	void RemoveAllStocks();

	bool ImportFromCSV(const QString &pFileName, int &pSuccCount, int &pFailCount);

	bool ExportToCSV(const QString &pFileName, int &pSuccCount, int &pFailCount);

	bool GetStockInfoList(tcStockInfoList &pStockInfoList);

	bool GetStockInfoListFilter(tcStockInfoList &pStockInfoList, const QString &pStockCodeFilter, const QString &pStockNameFilter);

	QString GetName() { return mName; }

	void SetName(const QString pName) { mName = pName; }

	QString GetDescription() { return mDescription; }

	void SetDescription(const QString &pDescription) { mDescription = pDescription; }

private:
	tcStockInfoList mStockInfoList;

	QString mName;

	QString mDescription;

signals:
	void OnStocksModified();

};

#endif //tcmarket_h
