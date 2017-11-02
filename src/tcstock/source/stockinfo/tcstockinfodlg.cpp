#include "tcstockinfodlg.h"

#include <QMessageBox>

#include "../tcdefine.h"
#include "../service/tcsvcpack.h"
#include "tcstockinfo.h"

tcStockInfoDialog::tcStockInfoDialog(QWidget *pParent, bool pAppendMode)
	: QDialog(pParent)
{
	mAppendMode = pAppendMode;

	setupUi(this);
	if (! mAppendMode) {
		edt1->setDisabled(true);
	}
	disconnect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(DoOk()));
}

bool tcStockInfoDialog::LoadFromStock(tcStock *pStock)
{
	edt1->setText(pStock->GetStockCode());
	edt2->setText(pStock->GetStockName());
	edt3->setText(pStock->GetDescription());
	return true;
}

bool tcStockInfoDialog::SaveToStock(tcStock *pStock)
{
	pStock->SetStockCode(edt1->text());
	pStock->SetStockName(edt2->text());
	pStock->SetDescription(edt3->text());
	return true;
}

void tcStockInfoDialog::DoOk()
{
	if (mAppendMode) {
		if (edt1->text().length() == 0) {
			QMessageBox::warning(this, SYSTEM_NAME, tr("Must input the stock code."));
			edt1->setFocus();
			return;
		}
		tcStockInfo stockinfo(edt1->text());
		if (stockinfo.IsAvailable()) {
			QMessageBox::warning(this, SYSTEM_NAME, tr("The stock with a same stock code already exists, change another stock code please."));
			edt1->setFocus();
			return;
		}
	}
	if (edt2->text().length() == 0) {
		QMessageBox::warning(this, SYSTEM_NAME, tr("Must input the stock name."));
		edt2->setFocus();
		return;
	}

	accept();
}
