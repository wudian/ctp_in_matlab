#ifndef tcstockselectdlg_h

#define tcstockselectdlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_stockselectdlg.h"

#include "tcstockinfo.h"
#include "tcstockinfolst.h"

/*! \brief tcStockSelectDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.26
 	
	显示股票列表，供用户从中选择单个或多个股票，选中的股票以 tcStockInfoList 形式返回。
*/
class tcStockSelectDialog : public QDialog , private Ui_tcStockSelectDialog
{
	Q_OBJECT

public:
	tcStockSelectDialog(QWidget *pParent);

	bool GetSelectedStockInfoList(tcStockInfoList &pStockInfoList);

protected:
	void LoadMarketList();

	void LoadStockList();

protected slots:
	void DoMarketIndexChanged(int pIndex);

	void DoFilterTextChanged(const QString &pText);

	void DoOk();

	void DoStockListNeedReload();

private:
	tcStockInfoList mViewStockInfoList;

};

#endif //tcstockselectdlg_h
