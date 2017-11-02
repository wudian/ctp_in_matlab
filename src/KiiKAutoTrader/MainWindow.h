#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

//主窗口类
#include <qobject.h>
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtimer.h>
#include <qlineedit.h>
#include <memory>
#include <qaction.h>
#include <qmenu.h>

enum wdConnectionStatus;
class TradeController;
class SelectShowMdWindow;
class SubscribingDialog;
class MarketDataController;
class MdTable;
struct wdTick;
struct wdConnectInfo;
struct wdKLine;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
private:
	void createStatusBur();
	void createMenu();
	//初始化连接控制器
	void initController();
private slots:
	//与timerForUpdateTimeLabel相联的槽函数
	void updateTime();				//每隔一秒更新时间

	void Md_Tick(wdTick *pTick);
	void Md_KLine(wdKLine *pKLine);

	void ConnectStatus(wdConnectInfo *info);

	//与disconnectButton相联的槽函数
	//void disconnect();				//断开连接,初始化与api相关的控制器
									//通知把表格内容清空

	//与selectShowMd动作相联的槽函数
	void showSelectMdWindow();		//展示对话框让使用者选择显示的合约

	//与writeToDB动作相联的槽函数
	void selectFileForWriter();		//展示对话框让使用者选择文件写入数据库

	//与showSubscribingAction动作相联的槽函数
	void showSubscribing();			//展示正在订阅的合约的对话框


private:
	//按钮和输入框
	QPushButton *connectMdButton;		//连行情
	QPushButton *connectTdButton;		//连交易
	QLineEdit *subscribeInstruments;	//订阅行情输入框
	QLineEdit *subscribePeriods;		//订阅的周期,默认tick
	QPushButton *subscribeButton;		//订阅行情按钮
	QLineEdit *unsubscribeInstruments;	//退订行情输入框
	QLineEdit *unsubscribePeriods;		//退订的周期,默认退订所有
	QPushButton *unsubscribeButton;		//退订行情按钮
	//QPushButton *disconnectMdButton;	//断开行情
	//QPushButton *disconnectTdButton;	//断开交易

	//状态栏的控件及相关
	QLabel *MdStatusLabel;
	QLabel *TdStatusLabel;
	/*///上期所时间
	QLabel *SHFETime;
	///大商所时间
	QLabel *DCETime;
	///郑商所时间
	QLabel *CZCETime;
	///中金所时间
	QLabel *FFEXTime;
	///能源中心时间
	QLabel *INETime;*/
	///本地时间
	QLabel *localTimeLabel;
	// 上期所、大商所、郑商所、中金所、能源中心的时间
	QLabel *ExchangeTimeLabel[5];
	QTimer *timerForUpdateTimeLabel;
	

	//对话框  这3个变量是不是static ？
	SelectShowMdWindow *sMdWindow;
	SubscribingDialog *subDialog;

	//表格
	MdTable *table;

	//菜单栏
	QMenu *selectMenu;
	QMenu *checkMenu;
	QMenu *editMenu;

	//动作
	QAction *selectShowMd;
	QAction *writeToDB;
	QAction *showSubscribingAction;
	QAction *editOnekeyAction;

	//控制器
	std::shared_ptr<MarketDataController> m_mdController;
	std::shared_ptr<TradeController> m_tdController;
};

#endif