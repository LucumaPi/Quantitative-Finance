// FullArray.hpp
//
// Template class for a full (non-sparse) arrays.
//
// (C) Datasim Component Technology 1999

#ifndef FullArray_HH
#define FullArray_HH

// Use the STL vector class
#include <vector>
#include "ArrayStructure.hh"

template <class V, class TA=std::allocator<V> >
class FullArray: public ArrayStructure<V>
{
private:
	std::vector<V, TA> m_vector;								// Use STL vector class for storage

public:
	// Constructors & destructor
	FullArray();											
	FullArray(size_t size);									
	FullArray(const FullArray<V, TA>& source);				
	virtual ~FullArray();									

	// Selectors
	virtual size_t Size() const;

	// Modifiers

	// Operators
	V& operator[] (size_t index);							
	const V& operator[] (size_t index) const;				

	FullArray<V, TA>& operator = (const FullArray<V, TA>& source);
};

#include "../../src/FullArray.cc"
#endif	// FullArray_HH