#ifndef tcviewstockgroup_h

#define tcviewstockgroup_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QGraphicsItemGroup>

#include "../stockinfo/tcstockinfopack.h"
#include "../viewmodel/tcviewmodelpack.h"

/*! \brief tcViewStockGroup
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.04
 	
	每日股票数据组，包含K线图形和成交量图形。
*/
class tcViewStockGroup : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT

public:
	tcViewStockGroup(QObject *pParent, const tcStockInfo pStockInfo, tcViewModel *pViewModel);

};

#endif //tcviewstockgroup_h
