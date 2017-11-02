#include "tcmainwnd.h"

#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QMessageBox>

#include "tcdefine.h"
#include "tcaboutdlg.h"
#include "service/tcsvcpack.h"
#include "importer/tcimporterpack.h"
#include "dataimpt/tcdataimptpack.h"

tcMainWindow::tcMainWindow(QWidget *pParent)
	: QMainWindow(pParent)
{
	setWindowTitle(tr("Teacher.Cheng Stock   [Version: %1]").arg(SYSTEM_VERSION));

	//create the menu and toolbar
	CreateMenusAndToolbar();

	//create the daily view
	mDailyViewWidget = new tcDailyViewWidget(this);
	setCentralWidget(mDailyViewWidget);

	//create the weekly view
	mWeeklyDock = new QDockWidget(tr("Weekly View"), this);
	mWeeklyDock->setAllowedAreas(Qt::BottomDockWidgetArea);
	mWeeklyDock->setMinimumSize(0, 150);
	mWeeklyViewWidget = new tcWeeklyViewWidget(mWeeklyDock);
	mWeeklyDock->setWidget(mWeeklyViewWidget);
	addDockWidget(Qt::BottomDockWidgetArea, mWeeklyDock);

	//create the tool pad widget
	mStockListDock = new QDockWidget(tr("Tool Pad"), this);
	mStockListDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	mStockListDock->setMinimumSize(250, 0);
	mToolPadWidget = new tcToolPadWidget(mStockListDock);
	connect(mToolPadWidget, SIGNAL(OnStockSelected(tcStockInfoList *)), this, SLOT(DoStockSelected(tcStockInfoList *)));
	mStockListDock->setWidget(mToolPadWidget);
	addDockWidget(Qt::RightDockWidgetArea, mStockListDock);
}

tcMainWindow::~tcMainWindow()
{
}

void tcMainWindow::CreateMenusAndToolbar()
{
	QAction *action;
	QMenu *menu;
	QToolBar *toolbar;

	toolbar = addToolBar(tr("ToolBar"));

	menu = menuBar()->addMenu(tr("&Data"));
	action = new QAction(QIcon(""), tr("Modify Market..."), this);
	connect(action, SIGNAL(triggered()), this, SLOT(DoModifyMarket()));
	menu->addAction(action);
	menu->addSeparator();
	action = new QAction(QIcon(""), tr("Input Stock Data..."), this);
	connect(action, SIGNAL(triggered()), this, SLOT(DoInputStockData()));
	menu->addAction(action);
	toolbar->addAction(action);
	action = new QAction(QIcon(""), tr("Edit Favourite Stock..."), this);
	connect(action, SIGNAL(triggered()), this, SLOT(DoEditFavouriteStock()));
	menu->addAction(action);
	toolbar->addAction(action);
	action = new QAction(QIcon(""), tr("Import Stock Data..."), this);
	connect(action, SIGNAL(triggered()), this, SLOT(DoImportStockData()));
	menu->addAction(action);
	toolbar->addAction(action);
	menu->addSeparator();
	action = new QAction(QIcon(""), tr("Exit"), this);
	connect(action, SIGNAL(triggered()), this, SLOT(DoExit()));
	menu->addAction(action);

	menu = menuBar()->addMenu(tr("&View"));
	action = new QAction(QIcon(""), tr("Stock List"), this);
	connect(action, SIGNAL(triggered()), this, SLOT(DoViewStockList()));
	menu->addAction(action);
	action = new QAction(QIcon(""), tr("Weekly View"), this);
	connect(action, SIGNAL(triggered()), this, SLOT(DoViewWeeklyView()));
	menu->addAction(action);

	menu = menuBar()->addMenu(tr("&Help"));
	action = new QAction(QIcon(""), tr("About..."), this);
	connect(action, SIGNAL(triggered()), this, SLOT(DoAbout()));
	menu->addAction(action);

#ifdef _DEBUG
	menu = menuBar()->addMenu("Test");
	action = new QAction(QIcon(""), "test", this);
	connect(action, SIGNAL(triggered()), this, SLOT(mytest()));
	menu->addAction(action);
#endif
}

void tcMainWindow::DoModifyMarket()
{
	tcObjService::GetMarketManager()->EditMarketList(this);
}

void tcMainWindow::DoInputStockData()
{
	tcObjService::GetStockManager()->EditStockData(this);
}

void tcMainWindow::DoEditFavouriteStock()
{
	tcFavouriteManager *favouritemanager = tcObjService::GetFavouriteManager();
	favouritemanager->EditFavouriteList(this, -1);
}

void tcMainWindow::DoImportStockData()
{
	tcDataImporter imp;
	imp.ShowSetupDialog(this);
}

void tcMainWindow::DoExit()
{
	close();
}

void tcMainWindow::DoViewStockList()
{
	mStockListDock->setVisible(! mStockListDock->isVisible());
}

void tcMainWindow::DoViewWeeklyView()
{
	mWeeklyDock->setVisible(! mWeeklyDock->isVisible());
}

void tcMainWindow::DoAbout()
{
	tcAboutDialog dlg(this);
	dlg.exec();
}

void tcMainWindow::mytest()
{
	//QDir dir("E:\\source\\TCStock\\001\\doc\\qianlong\\");

	//tcQianlongImporter imp;
	//imp.ReadFile(dir);

	/*
	tcStockInfoImporter imp;
	int count = imp.LoadFromFile("E:\\source\\TCStock\\001\\bin\\SZSE.COD", 1);
	QMessageBox::information(this, SYSTEM_NAME, tr("%1 stocks info imported.").arg(count));
	*/
	//tcSinaStockDataImporter *imp = new tcSinaStockDataImporter();
	//imp->LoadStockData();

	tcDataImporter imp;
	imp.ShowSetupDialog(this);
	//imp.Import(this);
}

void tcMainWindow::DoStockSelected(tcStockInfoList *pStockInfoList)
{
	mDailyViewWidget->LoadStockInfoList(pStockInfoList);
	mWeeklyViewWidget->LoadStockInfoList(pStockInfoList);
}
