// Line.hpp
//
// Class for lines.
//
// (C) Datasim Education BV 1998

#ifndef Line_hpp
#define Line_hpp

#include "Point.hpp"

class Line: public Shape
{
private:
     void init(const Point& ps1, const Point& ps2);

 	// The start and end points as properties
	Point p1;
	Point p2;

public:

	// Constructors and destructor
	Line();										// Default constructor
	Line(const Point& ps1, const Point& ps2);	// Construct with points
	Line(const Line& source);					// Copy constructor
	virtual ~Line();							// Destructor

	// Selectors
	Point P1() const;							// Return p1
	Point P2() const;							// Return p2
	double Length() const;						// Calculate the length of the line
	Point MidPoint() const;						// Calculate the point in the middle of the line

	// Modifiers
	void P1(const Point& NewP1);				// Set p1
	void P2(const Point& NewP2);				// Set p2

   	// Special copy function to create a copy of a shape when you only have a shape pointer
	virtual Shape* Clone() const;		// Create a copy of the shape
  
	// Operator overloading	
	Line& operator = (const Line& source);		// Assignment operator	

	void Accept(ShapeVisitor& v);	// Accept a visitor

	// Friends
	friend std::ostream& operator << (std::ostream& os, const Line& l);	// Output line to ostream
};

#endif	// Line_hpp