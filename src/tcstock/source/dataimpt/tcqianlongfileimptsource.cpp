#include "tcqianlongfileimptsource.h"

tcQianLongFileImportSource::tcQianLongFileImportSource()
{
}

QString tcQianLongFileImportSource::GetDescription()
{
	return tr("QianLong data");
}

bool tcQianLongFileImportSource::HaveSettingDialog()
{
	return false;
}

void tcQianLongFileImportSource::ShowSettingDialog(QWidget *pParent)
{
}

bool tcQianLongFileImportSource::ImportProcess()
{
	return false;
}

void tcQianLongFileImportSource::CancelImportProcess()
{
}
