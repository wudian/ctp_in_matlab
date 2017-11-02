#include "tccfgsvc.h"

#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>

#include "../tcdefine.h"
#include "tclogsvc.h"

#define CONFIG_XML_FILE "config.xml"

tcCfgService* tcCfgService::mThis = NULL;

tcConfigItem::tcConfigItem(const QString &pClassName)
{
	mClassName = pClassName;
}

bool tcConfigItem::LoadFromXml(const QDomElement &pElement)
{
	QDomElement element;
	QString key, value;
	element = pElement.firstChildElement();
	while (! element.isNull()) {
		key = element.attribute("key");
		value = element.attribute("value");
		mKeyList.append(key);
		mValueList.append(value);
		element = element.nextSiblingElement();
	}
	return true;
}

bool tcConfigItem::SaveToXml(QDomDocument &pDoc, QDomElement &pElement)
{
	int i=0;
	foreach (QString key, mKeyList) {
		QDomElement element = pDoc.createElement("item");
		pElement.appendChild(element);
		element.setAttribute("key", key);
		element.setAttribute("value", mValueList[i]);
		i++;
	}
	return true;
}

QString tcConfigItem::GetAttribute(const QString &pKey, const QString &pDefaultValue)
{
	int i = 0;
	foreach (QString key, mKeyList) {
		if (key == pKey) {
			return mValueList[i];
		}
		i++;
	}
	mKeyList.append(pKey);
	mValueList.append(pDefaultValue);
	return pDefaultValue;
}

void tcConfigItem::SetAttribute(const QString &pKey, const QString &pValue)
{
	int i = 0;
	foreach (QString key, mKeyList) {
		if (key == pKey) {
			mValueList[i] = pValue;
			return;
		}
		i++;
	}
	mKeyList.append(pKey);
	mValueList.append(pValue);
}

QString tcConfigItem::GetClassName()
{
	return mClassName;
}

bool tcCfgService::Initialize(int argc, char* argv[])
{
	Q_ASSERT(! mThis);
	mThis = new tcCfgService(argc, argv);
	return true;
}

bool tcCfgService::Finalize()
{
	Q_ASSERT(mThis);
	delete mThis;
	mThis = NULL;
	return true;
}

QString tcCfgService::GetAttribute(QObject *pObject, const QString &pKey, const QString &pDefaultValue)
{
	Q_ASSERT(mThis);
	tcConfigItem *item = mThis->GetConfigItem(pObject->metaObject()->className());
	Q_ASSERT(item);
	return item->GetAttribute(pKey, pDefaultValue);
}

void tcCfgService::SetAttribute(QObject *pObject, const QString &pKey, const QString &pValue)
{
	Q_ASSERT(mThis);
	tcConfigItem *item = mThis->GetConfigItem(pObject->metaObject()->className());
	Q_ASSERT(item);
	item->SetAttribute(pKey, pValue);
}

QString tcCfgService::GetGlobalAttribute(const QString &pKey, const QString &pDefaultValue)
{
	return GetAttribute(mThis, pKey, pDefaultValue);
}

tcCfgService::tcCfgService(int argc, char* argv[])
{
	QFileInfo fileinfo(argv[0]);
	mPath = fileinfo.absolutePath();
	if (! LoadFromFile()) {
		tcLogService::CreateLog(this, "Error when load configs.");
	}
}

tcCfgService::~tcCfgService()
{
	if (! SaveToFile()) {
		tcLogService::CreateLog(this, "Error when save configs.");
	}
	ClearAllConfigItems();
}

tcConfigItem* tcCfgService::GetConfigItem(const QString &pClassName)
{
	tcConfigItem *item;
	if (mConfigMap.contains(pClassName)) {
		item = mConfigMap[pClassName];
	}
	else {
		item = new tcConfigItem(pClassName);
		mConfigMap.insert(pClassName, item);
	}
	return item;
}

bool tcCfgService::LoadFromFile()
{
	ClearAllConfigItems();

	QFileInfo fileinfo(mPath, CONFIG_XML_FILE);
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::ReadOnly)) {
		tcLogService::CreateLog(this, "Can not open config file.");
		return false;
	}

	QDomDocument doc;
	if (! doc.setContent(&file, true)) {
		file.close();
		tcLogService::CreateLog(this, "Can not load config file.");
		return false;
	}
	file.close();

	QDomElement syselement = doc.documentElement();
	//load config info
	QDomElement element;
	element = syselement.firstChildElement();
	while (! element.isNull()) {
		tcConfigItem *item = new tcConfigItem(element.tagName());
		if (! item->LoadFromXml(element)) {
			tcLogService::CreateLog(this, "Can not load config.");
			delete item;
			return false;
		}
		mConfigMap.insert(element.tagName(), item);
		element = element.nextSiblingElement();
	}

	return true;
}

bool tcCfgService::SaveToFile()
{
	QFileInfo fileinfo(mPath, CONFIG_XML_FILE);
	QFile file(fileinfo.filePath());
	if (! file.open(QIODevice::WriteOnly)) {
		tcLogService::CreateLog(this, "Can not open config file.");
		return false;
	}

	QDomDocument doc;
	QDomElement syselement = doc.createElement(SYSTEM_NAME);
	doc.appendChild(syselement);

	//save config info
	foreach (tcConfigItem *item, mConfigMap) {
		QDomElement element = doc.createElement(item->GetClassName());
		syselement.appendChild(element);
		if (! item->SaveToXml(doc, element)) {
			tcLogService::CreateLog(this, "Can not save config.");
			return false;
		}
	}

	QTextStream stream(&file);
	doc.save(stream, 4);
	file.close();
	return true;
}

void tcCfgService::ClearAllConfigItems()
{
	foreach (tcConfigItem *item, mConfigMap) {
		delete item;
	}
	mConfigMap.clear();
}
