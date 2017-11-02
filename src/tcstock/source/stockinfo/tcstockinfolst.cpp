#include "tcstockinfolst.h"

#include "../service/tcsvcpack.h"
#include "tcmarket.h"
#include "tcmarketmgr.h"
#include "tcfavtmgr.h"

tcStockInfoList::tcStockInfoList()
	: QList<tcStockInfo>()
{
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();
	connect(marketmanager, SIGNAL(OnMarketsModified()), this, SLOT(DoMarketManagerMarketsModified()));
	connect(marketmanager, SIGNAL(OnStocksModified(tcMarket *)), this, SLOT(DoMarketManagerStocksModified(tcMarket *)));
	tcFavouriteManager *favouritemanager = tcObjService::GetFavouriteManager();
	connect(favouritemanager, SIGNAL(OnFavouriteGroupModified()), this, SLOT(DoFavouriteManagerFavouriteGroupModified()));
	connect(favouritemanager, SIGNAL(OnStocksModified(tcFavouriteGroup *)), this, SLOT(DoFavouriteManagerStocksModified(tcFavouriteGroup *)));
}

tcStockInfoList::tcStockInfoList(const tcStockInfoList &pStockInfoList)
	: QList<tcStockInfo>(pStockInfoList)
{
}

bool tcStockInfoList::LoadFromXml(const QDomElement &pElement)
{
	this->clear();

	QDomNode node = pElement.namedItem("stocks");
	if (! node.isElement()) {
		return false;
	}
	QDomElement stockselement = node.toElement();

	QDomElement element;
	element = stockselement.firstChildElement();
	while (! element.isNull()) {
		tcStockInfo stockinfo(element.attribute("StockCode"));
		this->append(stockinfo);
		element = element.nextSiblingElement();
	}
	return true;
}

bool tcStockInfoList::SaveToXml(QDomDocument &pDoc, QDomElement &pElement)
{
	QDomElement stockselement = pDoc.createElement("stocks");
	pElement.appendChild(stockselement);
	foreach (tcStockInfo stockinfo, *this) {
		QDomElement element = pDoc.createElement("info");
		stockselement.appendChild(element);
		element.setAttribute("StockCode", stockinfo.GetStockCode());
	}
	return true;
}

bool tcStockInfoList::GetGroupList(QStringList &pStringList)
{
	pStringList.clear();

	int i;
	tcFavouriteManager *favouritemanager = tcObjService::GetFavouriteManager();
	for (i=0; i<favouritemanager->GetFavouriteGroupCount(); i++) {
		tcFavouriteGroup *group = favouritemanager->GetFavouriteGroup(i);
		pStringList.append(group->GetName());
	}

	tcMarketManager *marketmanager = tcObjService::GetMarketManager();
	for (i=0; i<marketmanager->GetMarketCount(); i++) {
		tcMarket *market = marketmanager->GetMarket(i);
		pStringList.append(market->GetName());
	}
	return true;
}

bool tcStockInfoList::ReloadFromGroup(int pGroupIndex)
{
	this->clear();

	tcFavouriteManager *favouritemanager = tcObjService::GetFavouriteManager();
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();

	if (pGroupIndex >= 0 && pGroupIndex < favouritemanager->GetFavouriteGroupCount()) {
		tcFavouriteGroup *group = favouritemanager->GetFavouriteGroup(pGroupIndex);
		Q_ASSERT(group);
		return group->GetStockInfoList(*this);
	}
	else if (pGroupIndex >=favouritemanager->GetFavouriteGroupCount() && pGroupIndex < marketmanager->GetMarketCount() + favouritemanager->GetFavouriteGroupCount()) {
		tcMarket *market = marketmanager->GetMarket(pGroupIndex - favouritemanager->GetFavouriteGroupCount());
		Q_ASSERT(market);
		return market->GetStockInfoList(*this);
	}
	else {
		tcLogService::CreateLog(this, "Wrong group index.");
	}
	return false;
}

bool tcStockInfoList::ReloadFromGroupFilter(int pGroupIndex, const QString &pStockCodeFilter, const QString &pStockNameFilter)
{
	this->clear();

	tcFavouriteManager *favouritemanager = tcObjService::GetFavouriteManager();
	tcMarketManager *marketmanager = tcObjService::GetMarketManager();

	if (pGroupIndex >= 0 && pGroupIndex < favouritemanager->GetFavouriteGroupCount()) {
		tcFavouriteGroup *group = favouritemanager->GetFavouriteGroup(pGroupIndex);
		Q_ASSERT(group);
		return group->GetStockInfoListFilter(*this, pStockCodeFilter, pStockNameFilter);
	}
	else if (pGroupIndex >=favouritemanager->GetFavouriteGroupCount() && pGroupIndex < marketmanager->GetMarketCount() + favouritemanager->GetFavouriteGroupCount()) {
		tcMarket *market = marketmanager->GetMarket(pGroupIndex - favouritemanager->GetFavouriteGroupCount());
		Q_ASSERT(market);
		return market->GetStockInfoListFilter(*this, pStockCodeFilter, pStockNameFilter);
	}
	return false;
}

tcStockInfoList& tcStockInfoList::operator=(const tcStockInfoList &pStockInfoList)
{
	this->clear();
	foreach (tcStockInfo stockinfo, pStockInfoList) {
		this->append(stockinfo);
	}
	return *this;
}

void tcStockInfoList::DoMarketManagerMarketsModified()
{
	emit OnGroupListNeedReload();
}

void tcStockInfoList::DoMarketManagerStocksModified(tcMarket *pMarket)
{
	emit OnStockListNeedReload();
}

void tcStockInfoList::DoFavouriteManagerFavouriteGroupModified()
{
	emit OnGroupListNeedReload();
}

void tcStockInfoList::DoFavouriteManagerStocksModified(tcFavouriteGroup *pFavouriteGroup)
{
	emit OnStockListNeedReload();
}
