#include <string>
#include "gtest/gtest.h"

class StringCombination : public ::testing::Test {
	protected:
		virtual void SetUp(){
			this->foo="Foo";
			this->bar="Bar";
		}
		virtual void TearDown(){

		}

		std::string concatenate1();
		std::string concatenate2();
		std::string foo;
		std::string bar;
};
