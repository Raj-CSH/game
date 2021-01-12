#include "tests/log_test.h"

#include <array>
#include <fstream>
#include <istream>
#include <iostream>
#include <ostream>
#include <regex>
#include <thread>
#include <vector>

#include <cstddef>

#include "config.h"
#include "log.h"
#include "tests/test.h"

namespace LogTest {
	ThreadTest::ThreadTest(size_t n_threads, std::string fpath) : Test("Threading", "Input interleaved."), m_n_threads(n_threads), m_fpath(fpath) {
		m_fstr.open(m_fpath, std::ios::in | std::ios::out | std::ios::trunc);
	}

	ThreadTest::~ThreadTest() {
		m_fstr.close();
	}

	void ThreadTest::thread_task(int id) {
		for (int i = 0; i < 10; ++i)
			Log::logf(Log::INFO, "Thread %d: %d.", id, i);
	}

	bool ThreadTest::passed() {
		std::string line;
		std::regex log_start("INFO: Log started.");
		std::regex log_end("INFO: Log ended.");
		std::regex log_line("INFO: Thread [0-9]: [0-9].");
		std::regex eof("");
		m_fstr.seekg(0);
		while (!m_fstr.eof()) {
			std::getline(m_fstr, line);
			if (!(std::regex_match(line, log_start) | std::regex_match(line, log_end) | std::regex_match(line, log_line) | std::regex_match(line, eof))) {
				*Config::LOGF << "Bad line: '" << line << "'" << std::endl;
				return false;
			}
		}
		return true;
	}

	void ThreadTest::perform() {
		Log::init(Log::DEBUG, &m_fstr);
		std::vector<std::thread> threads;
		for (int i = 0; i < m_n_threads; ++i)
			threads.push_back(std::thread(thread_task, i));
		for (auto i = threads.begin(); i != threads.end(); ++i)
			i->join();
	}

	void ThreadTest::on_fail() {
		Log::init(Log::DEBUG, Config::LOGF);
	}

	void ThreadTest::on_pass() {
		Log::init(Log::DEBUG, Config::LOGF);
	}
}

