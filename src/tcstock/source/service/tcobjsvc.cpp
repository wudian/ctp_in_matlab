#include "tcobjsvc.h"

#include <QtCore/QFileInfo>

#include "tclogsvc.h"
#include "../stockinfo/tcstockinfopack.h"

tcObjService* tcObjService::mThis = NULL;

bool tcObjService::Initialize(int argc, char* argv[])
{
	Q_ASSERT(! mThis);
	mThis = new tcObjService(argc, argv);
	if (! mThis->InitializeAll()) {
		return false;
	}
	return true;
}

bool tcObjService::Finalize()
{
	Q_ASSERT(mThis);
	if (! mThis->FinalizeAll()) {
		return false;
	}
	delete mThis;
	mThis = NULL;
	return true;
}

tcObjService::tcObjService(int argc, char* argv[])
{
	QFileInfo fileinfo(argv[0]);
	mStockManager = new tcStockManager(fileinfo.absolutePath());
	mMarketManager = new tcMarketManager(fileinfo.absolutePath());
	mFavouriteManager = new tcFavouriteManager(fileinfo.absolutePath());
}

tcObjService::~tcObjService()
{
	delete mFavouriteManager;
	delete mMarketManager;
	delete mStockManager;
}

bool tcObjService::InitializeAll()
{
	if (! mStockManager->LoadFromFile()) {
		tcLogService::CreateLog(this, "Error when load stock manager.");
		return false;
	}
	if (! mMarketManager->LoadFromFile()) {
		tcLogService::CreateLog(this, "Error when load market manager.");
		return false;
	}
	if (! mFavouriteManager->LoadFromFile()) {
		tcLogService::CreateLog(this, "Error when load favourite manager.");
		return false;
	}
	return true;
}
	
bool tcObjService::FinalizeAll()
{
	return true;
}
