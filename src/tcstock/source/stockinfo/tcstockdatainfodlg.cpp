#include "tcstockdatainfodlg.h"

#include <QHeaderView>

tcStockDataInfoDialog::tcStockDataInfoDialog(QWidget *pParent)
	: QDialog(pParent)
{
	setupUi(this);
	tbl1->verticalHeader()->hide();
    tbl1->setSelectionMode(QAbstractItemView::SingleSelection);
    tbl1->setSelectionBehavior(QAbstractItemView::SelectRows);

	mDataModel = new tcStockDataItemModel(this);
	tbl1->setModel(mDataModel);
	QStringList grouplist;
	mDataModel->GetGroupList(grouplist);
	foreach (QString groupname, grouplist) {
		cbo1->addItem(groupname);
	}

	mDataDelegate = new tcStockDataItemDelegate(this);
	tbl1->setItemDelegate(mDataDelegate);

	mDataModel->CreateStockList(cbo1->currentIndex(), edt1->text(), edt2->text());

	cld1->setDate(QDate::currentDate());

	connect(cld1, SIGNAL(dateChanged(const QDate &)), this, SLOT(DoDateChanged(const QDate &)));
	connect(cbo1, SIGNAL(currentIndexChanged(int)), this, SLOT(DoGroupChanged(int)));
	connect(edt1, SIGNAL(textChanged(const QString &)), this, SLOT(DoFilterTextChanged(const QString &)));
	connect(edt2, SIGNAL(textChanged(const QString &)), this, SLOT(DoFilterTextChanged(const QString &)));

	DoGroupChanged(-1);
}

void tcStockDataInfoDialog::DoDateChanged(const QDate &pDate)
{
	setUpdatesEnabled(false);
	mDataModel->LoadStockData(pDate);
	setUpdatesEnabled(true);
}

void tcStockDataInfoDialog::DoGroupChanged(int pIndex)
{
	int groupindex = cbo1->currentIndex();
	setUpdatesEnabled(false);
	mDataModel->CreateStockList(groupindex, edt1->text(), edt2->text());
	mDataModel->LoadStockData(cld1->date());
	setUpdatesEnabled(true);
}

void tcStockDataInfoDialog::DoFilterTextChanged(const QString &pText)
{
	DoGroupChanged(-1);
}
