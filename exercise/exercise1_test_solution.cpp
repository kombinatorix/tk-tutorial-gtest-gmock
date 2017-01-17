#include "include/exercise1.hpp"
#include "gtest/gtest.h"

TEST(Sortierung, guteSortierung){
	goodandbadsort gabs(10);
	std::vector<int> sortedVector= gabs.goodSort();
	for(int i=0; i< sortedVector.size()-1;++i){
		EXPECT_LE(sortedVector.at(i),sortedVector.at(i+1));
	}
}

TEST(Sortierung, schlechteSortierung){
	goodandbadsort gabs(10);
	std::vector<int> sortedVector= gabs.badSort();
	for(int i=0; i< sortedVector.size()-1;++i){
		EXPECT_LE(sortedVector.at(i),sortedVector.at(i+1)) << "Der Wert an Position " << i << " ist größer als an Position " << i+1;
	}

}

TEST(Sortierung, Vergleich){
	goodandbadsort gabs(10);
	std::vector<int> goodVec = gabs.goodSort();
	std::vector<int> badVec  = gabs.badSort();
	int size = goodVec.size();
	for(int i=0; i<size; ++i){
		EXPECT_EQ(goodVec.at(i),badVec.at(i)) << "Die beiden Werte an Position "<< i << " unterscheiden sich";
	}
}

int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
