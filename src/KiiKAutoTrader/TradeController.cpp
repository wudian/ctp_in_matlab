#include "TradeController.h"
#include <string>
#include <qtime>
#include <QSqlQuery>
#include <QVariant>
#include "wdMainWindow.h"
#include "QuantBoxApi.h"

TradeController::TradeController(wdMainWindow &ui) : m_ui(ui) 
{
	db = QSqlDatabase::addDatabase("QSQLITE");

	for (int i = 0; i < 5; ++i)
		m_differenceSeconds[i] = INVALID_DIFF_SECONDS;
	CTP_RegOnConnect(std::bind(&TradeController::OnConnect, this, std::placeholders::_1));
	CTP_RegOnRspError(std::bind(&TradeController::OnError, this, std::placeholders::_1));
	CTP_RegOnRspQryInstrument(std::bind(&TradeController::OnInstrument, this, std::placeholders::_1));

	CTP_RegOnRspQryOrder(std::bind(&TradeController::OnOrder, this, std::placeholders::_1));
	CTP_RegOnRspQryTrade(std::bind(&TradeController::OnTrade, this, std::placeholders::_1));
	CTP_RegOnRspQryInvestorPosition(std::bind(&TradeController::OnPosition, this, std::placeholders::_1));
}

TradeController::~TradeController()
{
	db.close();
}

void TradeController::OnConnect(wdConnectInfo *info)
{
	if (info->type == E_TD && info->status == E_logined) {
		QTime LoginTime, SHFETime, DCETime, CZCETime, FFEXTime, INETime;

		/*if (QString(info->loginField.LoginTime)[0] != '-')
		LoginTime = QTime::fromString(info->loginField.LoginTime);
		else
		*/LoginTime = QTime::currentTime();

		if (QString(info->loginField.SHFETime)[0] != '-') {
			SHFETime = QTime::fromString(info->loginField.SHFETime);
			m_differenceSeconds[0] = SHFETime.second() - LoginTime.second();
		}
		else {
			m_differenceSeconds[0] = INVALID_DIFF_SECONDS;
		}

		if (QString(info->loginField.DCETime)[0] != '-') {
			DCETime = QTime::fromString(info->loginField.DCETime);
			m_differenceSeconds[1] = DCETime.second() - LoginTime.second();
		}
		else {
			m_differenceSeconds[1] = INVALID_DIFF_SECONDS;
		}

		if (QString(info->loginField.CZCETime)[0] != '-') {
			CZCETime = QTime::fromString(info->loginField.CZCETime);
			m_differenceSeconds[2] = CZCETime.second() - LoginTime.second();
		}
		else {
			m_differenceSeconds[2] = INVALID_DIFF_SECONDS;
		}

		if (QString(info->loginField.FFEXTime)[0] != '-') {
			FFEXTime = QTime::fromString(info->loginField.FFEXTime);
			m_differenceSeconds[3] = FFEXTime.second() - LoginTime.second();
		}
		else {
			m_differenceSeconds[3] = INVALID_DIFF_SECONDS;
		}

		if (QString(info->loginField.INETime)[0] != '-') {
			INETime = QTime::fromString(info->loginField.INETime);
			m_differenceSeconds[4] = INETime.second() - LoginTime.second();
		}
		else {
			m_differenceSeconds[4] = INVALID_DIFF_SECONDS;
		}	

		db.setDatabaseName("F:\\CTP-MATLAB\\src\\KiiKAutoTrader\\LocalDatabase\\TradeInfo.db");
		if (!db.open())
			emit error_msg("fail to open tdDB");
	}
	
	emit connect_status(info);
}

