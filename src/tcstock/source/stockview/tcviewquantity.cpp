#include "tcviewquantity.h"

#include <QPainter>

#include "tcstockviewdef.h"

tcViewQuantity::tcViewQuantity(QObject *pParent, tcViewModelStockData *pStockData)
	: QObject(pParent)
{
	mHeight = pStockData->Quantity;
	if (pStockData->OpenPrice < pStockData->ClosePrice) {
		mIsFill = false;
	}
	else {
		mIsFill = true;
	}

    setToolTip(pStockData->Tooltip);
}

QRectF tcViewQuantity::boundingRect() const
{
	return QRectF(0, 0, QUANTITY_WIDTH, mHeight);
}

void tcViewQuantity::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
	QRectF rect(0, 0, QUANTITY_WIDTH, mHeight);
	pPainter->setPen(QUANTITY_LINE_COLOR);
	QBrush brush;
	if (! mIsFill) {
		brush.setColor(BACKGROUND_COLOR);
	}
	else {
		brush.setColor(QUANTITY_FILL_COLOR);
	}
	brush.setStyle(Qt::Dense4Pattern);
	pPainter->setBrush(brush);
	pPainter->drawRect(rect);
}
