#include <iostream>
#include "DynamicArr.h"

int main() {
	DynamicArr arr1, arr2(3);
	DynamicArr arr3(arr1);
	
	for (size_t i = 0; i < 3; ++i) {
		arr3.push_back(i);
	}
	
	return 0;
}
