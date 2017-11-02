#include "MainWindow.h"
#include <qtablewidget.h>
#include <qboxlayout.h>
#include <qdatetime.h>
#include <QTextCodec>
#include <qstring.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <qfiledialog.h>
#include "MdTable.h"
#include "MarketDataController.h"
#include "TradeController.h"
#include "SelectShowMdWindow.h"
#include "SubscribingDialog.h"
#include "QuantBoxApi.h"

using namespace std;

static QTextCodec *s_codec = QTextCodec::codecForName("GB18030");
static const char *s_ConnectionStatus[] =
{
	"未初始化",
	"已经初始化",
	"连接已经断开",
	"连接中",
	"连接成功",
	"授权中",
	"授权成功",
	"登录中",
	"登录成功",
	"结算单确认中",
	"已经确认",
	"最大值"
};

MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, sMdWindow(nullptr) 
	, subDialog(nullptr)
{
	//初始化连接、断开按钮
	connectMdButton = new QPushButton(QStringLiteral("连接行情"));
	connectTdButton = new QPushButton(QStringLiteral("连接交易"));
	
	//初始化订阅、退订按键
	subscribeInstruments = new QLineEdit();
	subscribeInstruments->setEnabled(false);
	subscribePeriods = new QLineEdit;
	subscribePeriods->setEnabled(false);
	subscribeButton = new QPushButton(QStringLiteral("订阅行情"));
	subscribeButton->setEnabled(false);

	unsubscribeInstruments = new QLineEdit();
	unsubscribeInstruments->setEnabled(false);
	unsubscribePeriods = new QLineEdit;
	unsubscribePeriods->setEnabled(false);
	unsubscribeButton = new QPushButton(QStringLiteral("退订行情"));
	unsubscribeButton->setEnabled(false);

	// 订阅/退订行情区域
	//最上面两“层”的布局
	QHBoxLayout *top1 = new QHBoxLayout();
	top1->addWidget(new QLabel(QStringLiteral("合约代码:")));
	subscribeInstruments->setFixedSize(345, 25);
	subscribePeriods->setFixedSize(300, 25);
	top1->addWidget(subscribeInstruments);
	top1->addWidget(new QLabel(QStringLiteral("周期:")));
	top1->addWidget(subscribePeriods);
	top1->addWidget(subscribeButton);
	QHBoxLayout *top2 = new QHBoxLayout();
	top2->addWidget(new QLabel(QStringLiteral("合约代码:")));
	unsubscribeInstruments->setFixedSize(345, 25);
	unsubscribePeriods->setFixedSize(300, 25);
	top2->addWidget(unsubscribeInstruments);
	top2->addWidget(new QLabel(QStringLiteral("周期:")));
	top2->addWidget(unsubscribePeriods);
	top2->addWidget(unsubscribeButton);
	QVBoxLayout *top = new QVBoxLayout();
	top->addLayout(top1);
	top->addLayout(top2);

	//设置表格
	table = new MdTable();
	QVBoxLayout *conLayout = new QVBoxLayout();
	conLayout->addStretch();
	conLayout->addWidget(connectMdButton);
	conLayout->addWidget(connectTdButton);
	QHBoxLayout *down = new QHBoxLayout();		//下方的布局由表格和连接按钮那一块组成
	down->addWidget(table);
	down->addLayout(conLayout);
	down->setAlignment(Qt::AlignTop);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(top);
	mainLayout->addLayout(down);

	QWidget *mainW = new QWidget();
	mainW->setLayout(mainLayout);
	setCentralWidget(mainW);

	createStatusBur();	//创建状态栏
	createMenu();		//创建菜单栏
	initController();

	//设置窗口属性
	setWindowTitle(QStringLiteral("行情主机"));
}

/************************************私有函数*******************************************************/

