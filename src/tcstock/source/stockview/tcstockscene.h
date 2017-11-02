#ifndef tcstockscene_h

#define tcstockscene_h

#include <QtCore/QVariant>
#include <QGraphicsScene>
#include <QPainter>

#include "../stockinfo/tcstockinfopack.h"
#include "../viewmodel/tcviewmodelpack.h"
class tcViewStockGroup;

/*! \brief tcStockScene
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	显示股票K线图的场景（scene）类，与 tcStockView 配合一同显示各类K线图。

	与其它K线图显示相关类的关系图：
	tcStockScene -> tcViewStockGroup -> tcViewEntityGroup -> tcViewEntity
	                                                      -> QGraphicsTextItem
                                                          -> QGraphicsLineItem
                                     -> tcViewQuantityGroup -> tcViewQuantity
                                                            -> QGraphicsTextItem
*/
class tcStockScene : public QGraphicsScene
{
	Q_OBJECT

public:
	tcStockScene(QObject *pParent);

	~tcStockScene();

	void SetViewModel(tcViewModel *pViewModel);

	bool LoadStockInfoList(tcStockInfoList *pStockInfoList);

	bool ReloadStockInfoList();

	void ClearAll();

protected:
	void drawBackground(QPainter *pPainter, const QRectF &pRect);

private:
	tcViewModel *mViewModel;

	tcStockInfoList mViewStockInfoList;

	QList<tcViewStockGroup*> mViewStockGroupList;
	
};

#endif //tcstockscene_h
