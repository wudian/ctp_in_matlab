#ifndef tccfgsvc_h

#define tccfgsvc_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

class tcConfigItem : public QObject
{
	Q_OBJECT

public:
	tcConfigItem(const QString &pClassName);

	bool LoadFromXml(const QDomElement &pElement);

	bool SaveToXml(QDomDocument &pDoc, QDomElement &pElement);

	QString GetAttribute(const QString &pKey, const QString &pDefaultValue);

	void SetAttribute(const QString &pKey, const QString &pValue);

	QString GetClassName();

private:
	QString mClassName;

	QStringList mKeyList;

	QStringList mValueList;

};

/*! \brief tcCfgService
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.29
 	
	系统各种配置参数的管理类。
*/
class tcCfgService : public QObject
{
	Q_OBJECT

public:
	static bool Initialize(int argc, char* argv[]);

	static bool Finalize();

	static QString GetAttribute(QObject *pObject, const QString &pKey, const QString &pDefaultValue);

	static void SetAttribute(QObject *pObject, const QString &pKey, const QString &pValue);

	static QString GetGlobalAttribute(const QString &pKey, const QString &pDefaultValue);

protected:
	tcCfgService(int argc, char* argv[]);

	~tcCfgService();

	tcConfigItem* GetConfigItem(const QString &pClassName);

	bool LoadFromFile();

	bool SaveToFile();

	void ClearAllConfigItems();

private:
	static tcCfgService *mThis;

	QDir mPath;

	QMap<QString, tcConfigItem*> mConfigMap;

};

#endif //tccfgsvc_h
