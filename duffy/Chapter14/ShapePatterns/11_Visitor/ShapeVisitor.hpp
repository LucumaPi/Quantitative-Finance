// ShapeVisitor.hpp
//
// Base class for all shape visitors
//
// (C) Datasim Education BV 1998

#ifndef ShapeVisitor_hpp
#define ShapeVisitor_hpp

#include "Point.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "ShapeComposite.hpp"
#include "NameDecorator.hpp"

class ShapeVisitor
{
private:
public:
	// Constructors and Destructor
	ShapeVisitor();									// Default constructor
	ShapeVisitor(const ShapeVisitor& source);		// Copy constructor
	virtual ~ShapeVisitor();						// Destructor

	// The visit functions
	virtual void Visit(Point& p)=0;					// Visit point
	virtual void Visit(Line& l)=0;					// Visit line
	virtual void Visit(Circle& c)=0;				// Visit circle

	virtual void Visit(ShapeComposite& sc);			// Visit shape composite
	virtual void Visit(NameDecorator& nd);				// Visit name decorator

	// Operators
	ShapeVisitor& operator = (const ShapeVisitor& source);	// Assignment
};

#endif	// ShapeVisitor_hpp
