// AssocArray.cpp
//
// Associative array class. In this case we access elements by 
// using non-integral indices.
// This is a proof-of-concept (POC) class.
//
// Last modification dates:
//
//	16 August 2003 DD kick off
//	12 January 2004 DD some new member functions
//	2006-3-24 DD use Set as control; must implement exceptions
//
// (C) Datasim Component Technology 1999-2006

#ifndef AssocArray_cpp
#define AssocArray_cpp

#include "AssocArray.hpp"
#include <iostream>
using namespace std;

template <class V, class AI> 
	AssocArray<V, AI>::AssocArray()
{

	str = map<AI,V>();
	keys = Set<AI>();
}

template <class V, class AI> 
	AssocArray<V, AI>::AssocArray(const AssocArray<V, AI>& arr2)
{

	str = arr2.str;
	keys = arr2.keys;
}



// Construct the map from a list of names and a REPEATED val


template <class V, class AI> 
	AssocArray<V, AI>::AssocArray(const Set<AI>& names, const V& val)
{

	Set<AI>::const_iterator it;
	for (it = names.Begin(); it != names.End(); it++)
	{
		str.insert(pair<AI,V>(*it, val));

	}

	keys = names;
}

template <class V, class AI> 
	AssocArray<V, AI>& AssocArray<V, AI>::operator = (const AssocArray<V, AI>& ass2)
{
	if (&ass2 == this)
		return *this;


	 str = ass2.str;

	// Use copy algorithm to copy the maps
//	copy(ass2.str.begin(), ass2.end(), str.begin());
	
	keys = ass2.keys;

	return *this;

}


// New overloaded indexing operator
template <class V, class AI> 
	V& AssocArray<V, AI>::operator [] (const AI& index)
{

	return str[index];


}


// Iterator functions
template <class V, class AI> typename
AssocArray<V, AI>::iterator AssocArray<V, AI>::Begin()
{ // Return iterator at begin of composite

	return str.begin();
}

template <class V, class AI> typename
AssocArray<V, AI>::const_iterator AssocArray<V, AI>::Begin() const
{ // Return const iterator at begin of composite

	return str.begin();
}

template <class V, class AI> typename
AssocArray<V, AI>::iterator AssocArray<V, AI>::End()
{ // Return iterator after end of composite

	return str.end();
}

template <class V, class AI> typename
AssocArray<V, AI>::const_iterator AssocArray<V, AI>::End() const
{ // Return const iterator after end of composite

	return str.end();
}



#endif	// AssocArray_cpp