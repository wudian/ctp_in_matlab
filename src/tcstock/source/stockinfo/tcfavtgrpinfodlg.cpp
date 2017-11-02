#include "tcfavtgrpinfodlg.h"

#include <QMessageBox>

#include "../tcdefine.h"

tcFavouriteGroupInfoDialog::tcFavouriteGroupInfoDialog(QWidget *pParent)
	: QDialog(pParent)
{
	setupUi(this);
	disconnect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(DoOk()));
}

bool tcFavouriteGroupInfoDialog::LoadFromFavouriteGroup(tcFavouriteGroup *pFavouriteGroup)
{
	edt1->setText(pFavouriteGroup->GetName());
	edt2->setText(pFavouriteGroup->GetDescription());
	return true;
}

bool tcFavouriteGroupInfoDialog::SaveToFavouriteGroup(tcFavouriteGroup *pFavouriteGroup)
{
	pFavouriteGroup->SetName(edt1->text());
	pFavouriteGroup->SetDescription(edt2->text());
	return true;
}

void tcFavouriteGroupInfoDialog::DoOk()
{
	if (edt1->text().length() == 0) {
		QMessageBox::warning(this, SYSTEM_NAME, tr("Must input the favourite group name."));
		edt1->setFocus();
		return;
	}

	accept();
}
