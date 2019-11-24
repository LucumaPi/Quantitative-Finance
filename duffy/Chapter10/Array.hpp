// Array.hpp
//
// Simple templated array class.
//
// (C) Datasim Education BV  1995-2003

#ifndef Array_hpp
#define Array_hpp


template<class Type, int def_size>
class Array
{
private:
	Type* m_data;
	int m_size;

public:

	// Constructors & destructor
	Array();
	Array(int size);
	Array(const Array<Type, def_size>& source);
	virtual ~Array();

	// Selectors
	int Size() const;

	// Operators
	const Type& operator[](int index) const;	// Index operator for const Arrays
	Type& operator[](int index);				// Index operator for non const Arrays

	Array<Type, def_size>& operator = (const Array<Type, def_size>& source);
};

#endif // Array_hpp
