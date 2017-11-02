#ifndef tcweekly2viewmodel_h

#define tcweekly2viewmodel_h

#include <QtCore/QVariant>
#include <QtCore/QObject>

#include "tcviewmodel.h"
#include "tcweeklyviewmodel.h"

/*! \brief tcWeekly2ViewModel
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.10

 	双周K线显示模型。
*/
class tcWeekly2ViewModel : public tcWeeklyViewModel
{
	Q_OBJECT

public:
	tcWeekly2ViewModel(QObject *pParent, tcViewMode pViewMode);

	~tcWeekly2ViewModel();

	virtual QString GetViewItemText(int pIndex);

	virtual tcViewModelStockData* GetViewItemData(int pIndex, const tcStockInfo &pStockInfo);

	virtual bool IsCurrentItem(int pIndex);

protected:
	QDate GetViewItemStartDate(int pIndex);

};

#endif //tcweekly2viewmodel_h
