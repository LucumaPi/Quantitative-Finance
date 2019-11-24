// Shape.hpp
//
// Base class for shapes.
//
// 5-6-1998   MB  Started
//
// (C) Datasim Education BV 1998

#ifndef Shape_hpp
#define Shape_hpp

#include "Common.hpp"
#include "Angle.hpp"

class Shape
{
public:
	// Constructors and destructor
	Shape();							// Default constructor
	Shape(const Shape& source);			// Copy constructor
	virtual ~Shape();					// Destructor
	
	// Operator overloading
	Shape& operator = (const Shape& source);	// Assignment operator
};

#endif // Shape_hpp