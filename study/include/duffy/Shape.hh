// Shape.hpp
//
// Base class for shapes.
//
// 5-6-1998   MB  Started
// 2006-4-14 DD now in generic setting
//
// (C) Datasim Education BV 1998-2006

#ifndef SHAPE_HH
#define SHAPE_HH

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

#endif // SHAPE_HH