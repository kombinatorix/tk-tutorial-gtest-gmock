#include "gtest/gtest.h"

TEST(Case1, Test1){
	SUCCEED();
}

TEST(Case1, Test2){
	SUCCEED();
}
TEST(Case1, Test3){
	FAIL();
}
TEST(Case1, Test4){
	SUCCEED();
}



TEST(Case2, Test1FAIL){
	FAIL();
}
TEST(Case2, Test2SUCCEED){
	SUCCEED();
}
TEST(Case2, Test3FAIL){
	FAIL();
}
TEST(Case2, Test4FAIL){
	FAIL();
}
TEST(Case2, Test5SUCCEED){
	SUCCEED();
}



TEST(TOTALFAIL, Test1){
	FAIL();
}
TEST(TOTALFAIL, Test2){
	FAIL();
}
TEST(TOTALFAIL, Test3){
	FAIL();
}

int main(int argc,char **argv){

	::testing::GTEST_FLAG(filter)="*-:Case1.Test3:*FAIL*";
	::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
