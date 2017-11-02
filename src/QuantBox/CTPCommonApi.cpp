#include "CTPCommonApi.h"
#include "enums.h"
#include "CTPLastInfos.h"
#include "CppMysql.h"
#include "logger.h"
#include "defines.h"
#include "MarketData.h"

CCTPCommonApi::CCTPCommonApi()
	: m_status(E_uninit)
	, m_nRequestID(0)
{
	wdCTPLastInfos::instance();
	m_pMysql = std::make_shared<CppMysql>();
	if (!m_pMysql->Mysql_Init())
		LOG_ERROR << "Mysql³õÊ¼»¯Ê§°Ü";
}

CCTPCommonApi::~CCTPCommonApi()
{
	m_pMysql->Mysql_Finalize();
}
