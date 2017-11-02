#include "tcfavtinfomdl.h"

#include <QTableWidgetItem>

#include "../service/tcsvcpack.h"
#include "tcfavtmgr.h"
#include "tcfavtgrp.h"

tcFavouriteInfoModel::tcFavouriteInfoModel(QObject *pParent)
	: QStandardItemModel(0, 3, pParent)
{
	setHeaderData(0, Qt::Horizontal, tr("Stock Code"));
	setHeaderData(1, Qt::Horizontal, tr("Stock Name"));
	setHeaderData(2, Qt::Horizontal, tr("Level"));
}

void tcFavouriteInfoModel::LoadFavouriteInfoList(int pFavouriteGroupIndex)
{
	setRowCount(0);

	tcFavouriteManager *favouritemanager = tcObjService::GetFavouriteManager();
	tcFavouriteGroup *group = favouritemanager->GetFavouriteGroup(pFavouriteGroupIndex);
	if (group == NULL) {
		tcLogService::CreateLog(this, "Error when get favourite group.");
		return;
	}
	tcStockInfoList stockinfolist;
	if (! group->GetStockInfoList(stockinfolist)) {
		tcLogService::CreateLog(this, "Error when get stock info list.");
		return;
	}
	foreach (tcStockInfo stockinfo, stockinfolist) {
		int row = rowCount();
		insertRow(row);
		setItem(row, 0, new QStandardItem(stockinfo.GetStockCode()));
		setItem(row, 1, new QStandardItem(stockinfo->GetStockName()));
		setItem(row, 2, new QStandardItem("*****"));
	}
}

bool tcFavouriteInfoModel::AppendFavouriteInfo(QWidget *pParent, int pFavouriteGroupIndex)
{
	tcFavouriteManager *favouritemanager = tcObjService::GetFavouriteManager();
	tcFavouriteGroup *group = favouritemanager->GetFavouriteGroup(pFavouriteGroupIndex);
	if (group == NULL) {
		tcLogService::CreateLog(this, "Error when get favourite group.");
		return false;
	}
	tcStockInfoList stockinfolist;
	if (! group->AppendFavourite(pParent, stockinfolist)) {
		return false;
	}
	foreach (tcStockInfo stockinfo, stockinfolist) {
		int row = this->rowCount();
		this->insertRow(row);
		this->setItem(row, 0, new QStandardItem(stockinfo.GetStockCode()));
		this->setItem(row, 1, new QStandardItem(stockinfo->GetStockName()));
		this->setItem(row, 2, new QStandardItem("*****"));
	}
	return true;
}

bool tcFavouriteInfoModel::RemoveFavouriteInfo(QWidget *pParent, int pFavouriteGroupIndex, int pIndex)
{
	tcFavouriteManager *favouritemanager = tcObjService::GetFavouriteManager();
	tcFavouriteGroup *group = favouritemanager->GetFavouriteGroup(pFavouriteGroupIndex);
	if (group == NULL) {
		tcLogService::CreateLog(this, "Error when get favourite group.");
		return false;
	}
	if (! group->RemoveFavourite(pParent, pIndex)) {
		tcLogService::CreateLog(this, "Error when remove favourite stock.");
		return false;
	}
	this->removeRow(pIndex);
	return true;
}

