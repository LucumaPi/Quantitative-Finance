// ArrayStructure.hpp
//
// Base class for array storage structure.
// A size_t is used for indexing. Indexing starts at 1 in this class and its
// derived classes. These derived classes must implement the indexing [] operator.
//
// (C) Datasim Component Technology 1999

#ifndef ArrayStructure_HH
#define ArrayStructure_HH
#include <cstddef>

template <class V>
class ArrayStructure
{
public:
	// Constructors & destructor
	ArrayStructure();												// Default constructor
	ArrayStructure(const ArrayStructure<V>& source);				// Copy constructor
	virtual ~ArrayStructure();										// Destructor

	// Selectors
	virtual std::size_t Size() const=0;									// Size of the array
	const V& Element(std::size_t index) const;						// Get element at position

	std::size_t MinIndex() const;									// Return the minimum index == 1
	std::size_t MaxIndex() const;									// Return the maximum index == size

	// Modifiers
	void Element(size_t index, const V& val);					// Change element at position

	// Operators
	virtual V& operator[] (std::size_t index) = 0;			
	virtual const V& operator[] (std::size_t index) const = 0;

	ArrayStructure<V>& operator = (const ArrayStructure<V>& source);
};
#include "../../src/ArrayStructure.cc"
#endif	// ArrayStructure_HH