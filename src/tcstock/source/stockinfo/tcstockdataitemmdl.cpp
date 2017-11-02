#include "tcstockdataitemmdl.h"

#include <QTableWidgetItem>

#include "../service/tcsvcpack.h"
#include "../stockinfo/tcstockinfopack.h"

tcStockDataItemModel::tcStockDataItemModel(QObject *pParent)
	: QStandardItemModel(0, 8, pParent)
{
	setHeaderData(0, Qt::Horizontal, tr("Stock Code"));
	setHeaderData(1, Qt::Horizontal, tr("Name"));
	setHeaderData(2, Qt::Horizontal, tr("Open Price"));
	setHeaderData(3, Qt::Horizontal, tr("Close Price"));
	setHeaderData(4, Qt::Horizontal, tr("Max Price"));
	setHeaderData(5, Qt::Horizontal, tr("Min Price"));
	setHeaderData(6, Qt::Horizontal, tr("Total Price"));
	setHeaderData(7, Qt::Horizontal, tr("Quantity"));
}

bool tcStockDataItemModel::GetGroupList(QStringList &pStringList)
{
	return mViewStockInfoList.GetGroupList(pStringList);
}

void tcStockDataItemModel::CreateStockList(int pGroupIndex, const QString &pStockCodeFilter, const QString &pStockNameFilter)
{
	mViewStockInfoList.ReloadFromGroupFilter(pGroupIndex, pStockCodeFilter, pStockNameFilter);
	//show stock in the tableview
	setRowCount(0);
	foreach(tcStockInfo info, mViewStockInfoList) {
		int row = rowCount();
		insertRow(row);
		setItem(row, 0, new QStandardItem(info.GetStockCode()));
		setItem(row, 1, new QStandardItem(info->GetStockName()));
	}
}

void tcStockDataItemModel::LoadStockData(const QDate &pDate)
{
	//fill the data of stock
	mEditDate = pDate;
	int i=0;
	foreach(tcStockInfo info, mViewStockInfoList) {
		const tcStockDailyData *data = info->ReadData(pDate);
		if (! data) {
			continue;
		}
		QString floatstr;
		floatstr.setNum(qreal(data->OpenPrice) / 100.0, 'F', 2);
		setItem(i, 2, new QStandardItem(floatstr));
		floatstr.setNum(qreal(data->ClosePrice) / 100.0, 'F', 2);
		setItem(i, 3, new QStandardItem(floatstr));
		floatstr.setNum(qreal(data->MaxPrice) / 100.0, 'F', 2);
		setItem(i, 4, new QStandardItem(floatstr));
		floatstr.setNum(qreal(data->MinPrice) / 100.0, 'F', 2);
		setItem(i, 5, new QStandardItem(floatstr));
		floatstr.setNum(data->TotalPrice);
		setItem(i, 6, new QStandardItem(floatstr));
		floatstr.setNum(data->Quantity);
		setItem(i, 7, new QStandardItem(floatstr));
		i++;
	}
}

const tcStockDailyData* tcStockDataItemModel::ReadData(int pRow)
{
	if (pRow < 0 || pRow >= mViewStockInfoList.count()) {
		tcLogService::CreateLog(this, "Wrong index for read data.");
		return NULL;
	}
	tcStockInfo info = mViewStockInfoList[pRow];
	return info->ReadData(mEditDate);
}

bool tcStockDataItemModel::WriteData(int pRow, tcStockDailyData* pStockDailyData)
{
	if (pRow < 0 || pRow >= mViewStockInfoList.count()) {
		tcLogService::CreateLog(this, "Wrong index for write data.");
		return false;
	}
	tcStockInfo info = mViewStockInfoList[pRow];
	if (! info->WriteData(mEditDate, pStockDailyData)) {
		tcLogService::CreateLog(this, "Error when write data.");
		return false;
	}
	QString floatstr;
	floatstr.setNum(qreal(pStockDailyData->OpenPrice) / 100.0, 'F', 2);
	setItem(pRow, 2, new QStandardItem(floatstr));
	floatstr.setNum(qreal(pStockDailyData->ClosePrice) / 100.0, 'F', 2);
	setItem(pRow, 3, new QStandardItem(floatstr));
	floatstr.setNum(qreal(pStockDailyData->MaxPrice) / 100.0, 'F', 2);
	setItem(pRow, 4, new QStandardItem(floatstr));
	floatstr.setNum(qreal(pStockDailyData->MinPrice) / 100.0, 'F', 2);
	setItem(pRow, 5, new QStandardItem(floatstr));
	floatstr.setNum(pStockDailyData->TotalPrice);
	setItem(pRow, 6, new QStandardItem(floatstr));
	floatstr.setNum(pStockDailyData->Quantity);
	setItem(pRow, 7, new QStandardItem(floatstr));
	return true;
}
