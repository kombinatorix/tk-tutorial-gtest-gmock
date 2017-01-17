#include "include/exercise2.hpp"
#include "gtest/gtest.h"

TEST(NULLException, throwsException){
	int* ptr = nullptr;
	// ausfuellen
}

TEST(Sortierung, throwsNoException){
	int* ptr = nullptr;
	// ausfuellen
}


int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
