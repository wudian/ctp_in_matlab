#ifndef tcfxjfileimptsourcedlg_h

#define tcfxjfileimptsourcedlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_fxjfileimptsourcedlg.h"

#include "tcfxjfileimptsource.h"

/*! \brief tcFxjFileImportSourceDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.22
*/
class tcFxjFileImportSourceDialog : public QDialog, private Ui_tcFxjFileImportSourceDialog
{
	Q_OBJECT

public:
	tcFxjFileImportSourceDialog(QWidget *pParent);

	~tcFxjFileImportSourceDialog();

	bool SetSettings(const tcFxjFileImportSourceOption &pOption);

	bool GetSettings(tcFxjFileImportSourceOption &pOption);

protected slots:
	void DoSelectDadFilePath();

};

#endif //tcfxjfileimptsourcedlg_h
