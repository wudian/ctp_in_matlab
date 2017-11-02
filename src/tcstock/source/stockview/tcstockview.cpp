#include "tcstockview.h"

#include "tcstockviewdef.h"

tcStockView::tcStockView(QWidget *pParent, tcStockScene *pScene)
	: QGraphicsView(pScene, pParent)
{
	this->setAlignment(Qt::AlignBottom | Qt::AlignRight);
	this->setCacheMode(QGraphicsView::CacheBackground);
	//this->setDragMode(QGraphicsView::ScrollHandDrag);
	setBackgroundRole(QPalette::Window);

	ResetViewport();
}

tcStockView::~tcStockView()
{
}

void tcStockView::ResetViewport()
{
	QRectF scenerect = sceneRect();
	this->centerOn(scenerect.right(), scenerect.bottom());
}

