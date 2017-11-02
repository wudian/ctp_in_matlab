#ifndef tcfavtmgr_h

#define tcfavtmgr_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QDir>

#include "tcfavtgrp.h"

typedef QList<tcFavouriteGroup*> tcFavouriteGroupList;

/*! \brief tcFavouriteManager
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.16
 	
*/
class tcFavouriteManager : public QObject
{
	Q_OBJECT

public:
	tcFavouriteManager(const QDir &pPath);

	~tcFavouriteManager();

	bool LoadFromFile();

	bool SaveToFile();

	tcFavouriteGroup* GetFavouriteGroup(int pGroupIndex);

	bool EditFavouriteList(QWidget *pParent, int pGroupIndex);

	int GetFavouriteGroupCount();

	tcFavouriteGroup* AppendFavouriteGroup(const QString &pName);

	tcFavouriteGroup* AppendFavouriteGroup(QWidget *pParent);

	tcFavouriteGroup* ModifyFavouriteGroup(QWidget *pParent, int pGroupIndex);

	bool RemoveFavouriteGroup(QWidget *pParent, int pGroupIndex);

	bool GetStockInfoList(int pGroupIndex, tcStockInfoList &pStockInfoList);

	bool GetStockInfoListFilter(int pGroupIndex, tcStockInfoList &pStockInfoList, const QString &pStockCodeFilter, const QString &pStockNameFilter);

	void ClearAllFavouriteGroups();

protected slots:
	/*!
		notified by tcFavouriteGroup
	*/
	void DoStocksModified();

private:
	QDir mPath;

	tcFavouriteGroupList mFavouriteGroupList;

	bool mModified;

signals:
	void OnFavouriteGroupModified();

	void OnStocksModified(tcFavouriteGroup *pFavouriteGroup);

};

inline tcFavouriteGroup* tcFavouriteManager::GetFavouriteGroup(int pGroupIndex)
{
	if (pGroupIndex < 0 || pGroupIndex >= mFavouriteGroupList.count()) {
		return NULL;
	}
	return mFavouriteGroupList[pGroupIndex];
}

#endif //tcfavtmgr_h
