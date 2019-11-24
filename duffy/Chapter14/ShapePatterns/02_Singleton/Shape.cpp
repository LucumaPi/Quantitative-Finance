// Shape.cpp
//
// Base class for shapes.
//
// 5 june 1998	MB	Started
//
// (C) Datasim Education BV 1998

#include "Shape.hpp"

// Constructors and destructor
Shape::Shape()
{ // Default constructor
}

Shape::Shape(const Shape& source)
{ // Copy constructor
}

Shape:: ~Shape()
{ // Destructor
}

// Operator overloading
Shape& Shape::operator = (const Shape& source)
{ // Assignment operator

	return *this;
}
