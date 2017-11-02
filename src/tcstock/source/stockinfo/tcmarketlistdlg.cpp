#include "tcmarketlistdlg.h"

#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>

#include "../tcdefine.h"
#include "../service/tcsvcpack.h"
#include "tcmarketmgr.h"

tcMarketListDialog::tcMarketListDialog(QWidget *pParent)
	: QDialog(pParent)
{
	setupUi(this);
	connect(cbo1_1, SIGNAL(currentIndexChanged(int)), this, SLOT(DoMarketIndexChanged(int)));
	connect(btn1_1, SIGNAL(clicked()), this, SLOT(DoAppendMarket()));
	connect(btn1_2, SIGNAL(clicked()), this, SLOT(DoModifyMarket()));
	connect(btn1_3, SIGNAL(clicked()), this, SLOT(DoRemoveMarket()));
	connect(btn1, SIGNAL(clicked()), this, SLOT(DoAppendStock()));
	connect(btn2, SIGNAL(clicked()), this, SLOT(DoModifyStock()));
	connect(btn3, SIGNAL(clicked()), this, SLOT(DoRemoveStock()));
	connect(btn4, SIGNAL(clicked()), this, SLOT(DoImportStocksFromCSV()));
	connect(btn5, SIGNAL(clicked()), this, SLOT(DoExportStocksToCSV()));
    QStringList titles;
    titles<<tr("Stock Code")<<tr("Stock Name")<<tr("Description");
    tbl1->setColumnCount(3);
    tbl1->setHorizontalHeaderLabels(titles);
    //tbl1->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    tbl1->verticalHeader()->hide();
    tbl1->setSelectionMode(QAbstractItemView::SingleSelection);
    tbl1->setSelectionBehavior(QAbstractItemView::SelectRows);
	tbl1->setEditTriggers(QAbstractItemView::NoEditTriggers);

	LoadMarketList();
	LoadStockList();
}

void tcMarketListDialog::LoadMarketList()
{
	cbo1_1->clear();
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();
	int i;
	for (i=0; i<marketmanager->GetMarketCount(); i++) {
		tcMarket *market = marketmanager->GetMarket(i);
		cbo1_1->addItem(market->GetName());
	}
}

void tcMarketListDialog::LoadStockList()
{
	tcMarket *market = GetSelectedMarket();
	if (market == NULL) {
		return;
	}
	tcStockInfoList stockinfolist;
	if (! market->GetStockInfoList(stockinfolist)) {
		return;
	}

	setUpdatesEnabled(false);
	tbl1->setRowCount(0);
	foreach (tcStockInfo stockinfo, stockinfolist) {
		int row = tbl1->rowCount();
		tbl1->insertRow(row);
		tbl1->setItem(row, 0, new QTableWidgetItem(stockinfo.GetStockCode()));
		tbl1->setItem(row, 1, new QTableWidgetItem(stockinfo->GetStockName()));
		tbl1->setItem(row, 2, new QTableWidgetItem(stockinfo->GetDescription()));
	}
	setUpdatesEnabled(true);
}

tcMarket* tcMarketListDialog::GetSelectedMarket()
{
	int marketindex = cbo1_1->currentIndex();
	if (marketindex < 0) {
		return NULL;
	}
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();
	return marketmanager->GetMarket(marketindex);
}

void tcMarketListDialog::DoMarketIndexChanged(int)
{
	LoadStockList();
}

void tcMarketListDialog::DoAppendMarket()
{
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();
	tcMarket *market = marketmanager->AppendMarket(this);
	if (! market) {
		return;
	}
	cbo1_1->addItem(market->GetName());
	cbo1_1->setCurrentIndex(cbo1_1->count()-1);
}

void tcMarketListDialog::DoModifyMarket()
{
	int marketindex = cbo1_1->currentIndex();
	if (marketindex < 0) {
		return;
	}
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();
	tcMarket *market = marketmanager->ModifyMarket(this, marketindex);
	if (! market) {
		return;
	}
	cbo1_1->setItemText(marketindex, market->GetName());
}

void tcMarketListDialog::DoRemoveMarket()
{
	int marketindex = cbo1_1->currentIndex();
	if (marketindex < 0) {
		return;
	}
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();
	if (! marketmanager->RemoveMarket(this, marketindex)) {
		return;
	}
	cbo1_1->removeItem(marketindex);
}

void tcMarketListDialog::DoAppendStock()
{
	tcMarket *market = GetSelectedMarket();
	if (market == NULL) {
		QMessageBox::warning(this, SYSTEM_NAME, tr("Create some markets please."), QMessageBox::Ok);
		return;
	}
	tcStockInfo stockinfo;
	if (! market->AppendStock(this, stockinfo)) {
		return;
	}
	int row = tbl1->rowCount();
	tbl1->insertRow(row);
	tbl1->setItem(row, 0, new QTableWidgetItem(stockinfo.GetStockCode()));
	tbl1->setItem(row, 1, new QTableWidgetItem(stockinfo->GetStockName()));
	tbl1->setItem(row, 2, new QTableWidgetItem(stockinfo->GetDescription()));
}

void tcMarketListDialog::DoModifyStock()
{
	tcMarket *market = GetSelectedMarket();
	if (market == NULL) {
		QMessageBox::warning(this, SYSTEM_NAME, tr("Create some markets please."), QMessageBox::Ok);
		return;
	}
	int stockindex = tbl1->currentIndex().row();
	tcStockInfo stockinfo;
	if (! market->ModifyStock(this, stockindex, stockinfo)) {
		return;
	}
	tbl1->setItem(stockindex, 1, new QTableWidgetItem(stockinfo->GetStockName()));
	tbl1->setItem(stockindex, 2, new QTableWidgetItem(stockinfo->GetDescription()));
}

void tcMarketListDialog::DoRemoveStock()
{
	tcMarket *market = GetSelectedMarket();
	if (market == NULL) {
		QMessageBox::warning(this, SYSTEM_NAME, tr("Create some markets please."), QMessageBox::Ok);
		return;
	}
	int stockindex = tbl1->currentIndex().row();
	if (! market->RemoveStock(this, stockindex)) {
		return;
	}
	tbl1->removeRow(stockindex);
}

void tcMarketListDialog::DoImportStocksFromCSV()
{
	tcMarket *market = GetSelectedMarket();
	if (market == NULL) {
		QMessageBox::warning(this, SYSTEM_NAME, tr("Create some markets please."), QMessageBox::Ok);
		return;
	}

	QString filename = QFileDialog::getOpenFileName(this, SYSTEM_NAME, "", "*.csv");
	if (filename.isNull()) {
		return;
	}
	int succ, fail;
	if (! market->ImportFromCSV(filename, succ, fail)) {
		tcLogService::CreateLog(this, "Erro rwhen import CSV file.");
		return;
	}
	LoadStockList();

	QMessageBox::information(this, SYSTEM_NAME, tr("import %1 stocks, %2 successed.").arg(succ + fail).arg(succ));
}

void tcMarketListDialog::DoExportStocksToCSV()
{
	tcMarket *market = GetSelectedMarket();
	if (market == NULL) {
		QMessageBox::warning(this, SYSTEM_NAME, tr("Create some markets please."), QMessageBox::Ok);
		return;
	}
	//TODO: implement the export function
}
