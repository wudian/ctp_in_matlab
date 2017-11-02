#include "tcmonthlyviewmodel.h"

#include <QtCore/QDate>

#include "../stockinfo/tcstockinfopack.h"
#include "../service/tcsvcpack.h"

tcMonthlyViewModel::tcMonthlyViewModel(QObject *pParent, tcViewMode pViewMode)
	: tcWeeklyViewModel(pParent, pViewMode)
{
}

tcMonthlyViewModel::~tcMonthlyViewModel()
{
}

QString tcMonthlyViewModel::GetViewItemText(int pIndex)
{
	if (pIndex %3 == 2) {
		return GetViewItemStartDate(pIndex).toString("MM/dd");
	}
	return "";
}

tcViewModelStockData* tcMonthlyViewModel::GetViewItemData(int pIndex, const tcStockInfo &pStockInfo)
{
	QDate date = GetViewItemStartDate(pIndex);
	ResetData();

	tcStockDailyData data;
	if (! pStockInfo->ReadData(date, date.daysInMonth(), &data)) {
		tcLogService::CreateLog(this, "Error when read stock data.");
		return &mStockData;
	}
	mStockData.OpenPrice = data.OpenPrice;
	mStockData.ClosePrice = data.ClosePrice;
	mStockData.MaxPrice = data.MaxPrice;
	mStockData.MinPrice = data.MinPrice;
	mStockData.TotalPrice = data.TotalPrice;
	mStockData.Quantity = data.Quantity;

	QString floatstr;
	mStockData.Tooltip = "****\n";
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

bool tcMonthlyViewModel::IsCurrentItem(int pIndex)
{
	if (pIndex == GetViewItemCount() - 1) {
		return true;
	}
	return false;
}

QDate tcMonthlyViewModel::GetViewItemStartDate(int pIndex)
{
	QDate date = QDate::currentDate();
	date.setDate(date.year(), date.month(), 1);
	date = date.addMonths(-1*(GetViewItemCount() - pIndex - 1));
	return date;
}
