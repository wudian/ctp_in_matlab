#ifndef tcweeklyviewmodel_h

#define tcweeklyviewmodel_h

#include <QtCore/QVariant>
#include <QtCore/QObject>

#include "tcviewmodel.h"

/*! \brief tcWeeklyViewModel
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.09

 	周K线显示模型。
*/
class tcWeeklyViewModel : public tcViewModel
{
	Q_OBJECT

public:
	tcWeeklyViewModel(QObject *pParent, tcViewMode pViewMode);

	~tcWeeklyViewModel();

	virtual QString GetViewItemText(int pIndex);

	virtual tcViewModelStockData* GetViewItemData(int pIndex, const tcStockInfo &pStockInfo);

	virtual bool IsCurrentItem(int pIndex);

protected:
	QDate GetViewItemStartDate(int pIndex);

};

#endif //tcweeklyviewmodel_h

