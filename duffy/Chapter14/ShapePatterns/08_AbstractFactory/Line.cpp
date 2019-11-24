// Line.cpp
//
// Class for lines
//
// Modification dates:
// 5 june 1998	MB	Started
//
// (C) Datasim Education BV 1998

#include "Line.hpp"

void Line::init(const Point& ps1, const Point& ps2)
{ // Initialize the line

	p1 = ps1;
	p2 = ps2;
}

// Constructors and destructor
Line::Line(): Shape()
{ // Default constructor

	init(Point(0.0, 0.0), Point(0.0, 0.0));
}

Line::Line(const Point& ps1, const Point& ps2): Shape()     
{ // Normal constructor, constructs line from two points

	init(ps1, ps2);
}

Line::Line(const Line& source): Shape(source)
{ // Copy constructor

	init(source.p1, source.p2);
}

Line::~Line()
{ // Destructor
}

// Selectors
Point Line::P1() const
{// Return p1
	return p1;
}

Point Line::P2() const
{// Return p2
	return p2;
}

double Line::Length() const	
{ // Calculate the distance between start- and endpoint

    return p1.Distance(p2);
}

Point Line::MidPoint() const
{ // Calculate the point in the middle of the line

	return p1.MidPoint(p2);
}
	

// Modifiers
void Line::P1(const Point& NewP1)
{// Set p1
	p1 = NewP1;
}

void Line::P2(const Point& NewP2)
{// Set p2
	p2 = NewP2;
}

// Special copy function to create a copy of a shape when you only have a shape pointer
Shape* Line::Clone() const
{// Create a copy of the shape
	return new Line(*this);
}

// Operator overloading	
Line& Line::operator = (const Line& source)		
{ // Assignment 

	// Exit if same object
	if (this==&source) return *this;

	// Call base class assignment
	Shape::operator = (source);

	// Copy state
	init(source.p1, source.p2);

	return *this;
}

std::ostream& operator << (std::ostream& os, const Line& l)
{ // Output line to ostream

	os<<"Line("<<l.p1<<", "<<l.p2<<")";
	return os;
}
