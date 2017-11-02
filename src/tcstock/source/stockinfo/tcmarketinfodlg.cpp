#include "tcmarketinfodlg.h"

tcMarketInfoDialog::tcMarketInfoDialog(QWidget *pParent)
	: QDialog(pParent)
{
	setupUi(this);
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(DoOk()));
}

bool tcMarketInfoDialog::LoadFromMarket(tcMarket *pMarket)
{
	edt1->setText(pMarket->GetName());
	edt2->setText(pMarket->GetDescription());
	return true;
}

bool tcMarketInfoDialog::SaveToMarket(tcMarket *pMarket)
{
	pMarket->SetName(edt1->text());
	pMarket->SetDescription(edt2->text());
	return true;
}

void tcMarketInfoDialog::DoOk()
{
	//TODO: do some check
	accept();
}
