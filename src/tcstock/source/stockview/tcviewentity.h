#ifndef tcviewentity_h

#define tcviewentity_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QGraphicsItem>

#include "../viewmodel/tcviewmodelpack.h"

#define ENTITY_WIDTH 8

/*! \brief tcViewEntity
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.04
 	
	K线图中实体（entity）的显示，具体表现为一个空心或实心的矩形。
*/
class tcViewEntity : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	tcViewEntity(QObject *pParent, tcViewModelStockData *pStockData);

	bool IsReverse();

protected:
    QRectF boundingRect() const;

	void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget);

private:
	qreal mY1;

	qreal mY2;

	bool mIsReverse;

};

#endif //tcviewentity_h
