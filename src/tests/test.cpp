#include "tests/test.h"

#include <iostream>

#include "config.h"

namespace Test {
	Test::Test(std::string name, std::string msg) : m_name(name), m_msg(msg) {}

	bool Test::passed() {return false;}
	void Test::perform() {}
	void Test::on_fail() {}
	void Test::on_pass() {}

	bool Test::operator()() {
		perform();
		bool p = passed();
		if (!p) {
			on_fail();
			*Config::LOGF << "Test: " << m_name << " failed." << std::endl;
			*Config::LOGF << "Reason: " << m_msg << std::endl;
		} else {
			on_pass();
			*Config::LOGF << "Test: " << m_name << " passed." << std::endl;
		}
		return p;
	}
}

