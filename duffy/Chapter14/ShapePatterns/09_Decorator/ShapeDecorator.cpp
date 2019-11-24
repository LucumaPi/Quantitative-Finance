// ShapeDecorator.hpp
//
// Base class for shape decorators
//
// 5 november 1998	RD	Started
//
// (C) Datasim Education BV 1998

#include "ShapeDecorator.hpp"

ShapeDecorator::ShapeDecorator(): Shape()
{ // Default constructor

	shape=NULL;
}

ShapeDecorator::ShapeDecorator(const Shape& s): Shape(s)
{ // Normal constructor

	shape=s.Clone();
}

ShapeDecorator::ShapeDecorator(const ShapeDecorator& source): Shape(source)
{	// Copy constructor

	shape=source.shape->Clone();
}

ShapeDecorator::~ShapeDecorator()
{ // Destructor

	// Delete the contained shape
	if (shape!=NULL) delete shape;
}

Shape* ShapeDecorator::getShape() const
{ // Return the shape pointer

	return shape;
}

// Operators
ShapeDecorator& ShapeDecorator::operator = (const ShapeDecorator& source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	// Call base assignment
	Shape::operator = (source);

	shape=source.shape->Clone();

	return *this;
}