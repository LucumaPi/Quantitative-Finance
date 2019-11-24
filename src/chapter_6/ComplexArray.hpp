// ComplexArray.hpp
//
// Simple Complex Array class.
//
// (C) Datasim Education BV  1995-2003

#ifndef ComplexArray_hpp
#define ComplexArray_hpp

#include "Complex.hpp"

class ComplexArray
{
private:
	Complex* arr;
	int size;

	ComplexArray();

public:

	// Constructors & destructor
	ComplexArray(int size);
	ComplexArray(const ComplexArray& source);
	virtual ~ComplexArray();

	// Selectors
	int Size() const;
	int MinIndex() const;	// Smallest index in array
	int MaxIndex() const;	// Largest index in array

	// Operators
	const Complex& operator[](int index) const;	// Index operator for const ComplexArrays
	Complex& operator[](int index);				// Index operator for non const ComplexArrays

	ComplexArray& operator = (const ComplexArray& source);
};

#endif // ComplexArray_hpp
