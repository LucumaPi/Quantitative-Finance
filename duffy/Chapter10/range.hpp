// range.hpp
//
// A class that represents a closed interval [low, high]. This is
// needed in many applications, for example candlestick charts in 
// financial futures. Other uses could be for the following types:
//
//	Date and time objects
//	Other numerical types as end-points
//	Any type that has an ordering < operator
//
//	This is a closed interval, thus a value at the end-points is 
//	considered to be in the range.
//
// (C) Datasim Education BV 2003 - 2005


#ifndef Range_HPP
#define Range_HPP

#include "vector.cpp"

template <class Type> class Range
{

private:

	Type lo;
	Type hi;
	Range(); // Default constructor

public:
	// Constructors
	Range(const Type& low, const Type& high);	// Low and high value
	Range(const Range<Type>& ran2);				// Copy constructor

	// Destructor
	virtual ~Range();

	// Modifier functions
	void low(const Type& t1);					// Sets the low value of current range
	void high(const Type& t1);					// Sets the high value of current range

	//Accessing functions
	Type low() const;							// Lowest value in range
	Type high() const;							// Highest value in the range

	Type length() const;						// High - Low value

	// Boolean functions
	bool left(const Type& value) const;			// Is the value to the left of the range?
	bool right(const Type& value) const;		// Is the value to the right of the range?
	bool contains(const Type& value) const;		// Does range contain value?

	// Subset/superset relations
	//bool subset (const Range<Type>& ran2); // IS 'this' a subset of ran2?
	//bool superset (const Range<Type>& ran2); // IS 'this' a superset of ran2?

	// Operator overloading
	Range<Type>& operator = (const Range<Type>& ran2);

};

#endif
