#include "tcdailyviewwgt.h"

#include <QVBoxLayout>

tcDailyViewWidget::tcDailyViewWidget(QWidget *pParent)
	: QWidget(pParent)
{
	QVBoxLayout *vboxLayout;
    vboxLayout = new QVBoxLayout(this);

	mDailyViewModel = new tcDailyViewModel(this, tcViewModel::LargeView);
	mDailyViewScene = new tcStockScene(this);
	mDailyViewScene->SetViewModel(mDailyViewModel);
	mDailyView = new tcStockView(this, mDailyViewScene);
	mDailyView->ResetViewport();
	vboxLayout->addWidget(mDailyView);
}

void tcDailyViewWidget::LoadStockInfoList(tcStockInfoList *pStockInfoList)
{
	mDailyViewScene->LoadStockInfoList(pStockInfoList);
}


