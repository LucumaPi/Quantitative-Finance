// ShapeFactory.cpp
//
// Base class for shape factories
//
// 6 november 1998	RD	Started
//
// (C) Datasim Education BV 1998

#include "ShapeFactory.hpp"

ShapeFactory::ShapeFactory()
{ // Default constructor
}

ShapeFactory::ShapeFatory(const ShapeFactory& source)
{ // Copy constructor
}

ShapeFactory::~ShapeFactory()
{ // Destructor
}

ShapeFactory& ShapeFactory::operator = (const ShapeFactory& source)
{ // Assignment

	return *this;
}
