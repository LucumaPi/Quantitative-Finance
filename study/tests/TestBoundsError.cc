// TestBoundsError.cpp
//
//
//
// Built-in types
//
// (C) Datasim Education BV 2005-2006
//

#include <iostream>

int main()
{

	{ // Define a scope

		int j = 2;
		std::cout << j << std::endl;
	}

	// cout << j; j does not exist

	int myArr[10];

	// Initialise the array
	for (int j = 0; j < 10; j++)
	{
		myArr[j] = j + 1;
		std::cout << myArr[j] << ",";
	}

	std::cout << std::endl << myArr[-1];
	std::cout << std::endl << myArr[1000];


	return 0;
}
