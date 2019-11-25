// ComplexArray.cpp
//
// Simple templated ComplexArray class.
//
// 2005-4-2 DD kick-off code
//
// (C) Datasim Education BV  1995-2006

#ifndef ComplexArray_cpp
#define ComplexArray_cpp

#include "ComplexArray.hpp"


// Default constructor
ComplexArray::ComplexArray()
{
	// Create an ComplexArray with default size == 1
	arr=new Complex[1];
	size=1;
}

// Constructor with size
ComplexArray::ComplexArray(int size)
{
	arr=new Complex[size];
	size=size;
}

// Copy constructor
ComplexArray::ComplexArray(const ComplexArray& source)
{
	// Deep copy source
	size=source.size;
	arr=new Complex[size];
	for (int i=0; i<size; i++) arr[i]=source.arr[i];
}

// Destructor
ComplexArray::~ComplexArray()
{
	delete[] arr;
}

// Get the size
int ComplexArray::Size() const
{
	return size;
}

int ComplexArray::MinIndex() const
{ // Smallest index in array
	
	return 0;
}

int ComplexArray::MaxIndex() const
{ // Largest index in array

	return size - 1;
}


// Index operator for const ComplexArrays
const Complex& ComplexArray::operator[](int index) const
{
	// Simple bounds checking. Should throw an exception.
	// if (index<0 || index>=size) return arr[0];

	return arr[index];
}

// Index operator for non const ComplexArrays
Complex& ComplexArray::operator[](int index)
{
	// Simple bounds checking. Should throw an exception.
	//	if (index<0 || index>=size) return arr[0];

	return arr[index];
}

// Assignment operator
ComplexArray& ComplexArray::operator = (const ComplexArray& source)
{
	// Exit if same object
	if (this==&source) return *this;

	// Delete old memory
	delete[] arr;

	// Deep copy source
	size=source.size;
	arr=new Complex[size];
	for (int i=0; i<size; i++) arr[i]=source.arr[i];

	return *this;
}

#endif // ComplexArray_cpp