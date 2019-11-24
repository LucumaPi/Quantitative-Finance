// TestSetGroup.cpp
//
// Combining STL map and Datasim Set.
//
//	DD 2004-7-4 Written code
//
// (C) Datasim Education 2004

#include <map>
#include <iostream>
#include <string>
using namespace std;

#include "Set.cpp"

template <class T> void print(const Set<T>& l, const string& name)
{  // Print the contents of a Set. Notice the presence of a constant iterator.
	
	cout << endl << name << ", size of set is " << l.Size() << "\n[ ";

	set<T>::const_iterator i;

	for (i = l.Begin(); i != l.End(); ++i)
	{
			cout << *i << " ";

	}

	cout << "]\n";
}

int main()
{

	map<string, Set<int> > group;	
	
	Set<int> first;				// Default constructor
	first.Insert(1);
	first.Insert(2);
	first.Insert(3);

	Set<int> s11;
	s11.Insert(2);
	s11.Insert(3);

	Set<int> s12;
	s12.Insert(8);
	s12.Insert(9);


	// Using indexing to define the keys in the map
	group["a"]	= first;		
	group["b"]	= s11;	
	group["c"]	= s12;		
	group["d"]	= first;	
	group["e"]	= s11;	

	cout << "Size of map: " << group.size() << endl;;

	// Iterating in the map
	map<string, Set<int> >::iterator i = group.begin();

	while (i != group.end())
	{ 
			print((*i).second, (*i).first);
			i++;
	}



	return 0;




}






