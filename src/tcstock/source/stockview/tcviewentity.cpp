#include "tcviewentity.h"

#include <QPainter>
#include <QCursor>

#include "tcstockviewdef.h"

tcViewEntity::tcViewEntity(QObject *pParent, tcViewModelStockData *pStockData)
	: QObject(pParent)
{
	if (pStockData->OpenPrice < pStockData->ClosePrice) {
		mY1 = pStockData->ClosePrice;
		mY2 = pStockData->OpenPrice;
		mIsReverse = false;
	}
	else {
		mY1 = pStockData->OpenPrice;
		mY2 = pStockData->ClosePrice;
		mIsReverse = true;
	}

    setToolTip(pStockData->Tooltip);

	//setCursor(Qt::CrossCursor);
}

bool tcViewEntity::IsReverse()
{
	return mIsReverse;
}

QRectF tcViewEntity::boundingRect() const
{
	return QRectF(0, mY2, ENTITY_WIDTH, mY1-mY2);
}

void tcViewEntity::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
	pPainter->setPen(ENTITY_LINE_COLOR);
	QRectF rect = QRectF(0, mY2, ENTITY_WIDTH, mY1-mY2);
	if (! mIsReverse) {
		pPainter->setBrush(BACKGROUND_COLOR);
	}
	else {
		pPainter->setBrush(ENTITY_FILL_COLOR);
	}
	pPainter->drawRect(rect);
}
