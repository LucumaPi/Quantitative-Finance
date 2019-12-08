// TestSetGroup.cpp
//
// Combining STL map and Datasim Set.
//
//	DD 2004-7-4 Written code
//
// (C) Datasim Education 2004

#include <iostream>
#include <map>
#include <string>

#include <duffy/Set.hh>

template <class T> void print(const Set<T>& l, const std::string& name)
{  // Print the contents of a Set. Notice the presence of a constant iterator.
	
	std::cout << std::endl << name << ", size of set is " << l.Size() << "\n[ ";

	typename std::set<T>::const_iterator i;

	for (i = l.Begin(); i != l.End(); ++i)
	{
			std::cout << *i << " ";

	}

	std::cout << "]\n";
}

int main()
{

	std::map<std::string, Set<int> > group;	
	
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

	std::cout << "Size of map: " << group.size() << std::endl;

	// Iterating in the map
	std::map<std::string, Set<int> >::iterator i = group.begin();

	while (i != group.end())
	{ 
			print((*i).second, (*i).first);
			i++;
	}

	return 0;
}