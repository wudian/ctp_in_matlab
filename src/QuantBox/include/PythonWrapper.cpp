#include <boost/python.hpp>
using namespace boost::python;

#include "MdUserApi.h"
#include "TraderApi.h"
#include "toolkit.h"

void (CMdUserApi::*Subscribe_)(const char *, const char *) = &CMdUserApi::Subscribe;
void (CMdUserApi::*Unsubscribe_)(const char *, const char *) = &CMdUserApi::Unsubscribe;
void (CMdUserApi::*RegisterCallback_OnConnect)(fnOnConnect pCallback) = &CMdUserApi::RegisterCallback;



BOOST_PYTHON_MODULE( QuantBox )
{
	def("ReadConfigFile", ReadConfigFile);

	class_<CThostFtdcMdSpi>("CThostFtdcMdSpi")
		;

	class_<CMdUserApi, bases<CThostFtdcMdSpi> >("CMdUserApi", init<>())
		.def("Connect", &CMdUserApi::Connect)
		.def("Disconnect", &CMdUserApi::Disconnect)		
		.def("Unsubscribe", Unsubscribe_)
		.def("Subscribe", Subscribe_)
		.def("RegisterCallback_OnConnect", RegisterCallback_OnConnect)
	;

	class_<CThostFtdcTraderSpi>("CThostFtdcTraderSpi")
		;

	class_<CTraderApi, bases<CThostFtdcTraderSpi> >("CTraderApi", init<>())
		.def("Connect", &CTraderApi::Connect)
	;
}