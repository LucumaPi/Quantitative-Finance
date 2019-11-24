// TestSetOperations.cpp
//
// Test of set.Concerned with interactions between sets. In particular, we look
// at some set-like operations:
//
//	set_union
//	includes (is A a subset of B?)
//	set_intersection
//	set_difference
//	set_symmetric_difference (see section 20.28 in Musser)
//
//	These algorithms are in <algorithm> and they use the assumption that all elements are
//	sorted using the operator <. Another variant allows us to use a comparitor function.
// 
//	We use an insert iterator to compute these set functions (thanks to JD).
//
//	Finally, a number of generic algorithms are defined that promotes Information Hiding
//	so that STL is a bit more user-friendly. In particular, we do not have to worry about
//	iterating or using insert iterators in client code. This approach would form the 
//	beginnings of a Microkernel pattern for STL (see the patterns book by Buschmann).
//
// (C) Datasim Education 1998-2003

#include <set>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

template <class T> void print(const set<T>& l, const string& name)
{  // Print the contents of a set. Notice the presence of a constant iterator.
	
	cout << endl << name << ", size of set is " << l.size() << "\n[ ";

	set<T>::const_iterator i;

	for (i = l.begin(); i != l.end(); ++i)
	{
			cout << *i << " ";

	}

	cout << "]\n";
}

template <class T> bool subset(const set<T>& super, const set<T>& sub)
{ // Is one set a subset of another set?

	// sub is a subset of superset iff superset includes sub

	return includes(super.begin(), super.end(), sub.begin(), sub.end());

}

template <class T> bool superset(const set<T>& super, const set<T>& sub)
{ // Is one set a superset of another set?

	// superset contains sub iff sub is s subset of superset

	return subset(super, sub);

}


// Applying Information Hiding to the union of two sets. The same principles can be
// applied to the other set functions.
template <class T> void UnionSet(const set<T>& s1, const set<T>& s2, set<T>& myunion)
{ // Union of two sets

	set<int>::iterator i = myunion.begin();
	insert_iterator<set<int> > insertiter(myunion, i);
	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), insertiter);

}

template <class T> void DifferenceSet(const set<T>& s1, const set<T>& s2, set<T>& mydiff)
{ // Difference of two sets

	set<T>::iterator i = mydiff.begin();
	insert_iterator<set<int> > insertiter(mydiff, i);
	set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), insertiter);
		
}
template <class T> void IntersectionSet(const set<T>& s1, const set<T>& s2, set<T>& myintersect)
{ // Intersection of two sets

	set<int>::iterator i = myintersect.begin();
	insert_iterator<set<int> > insertiter(myintersect, i);
	set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), insertiter);
}
template <class T> void SymmetricDifferenceSet(const set<T>& s1, const set<T>& s2, set<T>& mysdiff)
{ // Symmetric difference of two sets

	set<T>::iterator i = mysdiff.begin();
	insert_iterator<set<int> > insertiter(mysdiff, i);
	set_symmetric_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), insertiter);
		
}

int main()
{

	set<int> first;				// Default constructor

	// Only unique (new elements) added
	first.insert(1);
	first.insert(2);
	first.insert(3);
	print (first, "First set");

	set<int> second (first);
	// Check for subsethood (in other words, is second a subset of first?)
	if (includes(first.begin(), first.end(), second.begin(), second.end()))
		cout << "OK, second set is a subset of first set\n";
	else
		cout << "BAAH Not a subset\n";

	second.erase(3);
	
	// Checking for subsethood in a more user-friendly way
	if (subset (first, second) == true)
		cout << "Second set is a subset of first, OK\n";

	if (superset(first, second) == true)
		cout << "First set is a superset of second, OK\n";

	if (superset (second, first) == false)
		cout << "Second set is a NOT a superset of first, OK\n";

	second.insert(51);
	second.insert(52);

	print(second, "Second set");

	// The 4 set functions use an insert iterator. This has the effect of causing an 
	// insertion at a given position rather than the usual 'overwrite' mode.
	// The union of two sets
	set<int> myunion;
	set<int>::iterator i = myunion.begin();
	insert_iterator<set<int> > insertiter(myunion, i);

	set_union(first.begin(), first.end(), second.begin(), second.end(), insertiter);

	print(myunion, "Union");

	// Now the union of two sets using Information Hiding
	set<int> myunion2;

	UnionSet(first, second, myunion2);

	print (myunion2, "Union, second variant");

	// Intersecton of two sets
	set<int> myintersect;
	i = myintersect.begin();
	insert_iterator<set<int> > insertiter2(myintersect, i);

	set_intersection(first.begin(), first.end(), second.begin(), second.end(), insertiter2);

	print(myintersect, "Intersection");

	// Intersection using Information Hiding
	set<int> myintersect2;

	IntersectionSet(first, second, myintersect2);

	print (myintersect2, "Intersection, version 2");

	// Difference of two sets
	set<int> mydifference;
	i = mydifference.begin();
	insert_iterator<set<int> > insertiter3(mydifference, i);

	set_difference(first.begin(), first.end(), second.begin(), second.end(), insertiter3);

	print(mydifference, "Difference");
	
	// Difference using Information Hiding
	set<int> mydiff2;

	DifferenceSet(first, second, mydiff2);

	print (mydiff2, "Difference, version 2");

	// Symmetric difference of two sets
	set<int> mysymmdifference;
	i = mysymmdifference.begin();
	insert_iterator<set<int> > insertiter4(mysymmdifference, i);

	set_symmetric_difference(first.begin(), first.end(), second.begin(), second.end(), insertiter4);

	print(mysymmdifference, "Symmetric difference");
	
	// Symmetric Difference using Information Hiding
	set<int> mysdiff2;
	SymmetricDifferenceSet(first, second, mysdiff2);
	print (mysdiff2, "Symmetric Difference, version 2");

	return 0;

}
