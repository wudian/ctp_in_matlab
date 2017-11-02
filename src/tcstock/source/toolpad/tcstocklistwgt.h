#ifndef tcstocklistwgt_h

#define tcstocklistwgt_h

#include <QtCore/QVariant>
#include <QWidget>
#include "ui_ui_stocklistwgt.h"

#include "../stockinfo/tcstockinfopack.h"

/*! \brief tcStockListWidget
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	所有股票列表面板。
*/
class tcStockListWidget : public QWidget, private Ui_tcStockListWidget
{
	Q_OBJECT

public:
	tcStockListWidget(QWidget *pParent);

	~tcStockListWidget();

protected:

protected slots:
	/*!
		notified by tcMarketManager
	*/
	void DoMarketModified();

	/*!
		notified by tcMarketManager
	*/
	void DoStockModified(tcMarket *pMarket);

	void DoEditFavourite();

	void DoMarketIndexChanged(int pIndex);

	void DoFilterTextChanged(const QString &pText);

	void DoStockSelectionChanged();

protected slots:
	/*!
		notified by tcStockInfoList when it's group may be changed.
	*/
	void DoGroupListNeedReload();

	/*!
		notified by tcStockInfoList when it's included stock may be changed.
	*/
	void DoStockListNeedReload();

private:
	tcStockInfoList mViewStockInfoList;

signals:
	void OnStockSelected(tcStockInfoList *pStockInfoList);

};

#endif //tcstocklistwgt_h

