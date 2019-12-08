// tesSet2.cpp
//
// Testing Set class. Mostly Cartesian Products
//
// (C) Datasim Education BV 2004
//

#include <iostream>
#include <string>

#include <duffy/Set.hh>

template <class T> void print(const Set<T>& l, const std::string& name)
{  // Print the contents of a Set. Notice the presence of a constant iterator.
	
	std::cout << std::endl << name << ", size of set is " << l.Size() << "\n[ ";

	typename Set<T>::const_iterator i;

	for (i = l.Begin(); i != l.End(); ++i)
	{
			std::cout << *i << " ";

	}

	std::cout << "]\n";
}

template <class T, class T2> void printSet(const Set<std::pair<T, T2> >& l, const std::string& name)
{  // Print the contents of a Set. Notice the presence of a constant iterator.
	
	std::cout << std::endl << name << ", size of set is " << l.Size() << "\n[ ";

	typename std::set<std::pair<T, T2> >::const_iterator i;

	for (i = l.Begin(); i != l.End(); ++i)
	{
			std::cout << (*i).first << ", " << (*i).second << std::endl;

	}

	std::cout << "]\n";
}

int main()
{
	Set<int> first;				// Default constructor

	// Only unique (new elements) added
	first.Insert(1);
	first.Insert(2);
	first.Insert(3);
	print (first, "First set");

	Set<char> s1;
	s1.Insert('A');
	s1.Insert('B');
	s1.Insert('C');
	s1.Insert('D');
	print (s1, "Set of char");

	Set<std::pair <int, char> > S = first.CartesianProduct(s1);
	printSet(S, "Product1");

	S = first*s1;
	printSet(S, "Product1");


	Set<std::pair <char, int> > S2 = s1.CartesianProduct(first);
	printSet(S2, "Product2");

	S2 = s1*first;
	printSet(S2, "Product2");

	return 0;
}