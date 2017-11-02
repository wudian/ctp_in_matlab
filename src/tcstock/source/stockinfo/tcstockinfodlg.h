#ifndef tcstockinfodlg_h

#define tcstockinfodlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_stockinfodlg.h"

#include "tcstock.h"

/*! \brief tcStockInfoDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.04
 	
	显示或编辑 tcStock 信息的对话框。
*/
class tcStockInfoDialog : public QDialog, private Ui_tcStockInfoDialog
{
	Q_OBJECT

public:
	tcStockInfoDialog(QWidget *pParent, bool pAppendMode);

	bool LoadFromStock(tcStock *pStock);

	bool SaveToStock(tcStock *pStock);

protected slots:
	void DoOk();

private:
	bool mAppendMode;

};

#endif //tcstockinfodlg_h

