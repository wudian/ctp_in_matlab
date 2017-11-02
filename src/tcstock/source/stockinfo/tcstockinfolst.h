#ifndef tcstockinfolst_h

#define tcstockinfolst_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include "tcstockinfo.h"

class tcMarket;
class tcFavouriteGroup;

/*! \brief tcStockInfoList
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.16
 	
*/
class tcStockInfoList : public QObject, public QList<tcStockInfo>
{
	Q_OBJECT

public:
	tcStockInfoList();

	tcStockInfoList(const tcStockInfoList &pStockInfoList);

	bool LoadFromXml(const QDomElement &pElement);

	bool SaveToXml(QDomDocument &pDoc, QDomElement &pElement);

	bool GetGroupList(QStringList &pStringList);

	bool ReloadFromGroup(int pGroupIndex);

	bool ReloadFromGroupFilter(int pGroupIndex, const QString &pStockCodeFilter, const QString &pStockNameFilter);

	tcStockInfoList& operator=(const tcStockInfoList &pStockInfoList);

protected slots:
	/*!
		be notified by tcMarketManager::OnMarketsModified.
	*/
	void DoMarketManagerMarketsModified();

	/*!
		be notified by tcMarketManager::OnStocksModified.
	*/
	void DoMarketManagerStocksModified(tcMarket *pMarket);

	/*!
		be notified by tcFavouriteManager::OnFavouriteGroupModified.
	*/
	void DoFavouriteManagerFavouriteGroupModified();

	/*!
		be notified by tcFavouriteManager::OnStocksModified.
	*/
	void DoFavouriteManagerStocksModified(tcFavouriteGroup *pFavouriteGroup);

signals:
	void OnGroupListNeedReload();

	void OnStockListNeedReload();

};

#endif //tcstockinfolst_h
