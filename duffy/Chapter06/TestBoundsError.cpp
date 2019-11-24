// TestBoundsError.cpp
//
//
//
// Built-in types
//
// (C) Datasim Education BV 2005-2006
//

#include <iostream>
using namespace std;

int main()
{

	{ // Define a scope

		int j = 2;
		cout << j << endl;
	}

	// cout << j; j does not exist

	int myArr[10];

	// Initialise the array
	for (int j = 0; j < 10; j++)
	{
		myArr[j] = j + 1;
		cout << myArr[j] << ",";
	}

	cout << endl << myArr[-1];
	cout << endl << myArr[1000];


	return 0;
}
