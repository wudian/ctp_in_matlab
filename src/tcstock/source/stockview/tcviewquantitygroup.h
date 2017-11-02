#ifndef tcviewquantitygroup_h

#define tcviewquantitygroup_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QGraphicsItemGroup>

#include "tcviewquantity.h"
#include "../viewmodel/tcviewmodelpack.h"

/*! \brief tcViewQuantityGroup
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.04
 	
	成交量组，包含成交量矩形以及显示文字等。
*/
class tcViewQuantityGroup : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT

public:
	tcViewQuantityGroup(QObject *pParent, tcViewModelStockData *pStockData);

	void SetPosAndScale(qreal pXPos, qreal pYScale);

private:
	tcViewQuantity *mViewQuantity;

	QGraphicsTextItem *mQuantityText;

};

#endif //tcviewquantitygroup_h

