// Testset1.cpp
//
// Creating sets. Simple functions for starters.
//
//		1. Create sets with string elements
//		2. Compare sets with '==' operator
//		3. Swap two sets using the swap() function
//		4. Assigning sets to each other
//
// (C) Datasim Education 2003-2006

#include <iostream>
#include <set>
#include <string>

template <class T> void print(const std::set<T>& mySet, const std::string& name)
{  // Print the contents of a set. Notice the presence of a const iterator.
	
	std::cout << std::endl << name << ", size of set is " << mySet.size() << "\n[";

	typename std::set<T>::const_iterator i;

	for (i = mySet.begin(); i != mySet.end(); ++i)
	{
			std::cout << (*i) << ",";

	}

	std::cout << "]\n";
}

int main()
{

	std::set<std::string> first;				// Default constructor

	// Only unique (new elements) added
	first.insert("r");
	first.insert("T");
	first.insert("sigma");

	std::cout << "First Size: " << first.size() << std::endl;

	std::set<std::string> second (first);	// Copy constructor

	// Add extra elements to second set
	second.insert("r");	// "Interest rate"
	second.insert("K");	// "Strike price"
	second.insert("S");	// "Current underlying price"
	second.insert("b");	// "Cost of carry"

	print(second, "Second set");	
	second.erase("K");
	print(second, "Second set");

	std::cout << "Second Size: " << second.size() << std::endl;

	// Are the sets the same?
	if (first == second)
		std::cout << "Sets have same elements\n";
	else
		std::cout << "Not same elements\n";

	// A bit of swapping
	swap(first, second);

	// Assignment
	std::set<std::string> third = first;


	// Now print the sets 
	print(first, "First set");
	print(second, "Second set");
	print(third, "Third set");


	// Now creat a set representing Executive options
	std::set<std::string> execOption(first);
	execOption.insert("lambda");		// The jump rate, see Haug 1998

	print(execOption, "An Executive Option");

}