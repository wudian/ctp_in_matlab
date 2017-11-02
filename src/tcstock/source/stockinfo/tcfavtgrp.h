#ifndef tcfavtgrp_h

#define tcfavtgrp_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include "tcstockinfo.h"
#include "tcstockinfolst.h"

/*! \brief tcFavouriteGroup
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.16
 	
*/
class tcFavouriteGroup : public QObject
{
	Q_OBJECT

public:
	tcFavouriteGroup();

	~tcFavouriteGroup();

	bool LoadFromXml(const QDomElement &pElement);

	bool SaveToXml(QDomDocument &pDoc, QDomElement &pElement);

	bool AppendFavourite(const QString &pStockCode, tcStockInfo &pStockInfo);

	bool AppendFavourite(QWidget *pParent, tcStockInfoList &pStockInfoList);

	bool ModifyFavourite(QWidget *pParent, int pFavouriteIndex, tcStockInfo &pStockInfo);

	bool RemoveFavourite(QWidget *pParent, int pFavouriteIndex);

	bool IsFavouriteExists(const tcStockInfo &pStockInfo);

	bool GetStockInfoList(tcStockInfoList &pStockInfoList);

	bool GetStockInfoListFilter(tcStockInfoList &pStockInfoList, const QString &pStockCodeFilter, const QString &pStockNameFilter);

	QString GetName();

	void SetName(const QString &pValue);

	QString GetDescription();

	void SetDescription(const QString &pValue);

private:
	tcStockInfoList mStockInfoList;

	QString mName;

	QString mDescription;

signals:
	void OnStocksModified();

};

#endif //tcfavtgrp_h

