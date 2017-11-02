#include "tcdataimptsetupdlg.h"

#include <QHeaderView>

tcDataImporterSetupDialog::tcDataImporterSetupDialog(QWidget *pParent, tcDataImporter *pDataImporter)
	: QDialog(pParent)
{
	mDataImporter = pDataImporter;
	setupUi(this);
	tbl1_1->setColumnCount(1);
	//tbl1_1->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	tbl1_1->verticalHeader()->hide();
	tbl1_1->horizontalHeader()->hide();
	tbl1_1->setSelectionMode(QAbstractItemView::SingleSelection);
	tbl1_1->setSelectionBehavior(QAbstractItemView::SelectRows);
	tbl1_1->setEditTriggers(QAbstractItemView::NoEditTriggers);

	connect(tbl1_1, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(DoSourceSelectionChanged(QTableWidgetItem*, QTableWidgetItem*)));
	connect(btn1_1, SIGNAL(clicked()), this, SLOT(DoSourceSetting()));
	connect(btn1_2, SIGNAL(clicked()), this, SLOT(DoSourceImport()));

	LoadImportSourceList();
}

tcDataImporterSetupDialog::~tcDataImporterSetupDialog()
{
}

void tcDataImporterSetupDialog::LoadImportSourceList()
{
	int sourceindex = 0;
	tcImportSource *source = mDataImporter->CreateImportSource(sourceindex);
	while (source != NULL) {
		int row = tbl1_1->rowCount();
		tbl1_1->insertRow(row);
		tbl1_1->setItem(row, 0, new QTableWidgetItem(source->GetDescription()));
		delete source;
		sourceindex++;
		source = mDataImporter->CreateImportSource(sourceindex);
	}

	sourceindex = mDataImporter->GetActiveSourceIndex();
	tbl1_1->setCurrentCell(sourceindex, 0);
}

void tcDataImporterSetupDialog::DoSourceSelectionChanged(QTableWidgetItem* pCurrent, QTableWidgetItem* pPrevious)
{
	btn1_1->setEnabled(false);
	btn1_2->setEnabled(false);
	int sourceindex = tbl1_1->currentIndex().row();
	mDataImporter->SetActiveSourceIndex(sourceindex);

	tcImportSource *source = mDataImporter->CreateImportSource(sourceindex);
	if (! source) {
		return;
	}
	if (source->HaveSettingDialog()) {
		btn1_1->setEnabled(true);
	}
	delete source;
	btn1_2->setEnabled(true);
}

void tcDataImporterSetupDialog::DoSourceSetting()
{
	int sourceindex = tbl1_1->currentIndex().row();
	tcImportSource *source = mDataImporter->CreateImportSource(sourceindex);
	if (! source) {
		return;
	}
	source->ShowSettingDialog(this);
	delete source;
}

void tcDataImporterSetupDialog::DoSourceImport()
{
	mDataImporter->Import(this);
}
