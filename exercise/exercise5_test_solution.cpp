#include "gtest/gtest.h"

TEST(Case1, Test1){
	SUCCEED();
}
TEST(Case1, Test2){
	SUCCEED();
}
TEST(Case1, Test3){
	SUCCEED();
}
TEST(Case1, Test4){
	SUCCEED();
}



int main(int argc,char **argv){

	::testing::GTEST_FLAG(repeat)=3;
	::testing::GTEST_FLAG(shuffle)=true;
	::testing::GTEST_FLAG(random_seed)=3;

	::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
