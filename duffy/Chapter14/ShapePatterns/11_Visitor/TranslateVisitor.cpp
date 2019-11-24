// TranslateVisitor.cpp
//
// Shape visitor that translates the shapes
//
// 4 november 1998	RD	Started
//
// (C) Datasim Education BV 1998

#include "TranslateVisitor.hpp"

// Constructors and Destructor
TranslateVisitor::TranslateVisitor(): ShapeVisitor()
{ // Default constructor

	pt=Point(0.0, 0.0);		// No translation
}

TranslateVisitor::TranslateVisitor(const Point& t): ShapeVisitor()
{ // Constructor with translation

	pt=t;
}

TranslateVisitor::TranslateVisitor(const TranslateVisitor& source): ShapeVisitor(source)
{ // Copy constructor

	pt=source.pt;
}

TranslateVisitor::~TranslateVisitor()
{ // Destructor
}


// The visit functions
void TranslateVisitor::Visit(Point& p)
{ // Visit point

	// Translate point
	p=Translate(p);
}

void TranslateVisitor::Visit(Line& l)
{ // Visit line

	// Translate the line points
	l.P1(Translate(l.P1()));
	l.P2(Translate(l.P2()));
}

void TranslateVisitor::Visit(Circle& c)
{ // Visit circle

	// translate center point
	c.CenterPoint(Translate(c.CenterPoint()));
}

void TranslateVisitor::Visit(ShapeComposite& sc)
{ // Visit shape composite

// If this visit function is not implemented then C++ tries to convert the 
// ShapeComposite to another Shape instead of calling the visit function 
// of the ShapeVisitor base class. We thus must alway implement this function

	// Call base class visit function
	ShapeVisitor::Visit(sc);
}

void TranslateVisitor::Visit(NameDecorator& nd)
{ // Visit NameDecorator

	ShapeVisitor::Visit(nd);
}


Point TranslateVisitor::Translate(const Point& p)
{ // Translate the point

	Point ptResult;

	// Translate point
	ptResult.X(p.X() + pt.X());
	ptResult.Y(p.Y() + pt.Y());

	return ptResult;
}

// Operators
TranslateVisitor& TranslateVisitor::operator = (const TranslateVisitor& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;

	// Call base assignment
	ShapeVisitor::operator = (source);

	pt=source.pt;

	return *this;
}