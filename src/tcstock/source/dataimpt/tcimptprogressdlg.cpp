#include "tcimptprogressdlg.h"

#include <QPushButton>
#include <QCloseEvent>

tcImportProgressDialog::tcImportProgressDialog(QWidget *pParent, tcImportSource *pImportSource)
	: QDialog(pParent)
{
	mImportSource = pImportSource;

	setupUi(this);
	this->setWindowModality(Qt::WindowModal);
	QPushButton *closebutton = buttonBox->button(QDialogButtonBox::Close);
	closebutton->setEnabled(false);
	connect(mImportSource, SIGNAL(OnUpdateProgress(int)), this, SLOT(DoUpdateProgress(int)));
	connect(mImportSource, SIGNAL(OnAppendMessage(const QString &, bool)), this, SLOT(DoAppendMessage(const QString &, bool)));
	connect(mImportSource, SIGNAL(OnImportFinished()), this, SLOT(DoImportFinished()));
	disconnect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(DoCancelImport()));
}

tcImportProgressDialog::~tcImportProgressDialog()
{
}

void tcImportProgressDialog::closeEvent(QCloseEvent *pEvent)
{
	if (mImportSource->IsImporting()) {
		pEvent->ignore();
	}
}

void tcImportProgressDialog::DoUpdateProgress(int pProgress)
{
	pgs1->setValue(pProgress);
}

void tcImportProgressDialog::DoAppendMessage(const QString &pMessage, bool pSuccess)
{
	if (pSuccess) {
		edt1->append("<font color=blue>" + pMessage + "</font>");
	}
	else {
		edt1->append("<font color=red>" + pMessage + "</font>");
	}
}

void tcImportProgressDialog::DoImportFinished()
{
	QPushButton *closebutton = buttonBox->button(QDialogButtonBox::Close);
	closebutton->setEnabled(true);
	QPushButton *abortbutton = buttonBox->button(QDialogButtonBox::Abort);
	abortbutton->setEnabled(false);
}

void tcImportProgressDialog::DoCancelImport()
{
	mImportSource->CancelImport();
}

