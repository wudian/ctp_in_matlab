#include "tcmarketmgr.h"

#include <QtCore/QTextStream>
#include <QMessageBox>
#include <QtXml/QDomDocument>

#include "../tcdefine.h"
#include "../service/tcsvcpack.h"
#include "tcstockmgr.h"
#include "tcmarketlistdlg.h"
#include "tcmarketinfodlg.h"
#include "tcmarketselectdlg.h"
#include "tcstockselectdlg.h"

#define MARKETS_XML_FILE "markets.xml"

tcMarketManager::tcMarketManager(const QDir &pPath)
{
	mPath = pPath;
}

tcMarketManager::~tcMarketManager()
{
	ClearAllMarkets();
}

bool tcMarketManager::LoadFromFile()
{
	ClearAllMarkets();

	QFileInfo fileinfo(mPath, MARKETS_XML_FILE);
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::ReadOnly)) {
		tcLogService::CreateLog(this, "Can not open markets file.");
		return false;
	}

	QDomDocument doc;
	if (! doc.setContent(&file, true)) {
		file.close();
		tcLogService::CreateLog(this, "Can not load markets file.");
		return false;
	}
	file.close();

	QDomElement syselement = doc.documentElement();
	//load market info
	QDomNode node = syselement.namedItem("markets");
	if (! node.isElement()) {
		tcLogService::CreateLog(this, "Markets file format error.");
		return false;
	}
	QDomElement marketselement = node.toElement();

	QDomElement element;
	element = marketselement.firstChildElement();
	while (! element.isNull()) {
		tcMarket *market = new tcMarket();
		if (! market->LoadFromXml(element)) {
			tcLogService::CreateLog(this, "Can not load market.");
			delete market;
			return false;
		}
		connect(market, SIGNAL(OnStocksModified()), this, SLOT(DoStocksModified()));
		mMarketList.append(market);
		element = element.nextSiblingElement();
	}

	return true;
}

bool tcMarketManager::SaveToFile()
{
	QFileInfo fileinfo(mPath, MARKETS_XML_FILE);
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::WriteOnly)) {
		tcLogService::CreateLog(this, "Can not open markets file.");
		return false;
	}

	QDomDocument doc;
	QDomElement syselement = doc.createElement(SYSTEM_NAME);
	doc.appendChild(syselement);

	//save markets info
	QDomElement marketselement = doc.createElement("markets");
	syselement.appendChild(marketselement);
	foreach(tcMarket *market, mMarketList) {
		QDomElement element = doc.createElement("market");
		marketselement.appendChild(element);
		if (! market->SaveToXml(doc, element)) {
			tcLogService::CreateLog(this, "Can not save market.");
			return false;
		}
	}

	QTextStream stream(&file);
	doc.save(stream, 4);
	file.close();
	return true;
}

tcMarket* tcMarketManager::GetMarket(QWidget *pParent)
{
	tcMarketSelectDialog dlg(pParent);
	if (! dlg.LoadMarketList(this)) {
		tcLogService::CreateLog(this, "can not load market list.");
		return NULL;
	}
	if (dlg.exec() != QDialog::Accepted) {
		return NULL;
	}
	int index = dlg.GetSelectedMarketIndex();
	return GetMarket(index);
}

bool tcMarketManager::EditMarketList(QWidget *pParent)
{
	tcMarketListDialog dlg(pParent);
	dlg.exec();
	if (! SaveToFile()) {
		tcLogService::CreateLog(this, "Error when save market manager.");
		return false;
	}
	tcStockManager *stockmanager = tcObjService::GetStockManager();
	if (! stockmanager->SaveToFile()) {
		tcLogService::CreateLog(this, "Error when save stock manager.");
		return false;
	}
	return true;
}

int tcMarketManager::GetMarketCount()
{
	return mMarketList.count();
}

tcMarket* tcMarketManager::AppendMarket(const QString &pName)
{
	tcMarket *market = new tcMarket();
	market->SetName(pName);
	connect(market, SIGNAL(OnStocksModified()), this, SLOT(DoStocksModified()));
	mMarketList.append(market);
	emit OnMarketsModified();
	return market;
}

