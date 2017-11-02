#ifndef _TRADE_CONTROLLER_H_
#define _TRADE_CONTROLLER_H_

#include <vector>
#include <qobject.h>
#include <QMap>
#include <QSqlDatabase>

enum wdConnectionStatus;
class wdMainWindow;
#include "TradeData.h"

#define INVALID_DIFF_SECONDS 9999

class TradeController : public QObject
{
	Q_OBJECT
public:
	TradeController(wdMainWindow &);
	virtual ~TradeController();

	const int *get_differenceSeconds() const { return m_differenceSeconds; }

private:
	void OnConnect(wdConnectInfo *info);
	void OnError(const char *);
	void OnInstrument(std::map<std::string, wdInstrument> *);
	void OnOrder(wdOrder *);
	void OnTrade(wdTradeTicket *);
	void OnPosition(wdPosition *);

	// 上期所、大商所、郑商所、中金所、能源中心的时间，与本地时间相差的秒数
	int m_differenceSeconds[5];
	QSqlDatabase db;

	QMap<wdOrderKey, int> m_mapOrder_No;
	QMap<wdOrderKey, wdOrder> m_mapOrders;

	QMap<wdPositionKey, int> m_mapPosition_No;
	QMap<wdPositionKey, wdPosition> m_mapPositions;

	wdMainWindow &m_ui;

	QMap<int, const wdOrder*>		m_mapNo_Order;		//第几行，显示哪个合约
	QMap<int, const wdPosition*>	m_mapNo_Position;	//第几行，显示的哪个持仓
	QMap<std::string, std::string>	m_mapInst_Exe;		//合约对应的交易所

public slots:
	void connectTdServer();
	void SendOrder(int = -1, int = -1); // 开仓、平仓
	void CancelOrder(int, int); // 撤单
	

signals:
	void connect_status(wdConnectInfo *info);	
	void error_msg(const char *);
	void instruments_rsp(const std::map<std::string, wdInstrument> *);
	void order_rsp(int, const wdOrder &);
	void trade_rsp(const wdTradeTicket *);
	void position_rsp(int, const wdPosition &);
};

#endif // !_TRADE_CONTROLLER_H_