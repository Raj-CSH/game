#include "log.h"

#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <string>
#include <system_error>

#include <cerrno>
#include <cstddef>
#include <cstdio>

#include "config.h"

static std::string const LVL_STR[] = {
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR"
};

class Logger {
	private:
		Log::Level m_lvl;
		std::mutex m_mtx;
		std::ostream * m_out;

		Logger() : m_out(Config::LOGF) {};
	public:
		static Logger& get_log() {
			static Logger logger;
			return logger;
		}

		void log(Log::Level lvl, std::string const & msg) {
			std::lock_guard<std::mutex> guard(m_mtx);
			if (lvl < m_lvl)
				return;
			*m_out << LVL_STR[lvl] << ": " << msg << std::endl;
		};

		void init(Log::Level lvl, std::ostream * out) {
			m_lvl = lvl;
			m_out = out;
			log(Log::INFO, "Log started.");
		}

		~Logger() {
			log(Log::INFO, "Log ended.");
		};

		Logger(Logger const &) = delete;
		void operator=(Logger const &) = delete;
};

namespace Log {
	void init(Level lvl, std::ostream * out) {
		Logger& logger = Logger::get_log();
		logger.init(lvl, out);
	}

	void log(Level lvl, std::string const & msg) {
		Logger& logger = Logger::get_log();
		logger.log(lvl, msg);
	}

	void vlogf(Level lvl, std::string const & fmt, va_list vl) {
		va_list vl_copy;
		va_copy(vl_copy, vl);
		size_t len = vsnprintf(nullptr, 0, fmt.c_str(), vl_copy);
		va_end(vl_copy);

		if (len >= 0) {
			std::string str(len + 1, '\0');
			vsnprintf(&str[0], str.size(), fmt.c_str(), vl);
			str.resize(len);
			log(lvl, str);
			return;
		}

		auto const err = errno;
		auto const ec = std::error_code(err, std::generic_category());
		throw std::system_error(ec);
	}

	void logf(Level lvl, std::string const & fmt, ...) {
		va_list vl;
		va_start(vl, fmt);
		vlogf(lvl, fmt, vl);
	}
}

