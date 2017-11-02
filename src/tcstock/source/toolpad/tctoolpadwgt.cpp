#include "tctoolpadwgt.h"

#include "../service/tcsvcpack.h"
#include "../stockinfo/tcstockinfopack.h"

tcToolPadWidget::tcToolPadWidget(QWidget *pParent)
	: QWidget(pParent)
{
	setupUi(this);

	mStockListWidget = new tcStockListWidget(this);
	connect(mStockListWidget, SIGNAL(OnStockSelected(tcStockInfoList *)), this, SLOT(DoTabStockSelected(tcStockInfoList *)));
	vboxLayout1->setMargin(0);
	vboxLayout1->addWidget(mStockListWidget);
}

tcToolPadWidget::~tcToolPadWidget()
{

}

void tcToolPadWidget::DoTabStockSelected(tcStockInfoList *pStockInfoList)
{
	emit OnStockSelected(pStockInfoList);
}
