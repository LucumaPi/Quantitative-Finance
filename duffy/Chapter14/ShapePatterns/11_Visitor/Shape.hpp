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

class ShapeVisitor;

class Shape
{
public:
	// Constructors and destructor
	Shape();							// Default constructor
	Shape(const Shape& source);			// Copy constructor
	virtual ~Shape();					// Destructor
	
	// Special copy function to create a copy of a shape when you only have a shape pointer
	virtual Shape* Clone() const=0;		// Create a copy of the shape

	// Operator overloading
	Shape& operator = (const Shape& source);	// Assignment operator

	// Visitor functionality
	virtual void Accept(ShapeVisitor& v) = 0;	// Accept a visitor
};

#endif // Shape_hpp