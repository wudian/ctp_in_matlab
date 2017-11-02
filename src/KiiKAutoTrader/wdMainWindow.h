#ifndef WDMAINWINDOW_H
#define WDMAINWINDOW_H

#include <memory>
#include <vector>
#include <qmainwindow.h>
#include <qlabel.h>
#include "ui_wdMainWindow.h"
#include "TradeData.h"

enum wdConnectionStatus;
class TradeController;
class SelectShowMdWindow;
class SubscribingDialog;
class MarketDataController;
class MdTable;
struct wdTick;
struct wdKLine;

class wdMainWindow : public QMainWindow, public Ui_MainWindow
{
	Q_OBJECT

public:
	wdMainWindow(QWidget *parent = 0);
	~wdMainWindow() {};

private:
	void createStatusBur();

	//初始化连接控制器
	void initController();

private slots:

	//与timerForUpdateTimeLabel相联的槽函数
	void updateTime();				//每隔一秒更新时间

	void Md_Tick(int, wdTick *);
	void Md_KLine(int, wdKLine *);

	void ConnectStatus(wdConnectInfo *info);
	void OnError(const char *);
	void InstrumentsRsp(const std::map<std::string, wdInstrument> *);
	void OrderRsp(int, const wdOrder &);
	void TradeRsp(const wdTradeTicket *);
	void PositionRsp(int ,const wdPosition &);

private:
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


	//控制器
	std::shared_ptr<MarketDataController> m_mdController;
	std::shared_ptr<TradeController> m_tdController;
};

#endif // WDMAINWINDOW_H
