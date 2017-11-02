#ifndef tcobjsvc_h

#define tcobjsvc_h

#include <QtCore/QVariant>
#include <QtCore/QObject>

class tcStockManager;
class tcMarketManager;
class tcFavouriteManager;

/*! \brief tcObjService
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2006.12.24
 	
	系统全局对象管理类。目前负责管理 tcMarketMaager 和 tcFavouriteManager 。
	也就是说要访问这些类，以及属于他们的自对象时，应该使用该类作为访问入口。
*/
class tcObjService : public QObject
{
	Q_OBJECT

public:
	static bool Initialize(int argc, char* argv[]);

	static bool Finalize();

	static tcStockManager* GetStockManager();

	static tcMarketManager* GetMarketManager();

	static tcFavouriteManager* GetFavouriteManager();

protected:
	tcObjService(int argc, char* argv[]);

	~tcObjService();

	bool InitializeAll();
	
	bool FinalizeAll();

private:
	static tcObjService *mThis;

	tcStockManager *mStockManager;	
	tcMarketManager *mMarketManager;
	tcFavouriteManager *mFavouriteManager;

};

inline tcStockManager* tcObjService::GetStockManager()
{
	return mThis->mStockManager;
}

inline tcMarketManager* tcObjService::GetMarketManager()
{
	return mThis->mMarketManager;
}

inline tcFavouriteManager* tcObjService::GetFavouriteManager()
{
	return mThis->mFavouriteManager;
}

#endif //tcobjsvc_h

