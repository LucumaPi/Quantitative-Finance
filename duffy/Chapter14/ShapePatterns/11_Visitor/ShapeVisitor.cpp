// ShapeVisitor.cpp
//
// Base class for all shape visitors
//
// 16 september 1998	RD	Started

// (C) Datasim Education BV 1998

#include "ShapeVisitor.hpp"

// Constructors and Destructor
ShapeVisitor::ShapeVisitor()
{ // Default constructor
}

ShapeVisitor::ShapeVisitor(const ShapeVisitor& source)
{ // Copy constructor
}

ShapeVisitor::~ShapeVisitor()
{ // Destructor
}


void ShapeVisitor::Visit(ShapeComposite& sc)
{ // Visit shape composite
  // Override in subclasses to add extra behaviour

	ShapeComposite::iterator it;

	// Send all shapes in the composite to the visitor
	for (it=sc.Begin(); it!=sc.End(); it++)
	{
		(*it)->Accept(*this);
	}
}

void ShapeVisitor::Visit(NameDecorator& nd)
{ // Visit NameDecorator

	nd.GetShape()->Accept(*this);
}


// Operators
ShapeVisitor& ShapeVisitor::operator = (const ShapeVisitor& source)
{ // Assignment

	return *this;
}
