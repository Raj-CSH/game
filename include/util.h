#ifndef UTIL_H_
#define UTIL_H_

#include <string>

#include <cstdarg>

namespace Util {
	void logf_sdl_error(std::string const & fmt, ...);
	void log_sdl_error(std::string const & msg);
}

#endif

