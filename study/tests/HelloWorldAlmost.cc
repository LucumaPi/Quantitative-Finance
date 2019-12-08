// ch3vector.cpp
//
// Examples to show how sequence containers (vector) work.
//
//	Last modificaton dates:
//
//	2006-3-22 DD new code for algorithms
//
// (C) Datasim Education BV 2003-2006
//
//

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

std::string UpperCase(std::string s)
{ // Convert a string to upper case

	for (int j = 0; j < s.length(); j++)
	{
		if (s[j] >= 'a' && s[j] <= 'z')
		{
			s[j] -= 'a' - 'A';
		}
	}

	return s;
}

class Join
{
public:

	// Overloading of operator ()
	std::string operator () (const std::string& s1, const std::string& s2)
	{
		return s1 + " and " +s2;
	}

};

bool myGreater(double x, double y)
{
	return x > y;
}

template <class T> void print(const std::vector<T>& l, std::string s = std::string("data"))
{  // A generic print function for vectors
	
	std::cout << std::endl << s << ", size of vector is " << l.size() << "\n[";

	// We must use a const iterator here, otherwise we get a compiler error.
	typename std::vector<T>::const_iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
			std::cout << *i << ",";

	}

	std::cout << "]\n";
}

int main()
{


	std::size_t n = 10;
	double val = 3.14;
	std::vector<double> myVec(n, val);	// Create n copies of val

	print(myVec);

	// Access elements of the vector by using the indexing operator []
	// Change some values here and there
	myVec[0] = 2.0;
	myVec[1] = 456.76;

	int last_element= myVec.size() - 1;
	myVec[last_element] = 55.66;

	print(myVec);

	// Now some algorithms

	std::vector<double> myVec2(myVec.size());
	std::list<double> myList;

	// Copy source range of type T1 into target range of type T2
	copy(myVec.begin(), myVec.end(), myVec2.begin());
	print(myVec2, std::string("copy to a vector"));

	copy(myVec.begin(), myVec.end(), myList.begin());


	// Copying and transformation at the same time 
	std::vector<std::string> First(3);
	First[0] = "Bill";
	First[1] = "Abbott";
	First[2] = "Bassie";

	std::vector<std::string> Second(3);
	Second[0] = "Ben";
	Second[1] = "Costello";
	Second[2] = "Adriaan";

	std::vector<std::string> Couples(3);

	// Now convert the First names to upper case
	transform (First.begin(), First.end(), First.begin(), UpperCase);
	print(First, std::string("An upper case vector"));

	// Now join to make a team
	transform (First.begin(), First.end(), Second.begin(), Couples.begin(),
			Join());
	print(Couples, std::string("Joined couples"));

	// Shift the elements of a vector to the left; those that fall off
	// are inserted at the end
	int N = 6;
	std::vector<double> myVec3(N);	

	for (int i = 0; i < myVec3.size(); i++)
	{
			myVec3[i] = double (i);

	}

	int shiftFactor = 2;
	rotate(myVec3.begin(), myVec3.begin() + shiftFactor, myVec3.end());
	print(myVec3, std::string("Rotated vector by 2 units"));

	// Now reverse the order of elements in the vector; the first becomes
	// last and vice versa
	reverse(myVec3.begin(), myVec3.end());
	print(myVec3, std::string("Reversed vector vec3"));


	// Now replace each occurrence of one value by a new value
	double oldVal = 2;
	double newVal = 999;
	replace(myVec3.begin(), myVec3.end(), oldVal, newVal);
	print(myVec3, std::string("Modified value of vec3"));

	// Now remove this element 
	remove(myVec3.begin(), myVec3.end(), newVal);
	print(myVec3, std::string("Removed element from vec3"));

	// Sort the random access container vector<T> class
	myVec3[myVec3.size() - 1] = 9999.0;
	stable_sort(myVec3.begin(), myVec3.end()); // Using < as comparitor
	print(myVec3, std::string("Sorted vec3 with '<' ASCENDING "));

	stable_sort(myVec3.begin(), myVec3.end(), myGreater);
	print(myVec3, std::string("Sorted vec3 with DESCENDING comparitor function "));

	// Merge two sorted vectors
	std::vector<double> myVec4(N, 2.41);	
	std::vector<double> myVec5(myVec3.size() + myVec4.size()); // Output
	merge(myVec3.begin(), myVec3.end(), myVec4.begin(), myVec4.end(),
			myVec5.begin());
	print(myVec5, std::string("Merged vector"));

	return 0;
}