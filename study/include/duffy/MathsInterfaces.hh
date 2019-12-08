#ifndef MathsInterfaces_HH
#define MathsInterfaces_HH

// Simulate C# in C++ for a possible migration
#define interface struct

template <class V, class I = int>
interface IOneDimensionalAccess
{
	// Operators
	virtual V& operator [] (I index) = 0;				// Subscripting operator
};

template <class V, class I = int>
interface ITwoDimensionalAccess
{
	// Operators
	virtual V& operator () (I row, I column) = 0;	// Get the element at position
};
#endif