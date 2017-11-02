#ifndef tcstockdatainfodlg_h

#define tcstockdatainfodlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_stockdatainfodlg.h"

#include "tcmarket.h"
#include "tcstockdataitemmdl.h"
#include "tcstockdataitemdlt.h"

/*! \brief tcStockDataInfoDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	股票日数据显示和录入对话框。
	使用 tcStockDataItemDelegate 和 tcStockDataItemModel 类来实现数据的录入功能。s
*/
class tcStockDataInfoDialog : public QDialog, private Ui_tcStockDataInfoDialog
{
	Q_OBJECT

public:
	tcStockDataInfoDialog(QWidget *pParent);

protected:

protected slots:
	void DoDateChanged(const QDate &pDate);

	void DoGroupChanged(int pIndex);

	void DoFilterTextChanged(const QString &pText);

private:
	tcStockDataItemModel *mDataModel;

	tcStockDataItemDelegate *mDataDelegate;
};

#endif //tcstockdatainfodlg_h

