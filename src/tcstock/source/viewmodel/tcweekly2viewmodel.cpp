#include "tcweekly2viewmodel.h"

#include <QtCore/QDate>

#include "../stockinfo/tcstockinfopack.h"
#include "../service/tcsvcpack.h"

tcWeekly2ViewModel::tcWeekly2ViewModel(QObject *pParent, tcViewMode pViewMode)
	: tcWeeklyViewModel(pParent, pViewMode)
{
}

tcWeekly2ViewModel::~tcWeekly2ViewModel()
{
}

QString tcWeekly2ViewModel::GetViewItemText(int pIndex)
{
	if (pIndex %3 == 2) {
		return GetViewItemStartDate(pIndex).toString("MM/dd");
	}
	return "";
}

tcViewModelStockData* tcWeekly2ViewModel::GetViewItemData(int pIndex, const tcStockInfo &pStockInfo)
{
	QDate date = GetViewItemStartDate(pIndex);
	ResetData();

	tcStockDailyData data;
	if (! pStockInfo->ReadData(date, 14, &data)) {
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
	mStockData.Tooltip = date.addDays(-14).toString("MM/dd dddd") + " - " + date.addDays(-3).toString("MM/dd dddd") + "\n";
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

bool tcWeekly2ViewModel::IsCurrentItem(int pIndex)
{
	if (pIndex == GetViewItemCount() - 1) {
		return true;
	}
	return false;
}

QDate tcWeekly2ViewModel::GetViewItemStartDate(int pIndex)
{
	QDate date = QDate::currentDate();
	date = date.addDays(-1 * date.dayOfWeek() + 1);
	date = date.addDays(-14 * (GetViewItemCount() - pIndex - 1));
	return date;
}
