#include "tcstocklistwgt.h"

#include <QtCore/QList>
#include <QHeaderView>

#include "../service/tcsvcpack.h"
#include "../stockinfo/tcstockinfopack.h"

tcStockListWidget::tcStockListWidget(QWidget *pParent)
	: QWidget(pParent)
{
	setupUi(this);
	QStringList titles;
	titles<<tr("Stock Code")<<tr("Stock Name");
	tbl1->setColumnCount(2);
	tbl1->setHorizontalHeaderLabels(titles);
	//tbl1->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
	tbl1->verticalHeader()->hide();
	//tbl1->setSelectionMode(QAbstractItemView::SingleSelection);
	tbl1->setSelectionBehavior(QAbstractItemView::SelectRows);
	tbl1->setEditTriggers(QAbstractItemView::NoEditTriggers);

	connect(cbo1, SIGNAL(currentIndexChanged(int)), this, SLOT(DoMarketIndexChanged(int)));
	connect(btn1, SIGNAL(clicked()), this, SLOT(DoEditFavourite()));
	connect(edt1, SIGNAL(textChanged(const QString &)), this, SLOT(DoFilterTextChanged(const QString &)));
	connect(edt2, SIGNAL(textChanged(const QString &)), this, SLOT(DoFilterTextChanged(const QString &)));
	connect(tbl1, SIGNAL(itemSelectionChanged()), this, SLOT(DoStockSelectionChanged()));
	connect(&mViewStockInfoList, SIGNAL(OnGroupListNeedReload()), this, SLOT(DoGroupListNeedReload()));
	connect(&mViewStockInfoList, SIGNAL(OnStockListNeedReload()), this, SLOT(DoStockListNeedReload()));

	DoMarketModified();
}

tcStockListWidget::~tcStockListWidget()
{
}

void tcStockListWidget::DoMarketModified()
{
	QString marketname = cbo1->currentText();
	cbo1->clear();

	QStringList grouplist;
	mViewStockInfoList.GetGroupList(grouplist);
	foreach (QString groupname, grouplist) {
		cbo1->addItem(groupname);
	}
	//restore the last selected market in the combo
	int index = cbo1->findText(marketname);
	if (index >= 0) {
		cbo1->setCurrentIndex(index);
	}
}

void tcStockListWidget::DoStockModified(tcMarket *pMarket)
{
	int index = cbo1->currentIndex();
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();
	if (index == 0 || marketmanager->GetMarket(index) == pMarket) {
		DoMarketIndexChanged(cbo1->currentIndex());
	}
}

void tcStockListWidget::DoEditFavourite()
{
	tcFavouriteManager *favouritemanager = tcObjService::GetFavouriteManager();
	favouritemanager->EditFavouriteList(this, cbo1->currentIndex());
}

void tcStockListWidget::DoMarketIndexChanged(int pIndex)
{
	mViewStockInfoList.ReloadFromGroupFilter(pIndex, edt1->text(), edt2->text());
	//show stock in the tableview
	tbl1->setRowCount(0);
	foreach (tcStockInfo info, mViewStockInfoList) {
		int row = tbl1->rowCount();
		tbl1->insertRow(row);
		tbl1->setItem(row, 0, new QTableWidgetItem(info.GetStockCode()));
		tbl1->setItem(row, 1, new QTableWidgetItem(info->GetStockName()));
	}
}

void tcStockListWidget::DoFilterTextChanged(const QString &pText)
{
	DoMarketIndexChanged(cbo1->currentIndex());
}

void tcStockListWidget::DoGroupListNeedReload()
{
	DoMarketModified();
}

void tcStockListWidget::DoStockSelectionChanged()
{
	tcStockInfoList list;
	QList<QTableWidgetItem*> sellist = tbl1->selectedItems();
	foreach(QTableWidgetItem *item, sellist) {
		tcStockInfo info = mViewStockInfoList[item->row()];
		list.append(info);
		break;
	}
	emit OnStockSelected(&list);
}

void tcStockListWidget::DoStockListNeedReload()
{
	DoMarketIndexChanged(cbo1->currentIndex());
}