//初始化控制器
void MainWindow::initController()
{
	m_mdController = make_shared<MarketDataController>();
	//连接按钮与连接控制器连接
	connect(connectMdButton, SIGNAL(clicked()), m_mdController.get(), SLOT(connectMdServer()));
	connect(subscribeButton, SIGNAL(clicked()), m_mdController.get(), SLOT(subscribe()));
	connect(unsubscribeButton, SIGNAL(clicked()), m_mdController.get(), SLOT(unsubscribe()));
	//连接控制器与状态栏连接
	connect(m_mdController.get(), &MarketDataController::md_tick, this, &MainWindow::Md_Tick, Qt::BlockingQueuedConnection);
	connect(m_mdController.get(), &MarketDataController::md_kline, this, &MainWindow::Md_KLine, Qt::BlockingQueuedConnection);

	//交易
	m_tdController = make_shared<TradeController>();
	connect(connectTdButton, SIGNAL(clicked()), m_tdController.get(), SLOT(connectTdServer()));

	connect(m_tdController.get(), &TradeController::connect_status, this, &MainWindow::ConnectStatus, Qt::BlockingQueuedConnection);
}

//创建状态栏
void MainWindow::createStatusBur()
{
	//设置时间标签
	timerForUpdateTimeLabel = new QTimer(this);
	connect(timerForUpdateTimeLabel, SIGNAL(timeout()), this, SLOT(updateTime()));
	timerForUpdateTimeLabel->start(1000);
	localTimeLabel = new QLabel(QStringLiteral(""));
	statusBar()->addPermanentWidget(localTimeLabel);
	for (int i = 0; i < 5; ++i) {
		ExchangeTimeLabel[i] = new QLabel(QStringLiteral(""));
		statusBar()->addPermanentWidget(ExchangeTimeLabel[i]);
	}
	
	//初始化状态标签
	MdStatusLabel = new QLabel(s_codec->toUnicode(s_ConnectionStatus[E_uninit]));
	statusBar()->addWidget(new QLabel(QStringLiteral("行情状态:")));
	statusBar()->addWidget(MdStatusLabel);
	TdStatusLabel = new QLabel(s_codec->toUnicode(s_ConnectionStatus[E_uninit]));
	statusBar()->addWidget(new QLabel(QStringLiteral("交易状态:")));
	statusBar()->addWidget(TdStatusLabel);
}

//创建菜单栏
void MainWindow::createMenu()
{
	//选择菜单
	selectMenu = menuBar()->addMenu(QStringLiteral("选择"));
	selectShowMd = new QAction(QStringLiteral("展示合约"), this);
	connect(selectShowMd, SIGNAL(triggered()), this, SLOT(showSelectMdWindow()));
	writeToDB = new QAction(QStringLiteral("写入数据库"), this);
	connect(writeToDB, SIGNAL(triggered()), this, SLOT(selectFileForWriter()));
	selectMenu->addAction(selectShowMd);
	selectMenu->addAction(writeToDB);
	//查看菜单
	checkMenu = menuBar()->addMenu(QStringLiteral("查看"));
	showSubscribingAction = new QAction(QStringLiteral("正在订阅"), this);
	connect(showSubscribingAction, SIGNAL(triggered()), this, SLOT(showSubscribing()));
	checkMenu->addAction(showSubscribingAction);
}

/************************************槽函数*********************************************************/

//时刻更新本地时间
void MainWindow::updateTime()
{
	static const char *s_ExchangeTime[] =
	{
		"上期所时间: ",
		"大商所时间: ",
		"郑商所时间: ",
		"中金所时间: ",
		"能源中心时间: "
	};
	const int *diffSec = m_tdController->get_differenceSeconds();
	QTime localTime = QTime::currentTime();
	localTimeLabel->setText(QStringLiteral("本地时间: ") + localTime.toString("hh:mm:ss"));
	for (int i = 0; i < 5; ++i) {
		if (diffSec[i] != INVALID_DIFF_SECONDS) {
			QTime time = localTime.addSecs(diffSec[i]);
			QString timeStr = time.toString("hh:mm:ss");
			ExchangeTimeLabel[i]->setText(s_codec->toUnicode(s_ExchangeTime[i]) + timeStr);
		}
		else {
			ExchangeTimeLabel[i]->setText(s_codec->toUnicode(s_ExchangeTime[i]) + "--:--:--");
		}
	}
}

