#include "wdMainWindow.h"
#include <mutex>
#include <qtablewidget.h>
#include <qboxlayout.h>
#include <qdatetime.h>
#include <QTextCodec>
#include <QHeaderView>
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
static const char *s_Type[] =
{
	"限价单",
	"市价单",
	"触发单",
	"废单"
};
static const char *s_Dir[] =
{
	"买",
	"卖"
};
static const char *s_Offset[] =
{
	"开仓",
	"平仓",
	"平今"
};
static const char *s_OrderStatus[] =
{
	"报单已发",
	"撤单已发",
	"部分成交(可撤)",
	"部分成交(不可撤)",
	"全成",
	"全撤",
	"等待成交(可撤)",
	"未知",
	"报单失败",
	"撤单失败(请继续撤单)"
};

//static QMap<const char *, const char *> s_mapExe_Name;

wdMainWindow::wdMainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, sMdWindow(nullptr) 
	, subDialog(nullptr)
{
	setupUi(this);

	lineEdit_insts->setEnabled(false);
	lineEdit_periods->setEnabled(false);	
	pushButton_sub->setEnabled(false);
	pushButton_unsub->setEnabled(false);	


	createStatusBur();	//创建状态栏
	initController();

	//设置窗口属性
	setWindowTitle(QStringLiteral("东航-自动交易软件"));
}

/************************************私有函数*******************************************************/

//初始化控制器
void wdMainWindow::initController()
{
	m_mdController = make_shared<MarketDataController>(*this);
	//连接按钮与连接控制器连接
	connect(checkBox_isHistory, &QCheckBox::stateChanged, m_mdController.get(), &MarketDataController::CheckIsHistory);
	connect(pushButton_3, SIGNAL(clicked()), m_mdController.get(), SLOT(connectMdServer()));
	connect(pushButton_sub, SIGNAL(clicked()), m_mdController.get(), SLOT(subscribe()));
	connect(pushButton_unsub, SIGNAL(clicked()), m_mdController.get(), SLOT(unsubscribe()));
	//连接控制器与状态栏连接
	connect(m_mdController.get(), &MarketDataController::md_tick, this, &wdMainWindow::Md_Tick, Qt::BlockingQueuedConnection);
	connect(m_mdController.get(), &MarketDataController::md_kline, this, &wdMainWindow::Md_KLine, Qt::BlockingQueuedConnection);

	//交易
	m_tdController = make_shared<TradeController>(*this);
	connect(pushButton_4, SIGNAL(clicked()), m_tdController.get(), SLOT(connectTdServer()));
	connect(pushButton_5, SIGNAL(clicked()), m_tdController.get(), SLOT(SendOrder()));
	connect(tableWidget_Order, &QTableWidget::cellDoubleClicked, m_tdController.get(), &TradeController::CancelOrder);
	connect(tableWidget_position, &QTableWidget::cellDoubleClicked, m_tdController.get(), &TradeController::SendOrder);

	connect(m_tdController.get(), &TradeController::connect_status, this, &wdMainWindow::ConnectStatus, Qt::BlockingQueuedConnection);
	connect(m_tdController.get(), &TradeController::error_msg, this, &wdMainWindow::OnError, Qt::BlockingQueuedConnection);
	connect(m_tdController.get(), &TradeController::instruments_rsp, this, &wdMainWindow::InstrumentsRsp, Qt::BlockingQueuedConnection);
	connect(m_tdController.get(), &TradeController::order_rsp, this, &wdMainWindow::OrderRsp, Qt::BlockingQueuedConnection);
	connect(m_tdController.get(), &TradeController::trade_rsp, this, &wdMainWindow::TradeRsp, Qt::BlockingQueuedConnection);
	connect(m_tdController.get(), &TradeController::position_rsp, this, &wdMainWindow::PositionRsp, Qt::BlockingQueuedConnection);
}

