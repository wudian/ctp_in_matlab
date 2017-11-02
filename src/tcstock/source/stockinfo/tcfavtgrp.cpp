#include "tcfavtgrp.h"

#include <QMessageBox>

#include "../tcdefine.h"
#include "../service/tcsvcpack.h"
#include "../stockinfo/tcstockinfopack.h"

tcFavouriteGroup::tcFavouriteGroup()
{
}

tcFavouriteGroup::~tcFavouriteGroup()
{
}

bool tcFavouriteGroup::LoadFromXml(const QDomElement &pElement)
{
	mStockInfoList.clear();

	mName = pElement.attribute("Name");
	mDescription = pElement.attribute("Description");

	mStockInfoList.LoadFromXml(pElement);
	return true;
}

bool tcFavouriteGroup::SaveToXml(QDomDocument &pDoc, QDomElement &pElement)
{
	pElement.setAttribute("Name", mName);
	pElement.setAttribute("Description", mDescription);

	mStockInfoList.SaveToXml(pDoc, pElement);
	return true;
}

bool tcFavouriteGroup::AppendFavourite(const QString &pStockCode, tcStockInfo &pStockInfo)
{
	tcStockInfo stockinfo(pStockCode);
	if (IsFavouriteExists(stockinfo)) {
		return false;
	}
	mStockInfoList.append(stockinfo);
	pStockInfo = stockinfo;
	emit OnStocksModified();
	return true;
}

bool tcFavouriteGroup::AppendFavourite(QWidget *pParent, tcStockInfoList &pStockInfoList)
{
	tcStockInfoList stockinfolist;
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();
	if (! marketmanager->SelectStock(pParent, stockinfolist)) {
		return false;
	}
	foreach (tcStockInfo info, stockinfolist) {
		if (IsFavouriteExists(info)) {
			continue;	//the stock already exists, ignore it
		}
		mStockInfoList.append(info);
		pStockInfoList.append(info);
	}
	emit OnStocksModified();
	return true;
}

bool tcFavouriteGroup::ModifyFavourite(QWidget *pParent, int pFavouriteIndex, tcStockInfo &pStockInfo)
{
	//TODO: implement this
	emit OnStocksModified();
	return false;
}

bool tcFavouriteGroup::RemoveFavourite(QWidget *pParent, int pFavouriteIndex)
{
	if (pFavouriteIndex < 0 || pFavouriteIndex >= mStockInfoList.count()) {
		tcLogService::CreateLog(this, "Wrong favourite index.");
		return false;
	}
	mStockInfoList.removeAt(pFavouriteIndex);
	emit OnStocksModified();
	return true;
}

bool tcFavouriteGroup::IsFavouriteExists(const tcStockInfo &pStockInfo)
{
	foreach (tcStockInfo stockinfo, mStockInfoList) {
		if (stockinfo == pStockInfo) {
			return true;
		}
	}
	return false;
}

bool tcFavouriteGroup::GetStockInfoList(tcStockInfoList &pStockInfoList)
{
	pStockInfoList = mStockInfoList;
	return true;
}

bool tcFavouriteGroup::GetStockInfoListFilter(tcStockInfoList &pStockInfoList, const QString &pStockCodeFilter, const QString &pStockNameFilter)
{
	foreach (tcStockInfo stockinfo, mStockInfoList) {
		if (pStockCodeFilter.length() > 0 && stockinfo.GetStockCode().indexOf(pStockCodeFilter) < 0) {
			continue;
		}
		if (pStockNameFilter.length() > 0 && stockinfo->GetStockName().indexOf(pStockNameFilter) < 0) {
			continue;
		}
		pStockInfoList.append(stockinfo);
	}
	return true;
}

QString tcFavouriteGroup::GetName()
{
	return mName;
}

void tcFavouriteGroup::SetName(const QString &pValue)
{
	mName = pValue;
}

QString tcFavouriteGroup::GetDescription()
{
	return mDescription;
}

void tcFavouriteGroup::SetDescription(const QString &pValue)
{
	mDescription = pValue;
}
