#ifndef tcmarketinfodlg_h

#define tcmarketinfodlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_marketinfodlg.h"

#include "tcmarket.h"

/*! \brief tcMarketInfoDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	股市信息编辑界面，由 tcMarketManager 类负责调用。
*/
class tcMarketInfoDialog : public QDialog, private Ui_tcMarketInfoDialog
{
	Q_OBJECT

public:
	tcMarketInfoDialog(QWidget *pParent);

	bool LoadFromMarket(tcMarket *pMarket);

	bool SaveToMarket(tcMarket *pMarket);

protected slots:
	void DoOk();

};

#endif //tcmarketinfodlg_h