//创建状态栏
void wdMainWindow::createStatusBur()
{
	//设置时间标签
	timerForUpdateTimeLabel = new QTimer(this);
	connect(timerForUpdateTimeLabel, SIGNAL(timeout()), this, SLOT(updateTime()));
	timerForUpdateTimeLabel->start(1000);
	localTimeLabel = new QLabel(QStringLiteral(""));
	Ui_MainWindow::statusbar->addPermanentWidget(localTimeLabel);
	for (int i = 0; i < 5; ++i) {
		ExchangeTimeLabel[i] = new QLabel(QStringLiteral(""));
		Ui_MainWindow::statusbar->addPermanentWidget(ExchangeTimeLabel[i]);
	}
	
	//初始化状态标签
	MdStatusLabel = new QLabel(s_codec->toUnicode(s_ConnectionStatus[E_uninit]));
	Ui_MainWindow::statusbar->addWidget(new QLabel(QStringLiteral("行情状态:")));
	Ui_MainWindow::statusbar->addWidget(MdStatusLabel);
	TdStatusLabel = new QLabel(s_codec->toUnicode(s_ConnectionStatus[E_uninit]));
	Ui_MainWindow::statusbar->addWidget(new QLabel(QStringLiteral("交易状态:")));
	Ui_MainWindow::statusbar->addWidget(TdStatusLabel);
}

/************************************槽函数*********************************************************/

//时刻更新本地时间
void wdMainWindow::updateTime()
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

void wdMainWindow::Md_Tick(int row, wdTick *pTick)
{
	if (row >= tableWidget_tick->rowCount())
		tableWidget_tick->insertRow(row);

	tableWidget_tick->setItem(row, 0, new QTableWidgetItem(pTick->InstrumentID));
	tableWidget_tick->setItem(row, 1, new QTableWidgetItem("tick"));
	tableWidget_tick->setItem(row, 2, new QTableWidgetItem(QString::number(pTick->LastPrice)));
}

void wdMainWindow::Md_KLine(int row, wdKLine *pKLine)
{
	if (row >= tableWidget_kline->rowCount())
		tableWidget_kline->insertRow(row);

	tableWidget_kline->setItem(row, 0, new QTableWidgetItem(pKLine->InstrumentID));
	tableWidget_kline->setItem(row, 1, new QTableWidgetItem(pKLine->Period));
	tableWidget_kline->setItem(row, 2, new QTableWidgetItem(QString::number(pKLine->OpenPrice)));
	tableWidget_kline->setItem(row, 3, new QTableWidgetItem(QString::number(pKLine->HighestPrice)));
	tableWidget_kline->setItem(row, 4, new QTableWidgetItem(QString::number(pKLine->LowestPrice)));
	tableWidget_kline->setItem(row, 5, new QTableWidgetItem(QString::number(pKLine->ClosePrice)));

}

void wdMainWindow::OnError(const char *msg)
{
	textBrowser->append(s_codec->toUnicode(msg));
}

void wdMainWindow::ConnectStatus(wdConnectInfo *info)
{
	if (info->type == E_MD) {
		MdStatusLabel->setText(s_codec->toUnicode(s_ConnectionStatus[info->status]));

		if (info->status == E_logined) { //连接成功后使得订阅和退订可执行				
			//激活相关的窗口部件
			pushButton_sub->setEnabled(true);
			lineEdit_insts->setEnabled(true);
			lineEdit_periods->setEnabled(true);
			pushButton_unsub->setEnabled(true);
			pushButton_3->setEnabled(false);
		}
		else if (info->status == E_unconnected) {
			QMessageBox::information(this, QStringLiteral("连接行情前置失败:"), s_codec->toUnicode(info->ErrorMsg));
			pushButton_3->setEnabled(true);
			return;
		}
	}
	else {
		TdStatusLabel->setText(s_codec->toUnicode(s_ConnectionStatus[info->status]));

		if (info->status == E_unconnected) {
			QMessageBox::information(this, QStringLiteral("连接交易前置失败:"), s_codec->toUnicode(info->ErrorMsg));
			pushButton_3->setEnabled(true);
			return;
		}
		else if (info->status == E_confirmed) {
			pushButton_4->setEnabled(false);
		}
	}
}

