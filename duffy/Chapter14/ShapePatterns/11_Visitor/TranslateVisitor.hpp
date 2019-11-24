// TranslateVisitor.hpp
//
// Shape visitor that translates the shapes
//
// (C) Datasim Education BV 1998

#ifndef TranslateVisitor_hpp
#define TranslateVisitor_hpp

#include "ShapeVisitor.hpp"

class TranslateVisitor: public ShapeVisitor
{
private:
	Point pt;	// Translation

	Point Translate(const Point& p);					// Translate the point argument

public:
	// Constructors and Destructor
	TranslateVisitor();									// Default constructor
	TranslateVisitor(const Point& t);					// Constructor with translation
	TranslateVisitor(const TranslateVisitor& source);	// Copy constructor
	virtual ~TranslateVisitor();						// Destructor

	// The visit functions
	virtual void Visit(Point& p);						// Visit point
	virtual void Visit(Line& l);						// Visit line
	virtual void Visit(Circle& c);						// Visit circle
	virtual void Visit(ShapeComposite& sc);				// Visit shape composite
	virtual void Visit(NameDecorator& nd);				// Visit name decorator

	// Operators
	TranslateVisitor& operator = (const TranslateVisitor& source);	// Assignment
};

#endif	// TranslateVisitor_hpp
