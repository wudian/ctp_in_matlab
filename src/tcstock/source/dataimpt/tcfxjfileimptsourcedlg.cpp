#include "tcfxjfileimptsourcedlg.h"

#include <QFileDialog>

tcFxjFileImportSourceDialog::tcFxjFileImportSourceDialog(QWidget *pParent)
	: QDialog(pParent)
{
	setupUi(this);
	connect(btn1, SIGNAL(clicked()), this, SLOT(DoSelectDadFilePath()));
}

tcFxjFileImportSourceDialog::~tcFxjFileImportSourceDialog()
{
}

bool tcFxjFileImportSourceDialog::SetSettings(const tcFxjFileImportSourceOption &pOption)
{
	if (pOption.DownloadZipFile) {
		rdo1->setChecked(true);
	}
	else {
		rdo2->setChecked(true);
	}
	edt1->setText(pOption.ZipFileUrl);
	edt2->setText(pOption.DataFilePath);
	return true;
}

bool tcFxjFileImportSourceDialog::GetSettings(tcFxjFileImportSourceOption &pOption)
{
	pOption.DownloadZipFile = rdo1->isChecked();
	pOption.ZipFileUrl = edt1->text();
	pOption.DataFilePath = edt2->text();
	return true;
}

void tcFxjFileImportSourceDialog::DoSelectDadFilePath()
{
	QString path = QFileDialog::getExistingDirectory(this);
	if (! path.isEmpty()) {
		edt2->setText(path);
	}
}

