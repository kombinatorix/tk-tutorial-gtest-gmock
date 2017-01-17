


#include "include/exercise1.hpp"
#include <algorithm>






goodandbadsort::goodandbadsort(int n){
		srand(time(NULL));
		for(int i=0; i<n; ++i){
			this->randomNumbers.push_back(rand() % 100);
		}
}

goodandbadsort::~goodandbadsort(){}

std::vector<int> goodandbadsort::goodSort(){
	std::vector<int> tempVec = this->randomNumbers;
	 std::sort(tempVec.begin(),tempVec.end());
	return tempVec;
}

std::vector<int> goodandbadsort::badSort(){
	return this->randomNumbers;
}

