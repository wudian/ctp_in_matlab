#include "logger.h"

std::ostream& operator<< (std::ostream& strm, my_severity_level level)
{
	static const char *strings[] =
	{
		/*"db_error",
		"db_warning",
		"db_normal",*/
		"normal",
		"warning",
		"error"
	};

	if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
		strm << strings[level];
	else
		strm << static_cast< int >(level);

	return strm;
}

// 输出高于lev的日志
void initLog(const std::string &logFilePath, my_severity_level lev)
{
	typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
	boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();
	
	sink->locked_backend()->add_stream(boost::make_shared< std::ofstream >(logFilePath));
	sink->locked_backend()->add_stream(
		boost::shared_ptr< std::ostream >(&std::clog/*, boost::empty_deleter()*/));

	sink->set_formatter(
		expr::format("[%1%]<%2%>(%3%): %4%")  
		% expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")  
		% expr::attr<my_severity_level>("Severity")  
		% expr::attr<attrs::current_thread_id::value_type >("ThreadID")  
		% expr::smessage  
		);  

	logging::core::get()->add_sink(sink);

	// 全局日志等级过滤
	sink->set_filter(expr::attr<my_severity_level>("Severity") >= lev);		

	// Add attributes
	logging::add_common_attributes();
}