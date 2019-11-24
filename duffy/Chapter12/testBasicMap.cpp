// testBasicMap.cpp
//
// Testng properties of maps
//
// 2006-3-27 DD Kick-off
//
// (C) Datasim Education BV 2003-2006
//

#include <map>
#include <string>
#include <iostream>
using namespace std;

void print (const map<char, double>& myMap)
{

	cout << "Number of elements in map: " << myMap.size() << endl;

	// Iterating in the map
	map<char, double>::const_iterator i = myMap.begin();

	while (i != myMap.end())
	{
			cout << (*i).first << ", " << ((*i).second) << endl;
			
			i++;
	}

	cout << endl;
}

void modify(map<char, double>& myMap, double scaleFactor)
{ // Multiply each value by a double

	// Iterating in the map (non-const)
	map<char, double>::iterator i = myMap.begin();

	while (i != myMap.end())
	{
			((*i).second) *= scaleFactor;
			
			i++;
	}

}

int main()
{

	map<char, double> map1;

	// Different ways of adding values
	// Using indexing
	map1['A'] = 1.0;

	// Inserting an 'explicit' pair object
	pair<char, double> myPair('B', 2.0);
	map1.insert(myPair);

	// Using make_pair template function
	pair<char, double> tmp = make_pair('C', 4.0);
	map1.insert(tmp);

	// Using anonymous objects
	map1.insert(pair<char, double>('F', 33.4));

	// Try to add keys again; does not work
	map1['A'] = 199.0; // Value will be changed however

	pair<char, double> tmp1 = make_pair('C', 55.0);
	map1.insert(tmp1);

	// Now print the map
	print(map1);

	// Change values
	double scaleF = 0.5;
	modify(map1, scaleF);
	print(map1);

	// Now erasing things

	// Erase a key
	map1.erase('B');
	print (map1);

	// Erase one iterator
	map1.erase(map1.begin());
	print (map1);

	// Erase between 2 iterators; same as map1.clear()
	map1.erase(map1.begin(), map1.end());
	print (map1);

	map1.clear();	// Delete an empty map has no effect

	return 0;
}
