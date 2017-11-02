#ifndef tcfavtgrpinfodlg_h

#define tcfavtgrpinfodlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_favouritegroupinfodlg.h"

#include "tcfavtgrp.h"

/*! \brief tcFavouriteGroupInfoDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.25
 	
	自选股票组编辑对话框。
*/
class tcFavouriteGroupInfoDialog : public QDialog, private Ui_tcFavouriteGroupInfoDialog
{
	Q_OBJECT

public:
	tcFavouriteGroupInfoDialog(QWidget *pParent);

	bool LoadFromFavouriteGroup(tcFavouriteGroup *pFavouriteGroup);

	bool SaveToFavouriteGroup(tcFavouriteGroup *pFavouriteGroup);

protected slots:
	void DoOk();

};

#endif //tcfavtgrpinfodlg_h
