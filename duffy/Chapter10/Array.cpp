// Array.cpp
//
// Simple templated array class.
//
// (C) Datasim Education BV  1995-2003

#ifndef Array_cpp
#define Array_cpp

#include "Array.hpp"


// Default constructor
template<class Type, int def_size>
Array<Type, def_size>::Array()
{
	// Create an array with default size
	m_data=new Type[def_size];
	m_size=def_size;
}

// Constructor with size
template<class Type, int def_size>
Array<Type, def_size>::Array(int size)
{
	m_data=new Type[size];
	m_size=size;
}

// Copy constructor
template<class Type, int def_size>
Array<Type, def_size>::Array(const Array<Type, def_size>& source)
{
	// Deep copy source
	m_size=source.m_size;
	m_data=new Type[m_size];
	for (int i=0; i<m_size; i++) m_data[i]=source.m_data[i];
}

// Destructor
template<class Type, int def_size>
Array<Type, def_size>::~Array()
{
	delete[] m_data;
}

// Get the size
template<class Type, int def_size>
int Array<Type, def_size>::Size() const
{
	return m_size;
}

// Index operator for const Arrays
template<class Type, int def_size>
const Type& Array<Type, def_size>::operator[](int index) const
{
	// Simple bounds checking. Should throw an exception.
	if (index<0 || index>=m_size) return m_data[0];
	return m_data[index];
}

// Index operator for non const Arrays
template<class Type, int def_size>
Type& Array<Type, def_size>::operator[](int index)
{
	// Simple bounds checking. Should throw an exception.
	if (index<0 || index>=m_size) return m_data[0];
	return m_data[index];
}

// Assignment operator
template<class Type, int def_size>
Array<Type, def_size>& Array<Type, def_size>::operator = (const Array<Type, def_size>& source)
{
	// Exit if same object
	if (this==&source) return *this;

	// Delete old memory
	delete[] m_data;

	// Deep copy source
	m_size=source.m_size;
	m_data=new Type[m_size];
	for (int i=0; i<m_size; i++) m_data[i]=source.m_data[i];

	return *this;
}

#endif // Array_cpp