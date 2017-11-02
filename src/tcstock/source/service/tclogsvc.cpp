#include "tclogsvc.h"

#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>

#define LOG_FILE "/sys.log"

tcLogService* tcLogService::mThis = NULL;

bool tcLogService::Initialize(int argc, char* argv[])
{
	Q_ASSERT(! mThis);
	mThis = new tcLogService(argc, argv);
	return true;
}

bool tcLogService::Finalize()
{
	Q_ASSERT(mThis);
	delete mThis;
	mThis = NULL;
	return true;
}

void tcLogService::CreateLog(QObject *pObject, const QString &pLogText)
{
	mThis->_CreateLog(pObject, pLogText);
}

tcLogService::tcLogService(int argc, char* argv[])
{
	QFileInfo fileinfo(argv[0]);
	mFile.setFileName(fileinfo.absolutePath() + LOG_FILE);
	if (! mFile.open(QIODevice::WriteOnly)) {
		Q_ASSERT(0);
		return;
	}
}

tcLogService::~tcLogService()
{
	mFile.close();
}

void tcLogService::_CreateLog(QObject *pObject, const QString &pLogText)
{
	QTextStream stream(&mFile);
	stream<<pObject->metaObject()->className()<<" :: "<<pLogText<<endl;
}
