#include "include/exercise2.hpp"
#include "gtest/gtest.h"

TEST(NULLException, throwsException){
	int* ptr = nullptr;
	ASSERT_THROW(throws(ptr),NULLException);
}

TEST(Sortierung, throwsNoException){
	int* ptr = nullptr;
	ASSERT_THROW(throwsNot(ptr),NULLException);
}


int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
