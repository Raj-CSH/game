#ifndef LOG_TEST_H_
#define LOG_TEST_H_

#include <fstream>
#include <string>

#include <cstddef>

#include "config.h"
#include "tests/test.h"

namespace LogTest {
	class ThreadTest : public Test::Test {
		private:
			size_t m_n_threads;
			std::string m_fpath;
			std::fstream m_fstr;

			static void thread_task(int id);
		public:
			ThreadTest(size_t n_threads, std::string fpath);
			~ThreadTest();

			bool passed();
			void perform();
			void on_fail();
			void on_pass();
	};
}

#endif

