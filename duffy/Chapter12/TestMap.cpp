// TestMap.cpp
//
// Test case for map container. Simple element-based operations.
//
// Important topics are:
//
//	1. The question of unique keys(when allowed/accepted)
//	2. Inserting pairs of object into map
//	3. Iterating over the elements of the map and using the current pair's option
//	and second elements.
//
// (C) Datasim Education 2003-2006

#include <map>
#include <iostream>
#include <string>

using namespace std;


int main()
{

	map<string, double> option;

	// Usind indexing to define the keys in the map
	option["r"] = 0.10;		// Interest rate
	option["sig"] = 0.28;	// Volatility
	option["K"]	= 19.0;		// Strike price
	option["T"] = 0.75;		// Expiry dat
	option["S"] = 19.0;		// Underlying asset

	cout << "Size of map: " << option.size() << endl;;

	// Iterating in the map
	map<string, double>::iterator i = option.begin();

	while (i != option.end())
	{ 
			cout << "Element pair [" << (*i).first << "," << (*i).second << "]\n";
			i++;
	}


	return 0;

}






