#include "util.h"

#include <string>

#include <cstdarg>

#include <SDL.h>

#include "log.h"

namespace Util {
	void logf_sdl_error(std::string const & fmt, ...) {
		va_list vl;
		va_start(vl, fmt);
		Log::vlogf(Log::ERROR, fmt + " SDL_Error: " + SDL_GetError() + ".", vl);
	}

	void log_sdl_error(std::string const & msg) {
		logf_sdl_error(msg);
	}
}

