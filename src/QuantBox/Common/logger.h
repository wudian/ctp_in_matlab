#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>  
#include <boost/shared_ptr.hpp>  
#include <boost/make_shared.hpp>  
#include <boost/thread/thread.hpp>  
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>  
#include <boost/log/sinks/sync_frontend.hpp>  
#include <boost/log/sinks/text_ostream_backend.hpp>  
#include <boost/log/sources/record_ostream.hpp>  
#include <boost/log/support/date_time.hpp>  
#include <boost/log/common.hpp>  
#include <boost/log/expressions.hpp>  
#include <boost/log/attributes.hpp>  
#include <boost/log/sinks.hpp>  
#include <boost/log/sources/logger.hpp>  
#include <boost/log/utility/setup/common_attributes.hpp>  
#include <boost/log/utility/setup/common_attributes.hpp>  
#include <boost/log/utility/setup/formatter_parser.hpp>  
#include <boost/log/sources/severity_logger.hpp>  
#include <boost/log/sources/severity_feature.hpp>  

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

// We define our own severity levels
enum my_severity_level
{/*
 db_error,
 db_warning,
 db_normal,*/
	normal,
	warning,
	error
};

// The operator puts a human-friendly representation of the severity level to the stream
std::ostream& operator<< (std::ostream& strm, my_severity_level level);

// 输出高于lev的日志
void initLog(const std::string &logFilePath, my_severity_level lev);

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::severity_logger_mt<my_severity_level>) 

#endif