void wdMainWindow::InstrumentsRsp(const std::map<std::string, wdInstrument> *mapInsts)
{
	static std::once_flag winner_flag2; 
	static QMap<char, const char *> s_mapInstrumentStatus;
	std::call_once(winner_flag2, [&](){
		s_mapInstrumentStatus[THOST_FTDC_IS_BeforeTrading] = "开盘前";
		s_mapInstrumentStatus[THOST_FTDC_IS_NoTrading] = "非交易";
		s_mapInstrumentStatus[THOST_FTDC_IS_Continous] = "连续交易";
		s_mapInstrumentStatus[THOST_FTDC_IS_AuctionOrdering] = "集合竞价报单";
		s_mapInstrumentStatus[THOST_FTDC_IS_AuctionBalance] = "集合竞价价格平衡";
		s_mapInstrumentStatus[THOST_FTDC_IS_AuctionMatch] = "集合竞价撮合";
		s_mapInstrumentStatus[THOST_FTDC_IS_Closed] = "收盘";
	});

	tableWidget_inst->clearContents();
	int i = 0;
	for (auto it = mapInsts->begin(); it != mapInsts->end(); ++it) {
		tableWidget_inst->insertRow(i);
		tableWidget_inst->setItem(i, 0, new QTableWidgetItem(it->second.ProductID));
		tableWidget_inst->setItem(i, 1, new QTableWidgetItem(it->second.InstrumentID));
		tableWidget_inst->setItem(i, 2, new QTableWidgetItem(it->second.ExchangeID));
		tableWidget_inst->setItem(i, 3, new QTableWidgetItem(QString::number(it->second.VolumeMultiple)));
		tableWidget_inst->setItem(i, 4, new QTableWidgetItem(QString::number(it->second.PriceTick)));
		tableWidget_inst->setItem(i, 5, new QTableWidgetItem(s_codec->toUnicode(s_mapInstrumentStatus[it->second.InstrumentStatus])));
		tableWidget_inst->setItem(i, 6, new QTableWidgetItem(QString::number(it->second.LongMarginRatioByMoney)));
		tableWidget_inst->setItem(i, 7, new QTableWidgetItem(QString::number(it->second.ShortMarginRatioByMoney)));
		tableWidget_inst->setItem(i, 8, new QTableWidgetItem(QString::number(it->second.OpenRatioByMoney)));
		tableWidget_inst->setItem(i, 9, new QTableWidgetItem(QString::number(it->second.CloseRatioByMoney)));
		tableWidget_inst->setItem(i, 10, new QTableWidgetItem(QString::number(it->second.CloseTodayRatioByMoney)));
		++i;
	}
}

void wdMainWindow::OrderRsp(int i, const wdOrder &order)
{
	if (tableWidget_Order->rowCount() <= i) {
		tableWidget_Order->insertRow(i);
	}
	tableWidget_Order->setItem(i, 0, new QTableWidgetItem(order.OrderSysID));
	tableWidget_Order->setItem(i, 1, new QTableWidgetItem(s_codec->toUnicode(s_Type[order.Type])));
	tableWidget_Order->setItem(i, 2, new QTableWidgetItem(order.InstrumentID));
	tableWidget_Order->setItem(i, 3, new QTableWidgetItem(s_codec->toUnicode(s_Dir[order.Dir])));
	tableWidget_Order->setItem(i, 4, new QTableWidgetItem(s_codec->toUnicode(s_Offset[order.Offset])));
	tableWidget_Order->setItem(i, 5, new QTableWidgetItem(s_codec->toUnicode(s_OrderStatus[order.Status])));
	tableWidget_Order->setItem(i, 6, new QTableWidgetItem(QString::number(order.Price)));
	tableWidget_Order->setItem(i, 7, new QTableWidgetItem(QString::number(order.Hands)));
	tableWidget_Order->setItem(i, 8, new QTableWidgetItem(QString::number(order.AvaHands)));
	tableWidget_Order->setItem(i, 9, new QTableWidgetItem(QString::number(order.TradedHands)));
	tableWidget_Order->setItem(i, 10, new QTableWidgetItem(order.InsertTime));
	tableWidget_Order->setItem(i, 11, new QTableWidgetItem(order.ExchangeID));
	tableWidget_Order->setItem(i, 12, new QTableWidgetItem(s_codec->toUnicode(order.StatusMsg)));
}

