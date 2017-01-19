#include "include/exercise3.hpp"
#include "gtest/gtest.h"


TEST_F(StringCombination, FooBar){
	ASSERT_EQ("FooBar",concatenate1());	
}

TEST_F(StringCombination, BarFoo){
	ASSERT_EQ("BarFoo",concatenate2());	
}

int main(int argc,char **argv){

	::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

