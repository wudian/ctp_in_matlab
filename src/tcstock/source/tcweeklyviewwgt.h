#ifndef tcweeklyviewwgt_h

#define tcweeklyviewwgt_h

#include <QtCore/QVariant>
#include <QWidget>

#include "stockinfo/tcstockinfopack.h"
#include "viewmodel/tcviewmodelpack.h"
#include "stockview/tcstockviewpack.h"

/*! \brief tcWeeklyViewWidget
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.28
 	
	主界面下方的周K线视图面板。
*/
class tcWeeklyViewWidget : public QWidget
{
	Q_OBJECT

public:
	tcWeeklyViewWidget(QWidget *pParent);

	void LoadStockInfoList(tcStockInfoList *pStockInfoList);

	void SetViewMode(int pModeIndex);

protected slots:
	void DoViewModeChanged(int pIndex);

private:
	tcViewModel *mWeeklyViewModel;

	tcStockScene *mWeeklyViewScene;

	tcStockView *mWeeklyView;

};

#endif //tcweeklyviewwgt_h