void MainWindow::Md_Tick(wdTick *pTick)
{

}

void MainWindow::Md_KLine(wdKLine *pKLine)
{

}

void MainWindow::ConnectStatus(wdConnectInfo *info)
{
	if (info->type == E_MD) {
		MdStatusLabel->setText(s_codec->toUnicode(s_ConnectionStatus[info->status]));

		if (info->status == E_logined) { //连接成功后使得订阅和退订可执行				
			//激活相关的窗口部件
			subscribeButton->setEnabled(true);
			subscribeInstruments->setEnabled(true);
			subscribePeriods->setEnabled(true);
			unsubscribeButton->setEnabled(true);
			unsubscribeInstruments->setEnabled(true);	
			unsubscribePeriods->setEnabled(true);

			////设置订阅/退订控制器		
			m_mdController->setSubTextLine(subscribeInstruments);
			m_mdController->setUnsubTextLine(unsubscribeInstruments);		
		}
		else if (info->status == E_unconnected) {
			QMessageBox::information(this, QStringLiteral("连接行情前置失败"), info->ErrorMsg);
			return;
		}
	}
	else {
		TdStatusLabel->setText(s_codec->toUnicode(s_ConnectionStatus[info->status]));

		if (info->status == E_unconnected) {
			QMessageBox::information(this, QStringLiteral("连接交易前置失败"), info->ErrorMsg);
			return;
		}
	}
}



//断开连接,初始化与api相关的控制器
//通知把表格内容清空
//void MainWindow::disconnect(){
//	//让各控制器恢复原本状态，使得后台api自动销毁
//	m_tdController->reset();
//	unsubController->reset();
//	m_mdController->reset();
//	onekeySubController->reset();
//	//禁用相关部件
//	subscribeButton->setEnabled(false);
//	subscribeInstruments->clear();
//	subscribeInstruments->setEnabled(false);
//	unsubscribeButton->setEnabled(false);
//	unsubscribeInstruments->clear();
//	unsubscribeInstruments->setEnabled(false);
//	disconnectButton->setEnabled(false);
//	//让连接控制器可用
//	connectButton->setEnabled(true);
//	//修改状态栏显示
//	statusLabel->setText(OFFLINE);
//	//表格清空
//	table->resetTable();
//	//把已订阅的列表清空
//	if (sMdWindow != nullptr){
//		sMdWindow->clearShowedInstru();
//	}
//}

//展示对话框让使用者选择显示的合约
void MainWindow::showSelectMdWindow(){
	if (sMdWindow == nullptr){
		sMdWindow = new SelectShowMdWindow();
		connect(sMdWindow, SIGNAL(showChange(std::set<QString>&)), table, SLOT(updateTableForSelect(std::set<QString>&)));
		connect(unsubscribeButton, SIGNAL(clicked()), table, SLOT(callUnsubUpdateTimer()));
	}
	sMdWindow->showDialog();
}

//展示对话框让使用者选择文件写入数据库
void MainWindow::selectFileForWriter(){
	/*if (m_mdController->isConnect() == true){
		QMessageBox::information(this, QStringLiteral("错误"), QStringLiteral("请断开主机再操作"));
		return;
	}
	else{
		QStringList filenames = QFileDialog::getOpenFileNames(this,QStringLiteral("选择行情记录"),"./data","记录文件 (*.csv)");
		if (filenames.isEmpty()){
			return;
		}
		else{
			dbWriterController->readyToWrite(filenames);
		}
	}*/
}

//展示正在订阅的合约
void MainWindow::showSubscribing(){
	if (subDialog == nullptr){
		subDialog = new SubscribingDialog();
		subDialog->show();
	}
	else{
		subDialog->showDialog();
	}
}
