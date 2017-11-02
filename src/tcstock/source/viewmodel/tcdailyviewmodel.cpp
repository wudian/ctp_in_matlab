#include "tcdailyviewmodel.h"

#include <QtCore/QDate>

#include "../stockinfo/tcstockinfopack.h"

tcDailyViewModel::tcDailyViewModel(QObject *pParent, tcViewMode pViewMode)
	: tcViewModel(pParent, pViewMode)
{
}

tcDailyViewModel::~tcDailyViewModel()
{
}

QString tcDailyViewModel::GetViewItemText(int pIndex)
{
	if (pIndex % 3 == 0) {
		return GetViewItemDate(pIndex).toString("MM/dd");
	}
	return "";
}

tcViewModelStockData* tcDailyViewModel::GetViewItemData(int pIndex, const tcStockInfo &pStockInfo)
{
	QDate date = GetViewItemDate(pIndex);
	const tcStockDailyData *data = pStockInfo->ReadData(date);
	Q_ASSERT(data);
	mStockData.OpenPrice = data->OpenPrice;
	mStockData.ClosePrice = data->ClosePrice;
	mStockData.MaxPrice = data->MaxPrice;
	mStockData.MinPrice = data->MinPrice;
	mStockData.TotalPrice = data->TotalPrice;
	mStockData.Quantity = data->Quantity;
	QString floatstr;
	mStockData.Tooltip = date.toString("MM/dd dddd") + "\n";
	floatstr.setNum(qreal(mStockData.OpenPrice) / 100.0, 'F', 2);
	mStockData.Tooltip += tr("OpenPrice : %1\n").arg(floatstr);
	floatstr.setNum(qreal(mStockData.ClosePrice) / 100.0, 'F', 2);
	mStockData.Tooltip += tr("ClosePrice : %1\n").arg(floatstr);
	floatstr.setNum(qreal(mStockData.MaxPrice) / 100.0, 'F', 2);
	mStockData.Tooltip += tr("MaxPrice : %1\n").arg(floatstr);
	floatstr.setNum(qreal(mStockData.MinPrice) / 100.0, 'F', 2);
	mStockData.Tooltip += tr("MinPrice : %1\n").arg(floatstr);
	floatstr.setNum(mStockData.TotalPrice);
	mStockData.Tooltip += tr("TotalPrice : %1\n").arg(floatstr);
	floatstr.setNum(mStockData.Quantity);
	mStockData.Tooltip += tr("Quantity : %1").arg(floatstr);
	return &mStockData;
}

bool tcDailyViewModel::IsCurrentItem(int pIndex)
{
	if (pIndex == GetViewItemCount() - 1) {
		return true;
	}
	return false;
}

QDate tcDailyViewModel::GetViewItemDate(int pIndex)
{
	QDate date = QDate::currentDate();
	return date.addDays(-1 * GetViewItemCount() + pIndex + 1);
}
