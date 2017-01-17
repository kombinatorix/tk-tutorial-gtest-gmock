#ifndef __example1__hpp__
#define __example1__hpp__

#include <vector>
#include <stdlib.h>
#include <time.h>

class goodandbadsort{
private:
	std::vector<int> randomNumbers;
public:
	goodandbadsort(int n);
	
	
	
	

	~goodandbadsort();

	std::vector<int> goodSort();




	std::vector<int> badSort();
};

#endif
