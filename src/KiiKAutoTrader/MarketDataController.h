#ifndef _MARKET_DATA_CONTROLLER_H_
#define _MARKET_DATA_CONTROLLER_H_

#include <qobject.h>
#include <qlineedit.h>
#include <qmap>

enum wdConnectionStatus;
struct wdTick;
struct wdKLine;
struct wdConnectInfo;
class wdMainWindow;

struct wdMdKey
{
	char	InstrumentID[31];
	char	Period[5];
	wdMdKey(const char *inst, const char *per); 
	bool operator<(const wdMdKey &) const;
};

class MarketDataController : public QObject
{
	Q_OBJECT
public:
	MarketDataController(wdMainWindow &);
	
private:
	void OnRtnDepthMarketData(wdTick *);
	void OnRtnDepthMarketData_KLine(wdKLine *);

	wdMainWindow &m_ui;
	bool m_isHistory;

	QMap<wdMdKey, int>	m_tick;
	QMap<wdMdKey, int>	m_kline;

public slots:
	//响应窗口部件的槽
	void connectMdServer();
	void subscribe();
	void unsubscribe();
	void CheckIsHistory(int s) { m_isHistory = (s != Qt::Unchecked); };

signals:
	//通知窗口部件的信号
	void md_status(wdConnectionStatus step, const char *errMsg = nullptr);
	void md_tick(int, wdTick *);
	void md_kline(int, wdKLine *);
};

#endif