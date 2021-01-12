#ifndef TEST_H_
#define TEST_H_

#include <string>

namespace Test {
	class Test {
		private:
			std::string m_name;
			std::string m_msg;
		public:
			Test(std::string name, std::string msg);
			virtual bool passed();
			virtual void perform();
			virtual void on_fail();
			virtual void on_pass();

			virtual bool operator()();
	};
}

#endif

