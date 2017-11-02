#include "tcmarket.h"

#include <QtCore/QTextStream>
#include <QMessageBox>

#include "../tcdefine.h"
#include "../service/tcsvcpack.h"
#include "tcstockmgr.h"

#define STOCKS_XML_FILE "stocks.xml"

tcMarket::tcMarket()
{
}

tcMarket::~tcMarket()
{
}

bool tcMarket::LoadFromXml(const QDomElement &pElement)
{
	mStockInfoList.clear();

	mName = pElement.attribute("Name");
	mDescription = pElement.attribute("Description");

	mStockInfoList.LoadFromXml(pElement);
	return true;
}

bool tcMarket::SaveToXml(QDomDocument &pDoc, QDomElement &pElement)
{
	pElement.setAttribute("Name", mName);
	pElement.setAttribute("Description", mDescription);

	mStockInfoList.SaveToXml(pDoc, pElement);
	return true;
}

bool tcMarket::AppendStock(const QString &pStockCode, const QString &pStockName, tcStockInfo &pStockInfo)
{
	tcStockManager *stockmanager = tcObjService::GetStockManager();
	tcStock *stock = stockmanager->AppendStock(pStockCode, pStockName);
	if (stock == NULL) {
		tcLogService::CreateLog(this, "Error when append stock to stock manager.");
		return false;
	}
	tcStockInfo stockinfo(stock->GetStockCode());
	mStockInfoList.append(stockinfo);
	pStockInfo = stockinfo;
	emit OnStocksModified();
	return true;
}

bool tcMarket::AppendStock(QWidget *pParent, tcStockInfo &pStockInfo)
{
	tcStockManager *stockmanager = tcObjService::GetStockManager();
	tcStock *stock = stockmanager->AppendStock(pParent);
	if (stock == NULL) {
		return false;
	}
	tcStockInfo stockinfo(stock->GetStockCode());
	mStockInfoList.append(stockinfo);
	pStockInfo = stockinfo;
	emit OnStocksModified();
	return true;
}

bool tcMarket::ModifyStock(QWidget *pParent, int pStockIndex, tcStockInfo &pStockInfo)
{
	if (pStockIndex < 0 || pStockIndex >= mStockInfoList.count()) {
		tcLogService::CreateLog(this, "Wrong stock index.");
		return false;
	}
	tcStockInfo stockinfo = mStockInfoList[pStockIndex];
	tcStockManager *stockmanager = tcObjService::GetStockManager();
	tcStock *stock = stockmanager->ModifyStock(pParent, stockinfo.GetStockCode());
	if (stock == NULL) {
		return false;
	}
	pStockInfo = stockinfo;
	emit OnStocksModified();
	return true;
}

bool tcMarket::RemoveStock(QWidget *pParent, int pStockIndex)
{
	if (pStockIndex < 0 || pStockIndex >= mStockInfoList.count()) {
		tcLogService::CreateLog(this, "Wrong stock index.");
		return false;
	}
	tcStockInfo stockinfo = mStockInfoList[pStockIndex];
	tcStockManager *stockmanager = tcObjService::GetStockManager();
	if (stockmanager->GetStockByCode(stockinfo.GetStockCode())) {	//if the stock exists in stock manager, remove it
		if (! stockmanager->RemoveStock(pParent, stockinfo.GetStockCode())) {
			return false;
		}
	}
	else {	//the stock not exists in the stock manager
		tcLogService::CreateLog(this, "Not found the stock in the stock manager, but still remove it from this market.");
	}
	mStockInfoList.removeAt(pStockIndex);
	emit OnStocksModified();
	return true;
}

void tcMarket::RemoveAllStocks()
{
	tcStockManager *stockmanager = tcObjService::GetStockManager();
	foreach (tcStockInfo stockinfo, mStockInfoList) {
		if (! stockmanager->RemoveStock(stockinfo.GetStockCode())) {
			//do nothing
		}
	}
	mStockInfoList.clear();
	emit OnStocksModified();
}

bool tcMarket::ImportFromCSV(const QString &pFileName, int &pSuccCount, int &pFailCount)
{
	pSuccCount = 0;
	pFailCount = 0;

	QFile file(pFileName);
	if (! file.open(QFile::ReadOnly)) {
		tcLogService::CreateLog(this, "Error when open file.");
		return false;
	}
	
	this->RemoveAllStocks();

	QTextStream stream(&file);
	QString linestr;
	QStringList strlist;
	tcStockInfo stockinfo;
	while (! stream.atEnd()) {
		linestr = stream.readLine();
		strlist = linestr.split(",");
		if (strlist.count() < 2) {
			continue;
		}
		if (! this->AppendStock(strlist[0], strlist[1], stockinfo)) {
			//do nothing
			pFailCount++;
		}
		else {
			pSuccCount++;
		}
	}

	file.close();
	return true;
}

bool tcMarket::ExportToCSV(const QString &pFileName, int &pSuccCount, int &pFailCount)
{
	//TODO: implement this 
	return false;
}

bool tcMarket::GetStockInfoList(tcStockInfoList &pStockInfoList)
{
	pStockInfoList = mStockInfoList;
	return true;
}

bool tcMarket::GetStockInfoListFilter(tcStockInfoList &pStockInfoList, const QString &pStockCodeFilter, const QString &pStockNameFilter)
{
	foreach (tcStockInfo stockinfo, mStockInfoList) {
		if (pStockCodeFilter.length() > 0 && stockinfo.GetStockCode().indexOf(pStockCodeFilter) < 0) {
			continue;
		}
		if (pStockNameFilter.length() > 0 && stockinfo->GetStockName().indexOf(pStockNameFilter) < 0) {
			continue;
		}
		pStockInfoList.append(stockinfo);
	}
	return true;
}
