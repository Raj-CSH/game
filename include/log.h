#ifndef LOG_H_
#define LOG_H_

#include <ostream>
#include <string>

#include <cstdarg>

namespace Log {
	enum Level{
		DEBUG,
		INFO,
		WARNING,
		ERROR,
	};

	void init(Level lvl, std::ostream * out);
	void log(Level lvl, std::string const & msg);
	void logf(Level lvl, std::string const & fmt, ...);
	void vlogf(Level lvl, std::string const & fmt, va_list vl);
}

#endif

