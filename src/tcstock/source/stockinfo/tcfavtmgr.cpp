#include "tcfavtmgr.h"

#include <QtCore/QTextStream>
#include <QMessageBox>

#include "../tcdefine.h"
#include "../service/tcsvcpack.h"
#include "tcfavtinfodlg.h"
#include "tcfavtgrpinfodlg.h"

#define FAVOURITES_XML_FILE "favourites.xml"

tcFavouriteManager::tcFavouriteManager(const QDir &pPath)
{
	mPath = pPath;
	mModified = false;
}

tcFavouriteManager::~tcFavouriteManager()
{
	ClearAllFavouriteGroups();
}

bool tcFavouriteManager::LoadFromFile()
{
	ClearAllFavouriteGroups();

	QFileInfo fileinfo(mPath, FAVOURITES_XML_FILE);
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::ReadOnly)) {
		tcLogService::CreateLog(this, "Can not open favourites file.");
		return false;
	}

	QDomDocument doc;
	if (! doc.setContent(&file, true)) {
		file.close();
		tcLogService::CreateLog(this, "Can not load favourites file.");
		return false;
	}
	file.close();

	QDomElement syselement = doc.documentElement();
	//load favourite info
	QDomNode node = syselement.namedItem("favourites");
	if (! node.isElement()) {
		tcLogService::CreateLog(this, "Favourites file format error.");
		return false;
	}
	QDomElement favouriteselement = node.toElement();

	QDomElement element;
	element = favouriteselement.firstChildElement();
	while (! element.isNull()) {
		tcFavouriteGroup *group = new tcFavouriteGroup();
		if (! group->LoadFromXml(element)) {
			tcLogService::CreateLog(this, "Can not load favourite.");
			delete group;
			return false;
		}
		connect(group, SIGNAL(OnStocksModified()), this, SLOT(DoStocksModified()));
		mFavouriteGroupList.append(group);
		element = element.nextSiblingElement();
	}

	mModified = false;
	return true;
}

bool tcFavouriteManager::SaveToFile()
{
	if (! mModified) {
		return true;
	}

	QFileInfo fileinfo(mPath, FAVOURITES_XML_FILE);
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::WriteOnly)) {
		tcLogService::CreateLog(this, "Can not open favourites file.");
		return false;
	}

	QDomDocument doc;
	QDomElement syselement = doc.createElement(SYSTEM_NAME);
	doc.appendChild(syselement);

	//savefavourites info
	QDomElement favouriteselement = doc.createElement("favourites");
	syselement.appendChild(favouriteselement);
	foreach(tcFavouriteGroup *group, mFavouriteGroupList) {
		QDomElement element = doc.createElement("favourite");
		favouriteselement.appendChild(element);
		if (! group->SaveToXml(doc, element)) {
			tcLogService::CreateLog(this, "Can not save favourite.");
			return false;
		}
	}

	QTextStream stream(&file);
	doc.save(stream, 4);
	file.close();

	mModified = false;
	return true;
}

bool tcFavouriteManager::EditFavouriteList(QWidget *pParent, int pGroupIndex)
{
	tcFavouriteInfoDialog dlg(pParent, pGroupIndex);
	dlg.exec();
	if (! this->SaveToFile()) {
		tcLogService::CreateLog(this, "Error when save favourite file.");
		return false;
	}
	return true;
}

int tcFavouriteManager::GetFavouriteGroupCount()
{
	return mFavouriteGroupList.count();
}

tcFavouriteGroup* tcFavouriteManager::AppendFavouriteGroup(const QString &pName)
{
	tcFavouriteGroup *group = new tcFavouriteGroup();
	group->SetName(pName);
	connect(group, SIGNAL(OnStocksModified()), this, SLOT(DoStocksModified()));
	mFavouriteGroupList.append(group);
	mModified = true;
	emit OnFavouriteGroupModified();
	return group;
}

