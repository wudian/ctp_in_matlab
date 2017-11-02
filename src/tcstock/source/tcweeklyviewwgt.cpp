#include "tcweeklyviewwgt.h"

#include <QVBoxLayout>
#include <QTabBar>

tcWeeklyViewWidget::tcWeeklyViewWidget(QWidget *pParent)
	: QWidget(pParent)
{
	QVBoxLayout *vboxLayout;
    vboxLayout = new QVBoxLayout(this);

	mWeeklyViewModel = NULL;
	mWeeklyViewScene = new tcStockScene(this);
	mWeeklyView = new tcStockView(this, mWeeklyViewScene);
	vboxLayout->addWidget(mWeeklyView);

	QTabBar *tabbar = new QTabBar(this);
	tabbar->setShape(QTabBar::TriangularSouth);
	tabbar->addTab(tr("Weekly View"));
	tabbar->addTab(tr("Double Week View"));
	tabbar->addTab(tr("Monthly View"));
	tabbar->addTab(tr("Nothing View"));
	vboxLayout->addWidget(tabbar);
	connect(tabbar, SIGNAL(currentChanged(int)), this, SLOT(DoViewModeChanged(int)));

	SetViewMode(0);
}

void tcWeeklyViewWidget::LoadStockInfoList(tcStockInfoList *pStockInfoList)
{
	mWeeklyViewScene->LoadStockInfoList(pStockInfoList);
}

void tcWeeklyViewWidget::SetViewMode(int pModeIndex)
{
	if (mWeeklyViewModel != NULL) {
		delete mWeeklyViewModel;
	}
	switch (pModeIndex) {
	case 0: 
		mWeeklyViewModel = new tcWeeklyViewModel(this, tcViewModel::SmallView);
		break;
	case 1: 
		mWeeklyViewModel = new tcWeekly2ViewModel(this, tcViewModel::SmallView);
		break;
	case 2:
		mWeeklyViewModel = new tcMonthlyViewModel(this, tcViewModel::SmallView);
		break;
	default:
		mWeeklyViewModel = NULL;
	}
	mWeeklyViewScene->SetViewModel(mWeeklyViewModel);
	mWeeklyView->ResetViewport();
}

void tcWeeklyViewWidget::DoViewModeChanged(int pIndex)
{
	SetViewMode(pIndex);
}
