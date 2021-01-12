#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include "config.h"
#include "tests/test.h"
#include "tests/log_test.h"

namespace RunTests {
	void run_tests() {
  		std::array<std::unique_ptr<Test::Test>, 1> TESTS = {
    		std::make_unique<LogTest::ThreadTest>(3, Config::TESTF_DIR + "log_test_thread.txt")
  		};
  		int failed = 0;
  		int passed = 0;

  		*Config::LOGF << "Performing Tests..." << std::endl;

  		for (auto i = TESTS.begin(); i != TESTS.end(); ++i) {
    			if ((**i)())
      				++passed;
    			else
      				++failed;
  		}

		*Config::LOGF << "Tests Performed." << std::endl;
		*Config::LOGF <<"Report: " << failed << " failed, "  << passed << " passed." << std::endl;
	}
}

