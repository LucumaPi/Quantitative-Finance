// PrintVisitor.hpp
//
// Shape visitor that prints the shapes
//
// (C) Datasim Education BV 1998

#ifndef PrintVisitor_hpp
#define PrintVisitor_hpp

#include "ShapeVisitor.hpp"

class PrintVisitor: public ShapeVisitor
{
private:

public:
	// Constructors and Destructor
	PrintVisitor();										// Default constructor
	PrintVisitor(const PrintVisitor& source);			// Copy constructor
	virtual ~PrintVisitor();							// Destructor

	// The visit functions
	virtual void Visit(Point& p);						// Visit point
	virtual void Visit(Line& l);						// Visit line
	virtual void Visit(Circle& c);						// Visit circle
	virtual void Visit(ShapeComposite& sc);				// Visit shape composite
	virtual void Visit(NameDecorator& nd);				// Visit name decorator

	// Operators
	PrintVisitor& operator = (const PrintVisitor& source);	// Assignment
};

#endif	// PrintVisitor_hpp