void wdMainWindow::TradeRsp(const wdTradeTicket *trade)
{
	static std::once_flag winner_flag;
	static QMap<char, const char *> s_mapTradeType, s_mapHedgeFlag;
	std::call_once(winner_flag, [&](){
		s_mapTradeType[THOST_FTDC_TRDT_SplitCombination] = "组合持仓拆分为单一持仓,初始化不应包含该类型的持仓";
		s_mapTradeType[THOST_FTDC_TRDT_Common] = "普通成交";
		s_mapTradeType[THOST_FTDC_TRDT_OptionsExecution] = "期权执行";
		s_mapTradeType[THOST_FTDC_TRDT_OTC] = "OTC成交";
		s_mapTradeType[THOST_FTDC_TRDT_EFPDerived] = "期转现衍生成交";
		s_mapTradeType[THOST_FTDC_TRDT_CombinationDerived] = "组合衍生成交";

		s_mapHedgeFlag[THOST_FTDC_HF_Speculation] = "投机";
		s_mapHedgeFlag[THOST_FTDC_HF_Arbitrage] = "套利";
		s_mapHedgeFlag[THOST_FTDC_HF_Hedge] = "套保";
	});

	int i = tableWidget_trade->rowCount();
	tableWidget_trade->insertRow(i);
	
	tableWidget_trade->setItem(i, 0, new QTableWidgetItem(trade->TradeID));
	tableWidget_trade->setItem(i, 1, new QTableWidgetItem(trade->OrderSysID));
	tableWidget_trade->setItem(i, 2, new QTableWidgetItem(trade->InstrumentID));
	tableWidget_trade->setItem(i, 3, new QTableWidgetItem(s_codec->toUnicode(s_Dir[trade->Dir])));
	tableWidget_trade->setItem(i, 4, new QTableWidgetItem(s_codec->toUnicode(s_Offset[trade->Offset])));
	tableWidget_trade->setItem(i, 5, new QTableWidgetItem(QString::number(trade->Price)));
	tableWidget_trade->setItem(i, 6, new QTableWidgetItem(QString::number(trade->Hands)));
	tableWidget_trade->setItem(i, 7, new QTableWidgetItem(s_codec->toUnicode(s_mapTradeType[trade->TradeType])));
	tableWidget_trade->setItem(i, 8, new QTableWidgetItem(trade->TradeTime));
	tableWidget_trade->setItem(i, 9, new QTableWidgetItem(trade->ExchangeID));
	tableWidget_trade->setItem(i, 10, new QTableWidgetItem(s_codec->toUnicode(s_mapHedgeFlag[trade->HedgeFlag])));
}

void wdMainWindow::PositionRsp(int i,const wdPosition &posi)
{
	if (tableWidget_position->rowCount() <= i)
		tableWidget_position->insertRow(i);
	tableWidget_position->setItem(i, 0, new QTableWidgetItem(posi.InstrumentID));
	tableWidget_position->setItem(i, 1, new QTableWidgetItem(s_codec->toUnicode(s_Dir[posi.Dir])));
	tableWidget_position->setItem(i, 2, new QTableWidgetItem(QString::number(posi.TPos)));
	tableWidget_position->setItem(i, 3, new QTableWidgetItem(QString::number(posi.APos)));
	tableWidget_position->setItem(i, 4, new QTableWidgetItem(QString::number(posi.PosAvgPrice)));
}