#ifndef tcimptprogressdlg_h

#define tcimptprogressdlg_h

#include <QtCore/QVariant>
#include <QDialog>
#include "ui_ui_imptprogressdlg.h"

#include "tcimptsource.h"

/*! \brief tcImportProgressDialog
 	\author tony (tonixinot@gmail.com)
 	\version 0.02
 	\date 2007.03.19
*/
class tcImportProgressDialog : public QDialog, private Ui_tcImportProgressDialog
{
	Q_OBJECT

public:
	tcImportProgressDialog(QWidget *pParent, tcImportSource *pImportSource);

	~tcImportProgressDialog();

protected:
	virtual void closeEvent(QCloseEvent *pEvent);

protected slots:
	void DoUpdateProgress(int pProgress);

	void DoAppendMessage(const QString &pMessage, bool pSuccess);

	void DoImportFinished();

	void DoCancelImport();

private:
	tcImportSource *mImportSource;

};

#endif //tcimptprogressdlg_h
