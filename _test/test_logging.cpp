/*
*
* templog library
*
* Copyright Hendrik Schober
* Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at
*     http://www.boost.org/LICENSE_1_0.txt)
*
* see http://templog.sourceforge.net/ for more info
*
*/

/**
* 
* \file
* 
* templog logging test application
*/

/**********************************************************************************************/
#include "config.h"

/**********************************************************************************************/
#include <iostream>

/**********************************************************************************************/

#include "logging.h"

/**********************************************************************************************/

namespace {

	typedef templog::logger< templog::global_logger
	                       , templog::sev_message
	                       , templog::audience_list<aud_support,aud_user> >
	                                                  logger1;

	template< class logger, int Severity_, int Audience_ >
	inline void test_log()
	{
		TEMPLOG_LOG(logger,Severity_,Audience_) << "test log output severity #" << templog::sev_debug   << " for log output audience #" << Audience_;
	}

	template< class logger, int Audience_ >
	inline bool test_all_severities()
	{
		test_log<logger,sev_debug  ,Audience_>();
		test_log<logger,sev_info   ,Audience_>();
		test_log<logger,sev_message,Audience_>();
		test_log<logger,sev_warning,Audience_>();
		test_log<logger,sev_error  ,Audience_>();
		test_log<logger,sev_fatal  ,Audience_>();

		return true;
	}

	template< class logger >
	inline bool test_all_audiences()
	{
		const bool dev = test_all_severities<logger1,templog::aud_developer>();
		const bool sup = test_all_severities<logger1,templog::aud_support  >();
		const bool usr = test_all_severities<logger1,templog::aud_user     >();
		return dev && sup && usr;
	}

	inline bool test_all_loggers()
	{
		templog::dynamic_write_policy::auto_writer<templog::std_write_policy> w;

		const bool log1 = test_all_audiences<logger1>();

		return log1;

	}

	inline bool test_logging()
	{
		return test_all_loggers();
	}

}

/**********************************************************************************************/

int main()
{
	const bool test = test_logging();
	if( !test ) {
		std::cerr << "ERROR in test!\n";
		return 1;
	}
	std::cerr << "Successfully tested.\n";
	return 0;
}

/**********************************************************************************************/
/* EOF */