void TradeController::SendOrder(int row, int column)
{
	if (row == -1 && column == -1) {
		QString Instrument = m_ui.lineEdit_5->text();
		double Price = m_ui.doubleSpinBox->value();
		int Volume = m_ui.spinBox->value();
		wdDirectionType Direction = (wdDirectionType)m_ui.comboBox->currentIndex();
		wdOffsetFlagType OffsetFlag = (wdOffsetFlagType)m_ui.comboBox_2->currentIndex();
		TD_SendLimitOrder(Instrument.toStdString().c_str(), Price, Volume, Direction, OffsetFlag);
	}
	else {
		const wdPosition *pPosition = m_mapNo_Position[row];
		// 暂未考虑隔夜仓
		if (m_mapInst_Exe[pPosition->InstrumentID] == "SHFE") // 上期所 平今仓
			TD_CancelOrder(pPosition->InstrumentID, pPosition->Dir, E_CloseToday);
		else // 其他交易所平仓
			TD_CancelOrder(pPosition->InstrumentID, pPosition->Dir, E_Close);
	}
}

void TradeController::CancelOrder(int row, int column)
{
	const wdOrder *pOrder = m_mapNo_Order[row];
	if (pOrder->Status != E_PartTradedNotQueueing && pOrder->Status != E_AllTraded && pOrder->Status != E_Canceled) {
		TD_CancelOrder(*pOrder);
	}
}


void TradeController::OnError(const char *msg)
{
	emit error_msg(msg);
}

void TradeController::OnInstrument(std::map<std::string, wdInstrument> *mapInst)
{
	emit instruments_rsp(mapInst);
	for (auto it = mapInst->begin(); it != mapInst->end(); ++it) {
		m_mapInst_Exe[it->first] = it->second.ExchangeID;
	}
}

void TradeController::OnTrade(wdTradeTicket *tradeTick)
{
	emit trade_rsp(tradeTick);
}

void TradeController::OnPosition(wdPosition *posi)
{
	wdPositionKey key(posi->InstrumentID, posi->Dir);
	if (!m_mapPosition_No.contains(key))
		m_mapPosition_No[key] = m_mapPosition_No.size();
	m_mapPositions[key] = *posi;
	emit position_rsp(m_mapPosition_No[key], m_mapPositions[key]);
	m_mapNo_Position[m_mapPosition_No[key]] = &m_mapPositions[key];
}

void TradeController::OnOrder(wdOrder *order)
{
	if (nullptr != order) {
		wdOrderKey key(order->FrontID, order->SessionID, order->OrderRef);
		if (!m_mapOrder_No.contains(key))
			m_mapOrder_No[key] = m_mapOrder_No.size();
		m_mapOrders[key] = *order;
		emit order_rsp(m_mapOrder_No[key], m_mapOrders[key]);
		m_mapNo_Order[m_mapOrder_No[key]] = &m_mapOrders[key];
		return;
	}
		
	m_mapOrder_No.clear();
	m_mapOrders.clear();
	int i = 0;
	QSqlQuery query;
	query.exec(QString("select * from %1;").arg("T_Order"));
	while (query.next()) {			
		wdOrder o;
		o.FrontID = query.value(0).toInt();
		o.SessionID = query.value(1).toInt();
		strcpy_s(o.OrderRef, query.value(2).toString().toStdString().c_str());
		wdOrderKey key(o.FrontID, o.SessionID, o.OrderRef);
		strcpy_s(o.OrderSysID, query.value(3).toString().toStdString().c_str());
		o.Type = (wdOrderType)query.value(4).toInt();
		strcpy_s(o.InstrumentID, query.value(5).toString().toStdString().c_str());
		o.Dir = (wdDirectionType)query.value(6).toInt();
		o.Offset = (wdOffsetFlagType)query.value(7).toInt();
		o.Status = (wdOrderStatus)query.value(8).toInt();
		o.Price = query.value(9).toDouble();
		o.Hands = query.value(10).toInt();
		o.AvaHands = query.value(11).toInt();
		o.TradedHands = query.value(12).toInt();
		strcpy_s(o.InsertTime, query.value(13).toString().toStdString().c_str());
		strcpy_s(o.StatusMsg, query.value(14).toString().toStdString().c_str());
		strcpy_s(o.ExchangeID, query.value(15).toString().toStdString().c_str());

		m_mapOrder_No[key] = i++;
		m_mapOrders[key] = o;
		emit order_rsp(m_mapOrder_No[key], m_mapOrders[key]);
		m_mapNo_Order[m_mapOrder_No[key]] = &m_mapOrders[key];
	}
}

void TradeController::connectTdServer() 
{
	TD_Connect();
}