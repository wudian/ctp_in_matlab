#include "tcstockmgr.h"

#include <QtCore/QTextStream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QMessageBox>

#include "../tcdefine.h"
#include "../service/tcsvcpack.h"
#include "tcstockinfodlg.h"
#include "tcstockdatainfodlg.h"

#define STOCKS_XML_FILE "stocks.xml"

tcStockManager::tcStockManager(const QDir &pPath)
{
	mPath = pPath;
	mStockDataCache = new tcStockDataCache(pPath);
	mModified = false;
}

tcStockManager::~tcStockManager()
{
	ClearAllStocks();
	delete mStockDataCache;
}

bool tcStockManager::LoadFromFile()
{
	ClearAllStocks();

	QFileInfo fileinfo(mPath, STOCKS_XML_FILE);
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::ReadOnly)) {
		tcLogService::CreateLog(this, "Can not open stocks file.");
		return false;
	}

	QDomDocument doc;
	if (! doc.setContent(&file, true)) {
		file.close();
		tcLogService::CreateLog(this, "Can not load stocks file.");
		return false;
	}
	file.close();

	QDomElement syselement = doc.documentElement();
	//load stock info
	QDomNode node = syselement.namedItem("stocks");
	if (! node.isElement()) {
		tcLogService::CreateLog(this, "Stocks file format error.");
		return false;
	}
	QDomElement stockselement = node.toElement();

	QDomElement element;
	element = stockselement.firstChildElement();
	while (! element.isNull()) {
		tcStock *stock = new tcStock(mStockDataCache);
		if (! stock->LoadFromXml(element)) {
			tcLogService::CreateLog(this, "Can not load stock.");
			delete stock;
			return false;
		}
		mStockMap.insert(stock->GetStockCode(), stock);
		element = element.nextSiblingElement();
	}
	
	mModified = false;
	return true;
}

bool tcStockManager::SaveToFile()
{
	if (! mModified) {
		return true;
	}

	QFileInfo fileinfo(mPath, STOCKS_XML_FILE);
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::WriteOnly)) {
		tcLogService::CreateLog(this, "Can not open stocks file.");
		return false;
	}

	QDomDocument doc;
	QDomElement syselement = doc.createElement(SYSTEM_NAME);
	doc.appendChild(syselement);

	//save stocks info
	QDomElement stockselement = doc.createElement("stocks");
	syselement.appendChild(stockselement);
	foreach (tcStock *stock, mStockMap) {
		QDomElement element = doc.createElement("stock");
		stockselement.appendChild(element);
		if (! stock->SaveToXml(doc, element)) {
			tcLogService::CreateLog(this, "Can not save stock.");
			return false;
		}
	}

	QTextStream stream(&file);
	doc.save(stream, 4);
	file.close();
	mModified = false;
	return true;
}

tcStock* tcStockManager::AppendStock(const QString &pStockCode, const QString &pStockName)
{
	if (mStockMap.contains(pStockCode) != NULL) {
		tcLogService::CreateLog(this, "This stock code already exists.");
		return NULL;
	}
	tcStock *stock = new tcStock(mStockDataCache);
	stock->SetStockCode(pStockCode);
	stock->SetStockName(pStockName);
	mStockMap.insert(pStockCode, stock);
	mModified = true;
	return stock;
}

tcStock* tcStockManager::AppendStock(QWidget *pParent)
{
	tcStockInfoDialog dlg(pParent, true);
	if (dlg.exec() != QDialog::Accepted) {
		return NULL;
	}
	tcStock *stock = new tcStock(mStockDataCache);
	if (! dlg.SaveToStock(stock)) {
		delete stock;
		tcLogService::CreateLog(this, "Error when save stock info.");
		return NULL;
	}
	if (mStockMap.contains(stock->GetStockCode()) != NULL) {
		delete stock;
		tcLogService::CreateLog(this, "This stock code already exists.");
		return NULL;
	}
	mStockMap.insert(stock->GetStockCode(), stock);
	mModified = true;
	return stock;
}

tcStock* tcStockManager::ModifyStock(QWidget *pParent, const QString &pStockCode)
{
	tcStock *stock = GetStockByCode(pStockCode);
	if (stock == NULL) {
		tcLogService::CreateLog(this, "Not found the stock.");
		return NULL;
	}
	tcStockInfoDialog dlg(pParent, false);
	if (! dlg.LoadFromStock(stock)) {
		tcLogService::CreateLog(this, "Error when load stock info.");
		return NULL;
	}
	if (dlg.exec() != QDialog::Accepted) {
		return NULL;
	}
	if (! dlg.SaveToStock(stock)) {	//the stock code will not be changed, so just update the object
		tcLogService::CreateLog(this, "Error when save stock info.");
		return NULL;
	}
	mModified = true;
	return stock;
}

bool tcStockManager::RemoveStock(const QString &pStockCode)
{
	tcStock *stock = GetStockByCode(pStockCode);
	if (stock == NULL) {
		tcLogService::CreateLog(this, "Not found the stock.");
		return false;
	}
	delete stock;
	mStockMap.remove(pStockCode);
	mModified = true;
	return true;
}

bool tcStockManager::RemoveStock(QWidget *pParent, const QString &pStockCode)
{
	tcStock *stock = GetStockByCode(pStockCode);
	if (stock == NULL) {
		tcLogService::CreateLog(this, "Not found the stock.");
		return false;
	}
	if (QMessageBox::question(pParent, SYSTEM_NAME, tr("Are you sure to remove this stock?"), QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Cancel) {
		return false;
	}
	delete stock;
	mStockMap.remove(pStockCode);
	mModified = true;
	return true;
}

bool tcStockManager::EditStockData(QWidget *pParent)
{
	tcStockDataInfoDialog dlg(pParent);
	dlg.exec();
	return mStockDataCache->SaveAllStockData();
}

void tcStockManager::ClearAllStocks()
{
	foreach (tcStock *stock, mStockMap) {
		delete stock;
	}
	mStockMap.clear();
	mModified = true;
}

#ifdef _DEBUG
bool tcStockManager::Test()
{
	ClearAllStocks();
	tcStock *stock;
	stock = AppendStock("111", "111name");
	if (! stock) {
		tcLogService::CreateLog(this, "Error when append stock 111.");
		return false;
	}
	stock = AppendStock("222", "222name");
	if (! stock) {
		tcLogService::CreateLog(this, "Error when append stock 222.");
		return false;
	}
	stock = AppendStock("222", "222 other name");
	if (stock) {
		tcLogService::CreateLog(this, "Error, this stock shouldn't be append.");
		return false;
	}
	stock = GetStockByCode("222");
	if (! stock) {
		tcLogService::CreateLog(this, "Error when get stock by code.");
		return false;
	}
	if (stock->GetStockName() != "222name") {
		tcLogService::CreateLog(this, "Wrong stock name.");
		return false;
	}
	if (! SaveToFile()) {
		tcLogService::CreateLog(this, "Error when save to file.");
		return false;
	}

	ClearAllStocks();
	if (! LoadFromFile()) {
		tcLogService::CreateLog(this, "Error when load from file.");
		return false;
	}
	stock = GetStockByCode("222");
	if (! stock) {
		tcLogService::CreateLog(this, "Error when get stock by code.");
		return false;
	}
	if (stock->GetStockName() != "222name") {
		tcLogService::CreateLog(this, "Wrong stock name.");
		return false;
	}
	return true;
}
#endif
