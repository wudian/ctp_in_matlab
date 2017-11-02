#include "tcviewquantitygroup.h"

#include <QFont>

tcViewQuantityGroup::tcViewQuantityGroup(QObject *pParent, tcViewModelStockData *pStockData)
	: QObject(pParent)
{
	//create the quantity
	mViewQuantity = new tcViewQuantity(this, pStockData);
	mViewQuantity->setPos(-1 * QUANTITY_WIDTH / 2, 0);
	this->addToGroup(mViewQuantity);

	QString floatstr;
	QFont font;
	font.setPixelSize(10);

	//create the quantity text
	mQuantityText = new QGraphicsTextItem(this);
	mQuantityText->setFont(font);
	if (pStockData->Quantity != 0) {
		QString quantitystr;
		quantitystr.setNum(pStockData->Quantity);
		mQuantityText->setPlainText(quantitystr);
	}
	this->addToGroup(mQuantityText);
}

void tcViewQuantityGroup::SetPosAndScale(qreal pXPos, qreal pYScale)
{
	//mViewQuantity->scale(1, -1 * pYScale);
	mQuantityText->setPos(-1 * QUANTITY_WIDTH / 2, mViewQuantity->sceneBoundingRect().top() - 15);
	this->setPos(pXPos, 0);
}
