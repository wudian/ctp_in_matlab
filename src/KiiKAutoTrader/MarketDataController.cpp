#include "MarketDataController.h"
#include <functional>
#include "wdMainWindow.h"
#include "QuantBoxApi.h"

wdMdKey::wdMdKey(const char *inst, const char *per)
{
	strcpy_s(InstrumentID, inst);
	strcpy_s(Period, per);
}

bool wdMdKey::operator<(const wdMdKey &o) const
{
	int i;
	if ((i = strcmp(InstrumentID, o.InstrumentID)) == 0) {
		return strcmp(Period, o.Period) < 0;
	}
	else {
		return i < 0;
	}
}

MarketDataController::MarketDataController(wdMainWindow &ui) : m_ui(ui), m_isHistory(false) {
	CTP_RegOnRtnDepthMarketData_Tick(std::bind(&MarketDataController::OnRtnDepthMarketData, this, std::placeholders::_1));
	CTP_RegOnRtnDepthMarketData_KLine(std::bind(&MarketDataController::OnRtnDepthMarketData_KLine, this, std::placeholders::_1));
}


/*************************************槽函数***********************************************/

void MarketDataController::OnRtnDepthMarketData(wdTick *pTick)
{
	wdMdKey key(pTick->InstrumentID, "tick");
	if (!m_tick.contains(key)) 
		m_tick[key] = m_tick.size();
	emit md_tick(m_tick[key], pTick);
}

void MarketDataController::OnRtnDepthMarketData_KLine(wdKLine *pKLine)
{
	wdMdKey key(pKLine->InstrumentID, pKLine->Period);
	if (!m_kline.contains(key))
		m_kline[key] = m_kline.size();
	emit md_kline(m_kline[key], pKLine);
}

void MarketDataController::connectMdServer()
{
	MD_Connect();
}

void MarketDataController::subscribe()
{
	//从文本框获取输入
	QString &instruments = m_ui.lineEdit_insts->text();
	QString periods = m_ui.lineEdit_periods->text();
	if (periods.isEmpty())
		periods = "tick";
	if (m_isHistory)
		MD_SubscribeHistory(m_ui.lineEdit_beginTime->text().toStdString().c_str(), m_ui.lineEdit_endTime->text().toStdString().c_str(), instruments.toStdString().c_str(), periods.toStdString().c_str());
	else
		MD_Subscribe(instruments.toStdString().c_str(), periods.toStdString().c_str());

}

void MarketDataController::unsubscribe()
{
	//从文本框获取输入
	QString &instruments = m_ui.lineEdit_insts->text();
	QString periods = m_ui.lineEdit_periods->text();
	if (periods.isEmpty())
		periods = "all";
	if (!m_isHistory)
		MD_Unsubscribe(instruments.toStdString().c_str(), periods.toStdString().c_str());
}