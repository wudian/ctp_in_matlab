#include "tcmarketselectdlg.h"

tcMarketSelectDialog::tcMarketSelectDialog(QWidget *pParent)
	: QDialog(pParent)
{
	setupUi(this);
}

bool tcMarketSelectDialog::LoadMarketList(tcMarketManager *pMarketManager)
{
	int i;
	for (i=0; i<pMarketManager->GetMarketCount(); i++) {
		tcMarket *market = pMarketManager->GetMarket(i);
		Q_ASSERT(market);
		cbo1->addItem(market->GetName());
	}
	return true;
}

int tcMarketSelectDialog::GetSelectedMarketIndex()
{
	return cbo1->currentIndex();
}
