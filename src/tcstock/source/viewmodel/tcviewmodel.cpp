#include "tcviewmodel.h"

#include "../stockinfo/tcstockinfopack.h"

#define VIEW_COORDINATE_SPACE 50

tcViewModel::tcViewModel(QObject *pParent, tcViewMode pViewMode)
	: QObject(pParent)
{
	mViewMode = pViewMode;
}

tcViewModel::~tcViewModel()
{
}

qreal tcViewModel::GetViewItemCount()
{
	if (mViewMode == LargeView) {
		return 100.0;
	}
	else {
		return 60.0;
	}
}

qreal tcViewModel::GetViewItemWidth()
{
	return 20.0;
}

qreal tcViewModel::GetViewHeight()
{
	if (mViewMode == LargeView) {
		return 500.0;
	}
	else {
		return 200.0;
	}
}

qreal tcViewModel::GetViewEntityOffset()
{
	if (mViewMode == LargeView) {
		return 150.0;
	}
	else {
		return 80.0;
	}
}

qreal tcViewModel::GetViewEntityHeight()
{
	if (mViewMode == LargeView) {
		return 300.0;
	}
	else {
		return 100.0;
	}
}

qreal tcViewModel::GetViewQuantityHeight()
{
	if (mViewMode == LargeView) {
		return 120.0;
	}
	else {
		return 60.0;
	}
}

void tcViewModel::ResetData()
{
	mStockData.OpenPrice = 0;
	mStockData.ClosePrice = 0;
	mStockData.MaxPrice = 0;
	mStockData.MinPrice = 0;
	mStockData.TotalPrice = 0;
	mStockData.Quantity = 0;
	mStockData.Tooltip = "";
}