tcMarket* tcMarketManager::AppendMarket(QWidget *pParent)
{
	tcMarketInfoDialog dlg(pParent);
	if (dlg.exec() != QDialog::Accepted) {
		return NULL;
	}
	tcMarket *market = new tcMarket();
	if (! dlg.SaveToMarket(market)) {
		delete market;
		tcLogService::CreateLog(this, "Error when save market info.");
		return NULL;
	}
	connect(market, SIGNAL(OnStocksModified()), this, SLOT(DoStocksModified()));
	mMarketList.append(market);
	emit OnMarketsModified();
	return market;
}

tcMarket* tcMarketManager::ModifyMarket(QWidget *pParent, int pIndex)
{
	tcMarket *market = GetMarket(pIndex);
	if (! market) {
		tcLogService::CreateLog(this, "Wrong market index.");
		return NULL;
	}
	tcMarketInfoDialog dlg(pParent);
	if (! dlg.LoadFromMarket(market)) {
		tcLogService::CreateLog(this, "Error when load market info.");
		return NULL;
	}
	if (dlg.exec() != QDialog::Accepted) {
		return NULL;
	}
	if (! dlg.SaveToMarket(market)) {
		tcLogService::CreateLog(this, "Error when save market info.");
		return NULL;
	}
	emit OnMarketsModified();
	return market;
}

bool tcMarketManager::RemoveMarket(QWidget *pParent, int pMarketIndex)
{
	if (pMarketIndex < 0 || pMarketIndex >= mMarketList.count()) {
		tcLogService::CreateLog(this, "Wrong market index.");
		return false;
	}
	if (QMessageBox::question(pParent, SYSTEM_NAME, tr("Are you sure to remove this market?"), QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Cancel) {
		return false;
	}
	tcMarket *market = mMarketList[pMarketIndex];
	mMarketList.removeAt(pMarketIndex);
	emit OnMarketsModified();
	return true;
}

bool tcMarketManager::SelectStock(QWidget *pParent, tcStockInfoList &pStockInfoList)
{
	tcStockSelectDialog dlg(pParent);
	if (dlg.exec() != QDialog::Accepted) {
		return false;
	}
	if (! dlg.GetSelectedStockInfoList(pStockInfoList)) {
		tcLogService::CreateLog(this, "Error when get selected stock list.");
		return false;
	}
	return true;
}

bool tcMarketManager::GetStockInfoList(int pMarketIndex, tcStockInfoList &pStockInfoList)
{
	if (pMarketIndex < 0) {	//get all market's stocks
		foreach (tcMarket *market, mMarketList) {
			if (! market->GetStockInfoList(pStockInfoList)) {
				tcLogService::CreateLog(this, "Error when get stock info list.");
				return false;
			}
		}
		return true;
	}
	if (pMarketIndex >=0 && pMarketIndex < mMarketList.count()) {
		tcMarket *market = mMarketList[pMarketIndex];
		if (! market->GetStockInfoList(pStockInfoList)) {
			tcLogService::CreateLog(this, "Error when get stock info list.");
			return false;
		}
		return true;
	}
	return false;
}

bool tcMarketManager::GetStockInfoListFilter(int pMarketIndex, tcStockInfoList &pStockInfoList, const QString &pStockCodeFilter, const QString &pStockNameFilter)
{
	if (pMarketIndex < 0) {	//get all market's stocks
		foreach (tcMarket *market, mMarketList) {
			if (! market->GetStockInfoListFilter(pStockInfoList, pStockCodeFilter, pStockNameFilter)) {
				tcLogService::CreateLog(this, "Error when get stock info list.");
				return false;
			}
		}
		return true;
	}
	if (pMarketIndex >=0 && pMarketIndex < mMarketList.count()) {
		tcMarket *market = mMarketList[pMarketIndex];
		if (! market->GetStockInfoListFilter(pStockInfoList, pStockCodeFilter, pStockNameFilter)) {
			tcLogService::CreateLog(this, "Error when get stock info list.");
			return false;
		}
		return true;
	}
	return false;
}

void tcMarketManager::ClearAllMarkets()
{
	foreach(tcMarket* market, mMarketList) {
		delete market;
	}
	mMarketList.clear();
}

void tcMarketManager::DoStocksModified()
{
	emit OnStocksModified((tcMarket*)sender());
}
