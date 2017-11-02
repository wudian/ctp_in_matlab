#include "tcimptsource.h"

tcImportSource::tcImportSource()
{
}

tcImportSource::~tcImportSource()
{
}

QString tcImportSource::GetDescription()
{
	return "";
}

bool tcImportSource::HaveSettingDialog()
{
	return false;
}

void tcImportSource::ShowSettingDialog(QWidget *pParent)
{
}

bool tcImportSource::Import()
{
	mIsImporting = true;
	bool result = ImportProcess();
	mIsImporting = false;
	emit OnImportFinished();
	return result;
}

void tcImportSource::CancelImport()
{
	CancelImportProcess();
}

bool tcImportSource::ImportProcess()
{
	return false;
}

void tcImportSource::CancelImportProcess()
{
}
