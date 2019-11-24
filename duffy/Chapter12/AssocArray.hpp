// AssocArray.hpp
//
// Associative array class. In this case we access elements by 
// using non-integral indices. This is potentially a very useful class
// and it can be used in many financial applications.
// 
// This class is essentially an Adaptor class from an STL map.
//
// (C) Datasim Component Technology 1999-2006

#ifndef AssocArray_hpp
#define AssocArray_hpp

#include "Array.cpp"
#include "Set.cpp"
#include <map>
using namespace std;

template <class V, class AI = string> class AssocArray
{ // Note that the first index is the value and second index is 
  // 'associative' key

private: 
		map<AI,V> str;	// The list of associative values, e.g. strings
		
		// Redundant information for performance
		Set<AI> keys;

public:
	// Constructors & destructor
	AssocArray();
	AssocArray(const AssocArray<V, AI>& arr2);
	// Construct the map from a list of names and values
	AssocArray(const Set<AI>& names, const V& val);

	AssocArray<V, AI>& operator = (const AssocArray<V, AI>& ass2);

	// New overloaded indexing operator
	virtual V& operator [] (const AI& index);	// Subscripting operator


	typedef typename map<AI,V>::iterator iterator;
	typedef typename map<AI,V>::const_iterator const_iterator;

	// Iterator functions
    iterator Begin();				// Return iterator at begin of assoc array
	const_iterator Begin() const;	// Return const iterator at begin of assoc array
	iterator End();					// Return iterator after end of assoc array
    const_iterator End() const;		// Return const iterator after end of assoc array

	// Selectors
	long Size() const { return str.size(); }
	Set<AI> Keys() const { return keys; }		// Copy

	// Modifiers
//	void add(const AI& key, const V& value);
//	void remove(const AI& key);


};


#endif	// AssocArray_hpp