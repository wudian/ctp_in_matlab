#ifndef tcviewmodel_h

#define tcviewmodel_h

#include <QtCore/QVariant>
#include <QtCore/QObject>

class tcStockInfo;

typedef struct {
	long OpenPrice;
	long ClosePrice;
	long MaxPrice;
	long MinPrice;
	long TotalPrice;
	long Quantity;
	QString Tooltip;
} tcViewModelStockData;

/*! \brief tcViewModel
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.09
 	
	通用股票K线显示模型，日K线，周K线等显示模型都由该类派生。
	负责K线图显示的具体大小尺寸，以及显示数据内容。
*/
class tcViewModel : public QObject
{
	Q_OBJECT

public:
	typedef enum tcViewMode {SmallView, LargeView};

	tcViewModel(QObject *pParent, tcViewMode pViewMode);

	~tcViewModel();

	qreal GetViewItemCount();

	qreal GetViewItemWidth();

	qreal GetViewHeight();

	qreal GetViewEntityOffset();

	qreal GetViewEntityHeight();

	qreal GetViewQuantityHeight();

	virtual QString GetViewItemText(int pIndex) = 0;

	virtual tcViewModelStockData* GetViewItemData(int pIndex, const tcStockInfo &pStockInfo) = 0;

	virtual bool IsCurrentItem(int pIndex) = 0;

protected:
	void ResetData();

	tcViewMode mViewMode;

	tcViewModelStockData mStockData;

};

#endif //tcviewmodel_h
