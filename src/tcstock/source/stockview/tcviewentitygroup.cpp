#include "tcviewentitygroup.h"

#include <QPen>
#include <QFont>

#include "tcstockviewdef.h"

tcViewEntityGroup::tcViewEntityGroup(QObject *pParent, tcViewModelStockData *pStockData)
	: QObject(pParent)
{
	//create the entity
	mViewEntity = new tcViewEntity(this, pStockData);
	mViewEntity->setPos(-1 * ENTITY_WIDTH / 2, 0);
	this->addToGroup(mViewEntity);

	//create entity line
	mEntityLine = new QGraphicsLineItem(this);
	QPen pen;
	pen.setColor(ENTITY_LINE_COLOR);
	mEntityLine->setPen(pen);
	mEntityLine->setLine(0, pStockData->MinPrice, 0, pStockData->MaxPrice);
	this->addToGroup(mEntityLine);

	QString floatstr;
	QFont font;
	font.setPixelSize(10);

	//create open price text
	mOpenPriceText = new QGraphicsTextItem(this);
	mOpenPriceText->setFont(font);
	if (pStockData->OpenPrice != 0) {
		floatstr.setNum(qreal(pStockData->OpenPrice) / 100.0, 'F', 2);
		mOpenPriceText->setPlainText(floatstr);
	}
	this->addToGroup(mOpenPriceText);

	//create close price text
	mClosePriceText = new QGraphicsTextItem(this);
	mClosePriceText->setFont(font);
	if (pStockData->ClosePrice != 0) {
		floatstr.setNum(qreal(pStockData->ClosePrice) / 100.0, 'F', 2);
		mClosePriceText->setPlainText(floatstr);
	}
	this->addToGroup(mClosePriceText);

	//create the max price text
	mMaxPriceText = new QGraphicsTextItem(this);
	mMaxPriceText->setFont(font);
	if (pStockData->MaxPrice != 0 && pStockData->MaxPrice != pStockData->OpenPrice && pStockData->MaxPrice != pStockData->ClosePrice) {
		floatstr.setNum(qreal(pStockData->MaxPrice) / 100.0, 'F', 2);
		mMaxPriceText->setPlainText(floatstr);
	}
	this->addToGroup(mMaxPriceText);

	//create the min price text
	mMinPriceText = new QGraphicsTextItem(this);
	mMinPriceText->setFont(font);
	if (pStockData->MinPrice != 0 && pStockData->MinPrice != pStockData->OpenPrice && pStockData->MinPrice != pStockData->ClosePrice) {
		floatstr.setNum(qreal(pStockData->MinPrice) / 100.0, 'F', 2);
		mMinPriceText->setPlainText(floatstr);
	}
	this->addToGroup(mMinPriceText);
}

void tcViewEntityGroup::SetPosAndScale(qreal pXPos, qreal pYPos, qreal pYScale)
{
	/*mViewEntity->scale(1, -pYScale);
	mEntityLine->scale(1, -pYScale);*/
	QRectF rect1, rect2;
	rect1 = mViewEntity->sceneBoundingRect();
	if (mViewEntity->IsReverse()) {
		mOpenPriceText->setPos(0, rect1.top() - 15);
		mClosePriceText->setPos(0, rect1.bottom());
	}
	else {
		mOpenPriceText->setPos(0, rect1.bottom());
		mClosePriceText->setPos(0, rect1.top() - 15);
	}
	rect2 = mEntityLine->sceneBoundingRect();
	if (rect2.top() - rect1.top() > -10) {
		rect2.setTop(rect1.top() - 10);
	}
	if (rect2.bottom() - rect1.bottom() < 10) {
		rect2.setBottom(rect1.bottom() + 10);
	}
	mMaxPriceText->setPos(0, rect2.top() - 15);
	mMinPriceText->setPos(0, rect2.bottom());
	this->setPos(pXPos, pYPos);
}
