#ifndef tcmonthlyviewmodel_h

#define tcmonthlyviewmodel_h

#include <QtCore/QVariant>
#include <QtCore/QObject>

#include "tcviewmodel.h"
#include "tcweeklyviewmodel.h"

/*! \brief tcMonthlyViewModel
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.28

 	月K线显示模型。
*/
class tcMonthlyViewModel : public tcWeeklyViewModel
{
	Q_OBJECT

public:
	tcMonthlyViewModel(QObject *pParent, tcViewMode pViewMode);

	~tcMonthlyViewModel();

	virtual QString GetViewItemText(int pIndex);

	virtual tcViewModelStockData* GetViewItemData(int pIndex, const tcStockInfo &pStockInfo);

	virtual bool IsCurrentItem(int pIndex);

protected:
	QDate GetViewItemStartDate(int pIndex);

};

#endif //tcmonthlyviewmodel_h
