#ifndef tcmarketselectdlg_h

#define tcmarketselectdlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_marketselectdlg.h"

#include "tcmarketmgr.h"

/*! \brief tcMarketSelectDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.03
 	
	股市选择窗口，由 tcMarketManager 类负责调用。
*/
class tcMarketSelectDialog : public QDialog, private Ui_tcMarketSelectDialog
{
	Q_OBJECT

public:
	tcMarketSelectDialog(QWidget *pParent);

	bool LoadMarketList(tcMarketManager *pMarketManager);

	int GetSelectedMarketIndex();

};

#endif //tcmarketselectdlg_h