tcFavouriteGroup* tcFavouriteManager::AppendFavouriteGroup(QWidget *pParent)
{
	tcFavouriteGroupInfoDialog dlg(pParent);
	if (dlg.exec() != QDialog::Accepted) {
		return NULL;
	}
	tcFavouriteGroup *group = AppendFavouriteGroup("");
	if (! group) {
		tcLogService::CreateLog(this, "Error when create favourite group.");
		return NULL;
	}
	if (! dlg.SaveToFavouriteGroup(group)) {
		tcLogService::CreateLog(this, "Error when save favourite group info.");
		return NULL;
	}
	mModified = true;
	emit OnFavouriteGroupModified();
	return group;
}

tcFavouriteGroup* tcFavouriteManager::ModifyFavouriteGroup(QWidget *pParent, int pGroupIndex)
{
	if (pGroupIndex < 0 || pGroupIndex >= mFavouriteGroupList.count()) {
		tcLogService::CreateLog(this, "Wrong favourite group index.");
		return NULL;
	}
	tcFavouriteGroup *group = mFavouriteGroupList[pGroupIndex];
	tcFavouriteGroupInfoDialog dlg(pParent);
	if (! dlg.LoadFromFavouriteGroup(group)) {
		tcLogService::CreateLog(this, "Error when load favourite group info.");
		return NULL;
	}
	if (dlg.exec() != QDialog::Accepted) {
		return NULL;
	}
	if (! dlg.SaveToFavouriteGroup(group)) {
		tcLogService::CreateLog(this, "Error when save favourite group info.");
		return NULL;
	}
	mModified = true;
	emit OnFavouriteGroupModified();
	return group;
}

bool tcFavouriteManager::RemoveFavouriteGroup(QWidget *pParent, int pGroupIndex)
{
	if (pGroupIndex < 0 || pGroupIndex >= mFavouriteGroupList.count()) {
		tcLogService::CreateLog(this, "Wrong favourite group index.");
		return NULL;
	}
	if (QMessageBox::question(pParent, SYSTEM_NAME, tr("Are you sure to remove this favourite group?"), QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Cancel) {
		return false;
	}
	mFavouriteGroupList.removeAt(pGroupIndex);
	mModified = true;
	emit OnFavouriteGroupModified();
	return true;
}

bool tcFavouriteManager::GetStockInfoList(int pGroupIndex, tcStockInfoList &pStockInfoList)
{
	if (pGroupIndex < 0 || pGroupIndex >= mFavouriteGroupList.count()) {
		tcLogService::CreateLog(this, "Wrong favourite group index.");
		return NULL;
	}
	tcFavouriteGroup *group = mFavouriteGroupList[pGroupIndex];
	if (! group->GetStockInfoList(pStockInfoList)) {
		tcLogService::CreateLog(this, "Error when get stock info list.");
		return NULL;
	}
	return true;
}

bool tcFavouriteManager::GetStockInfoListFilter(int pGroupIndex, tcStockInfoList &pStockInfoList, const QString &pStockCodeFilter, const QString &pStockNameFilter)
{
	if (pGroupIndex < 0 || pGroupIndex >= mFavouriteGroupList.count()) {
		tcLogService::CreateLog(this, "Wrong favourite group index.");
		return NULL;
	}
	tcFavouriteGroup *group = mFavouriteGroupList[pGroupIndex];
	if (! group->GetStockInfoListFilter(pStockInfoList, pStockCodeFilter, pStockNameFilter)) {
		tcLogService::CreateLog(this, "Error when get stock info list.");
		return NULL;
	}
	return true;
}

void tcFavouriteManager::ClearAllFavouriteGroups()
{
	foreach (tcFavouriteGroup *group, mFavouriteGroupList) {
		delete group;
	}
	mFavouriteGroupList.clear();
	mModified = true;
}

void tcFavouriteManager::DoStocksModified()
{
	emit OnStocksModified((tcFavouriteGroup*)sender());
}
