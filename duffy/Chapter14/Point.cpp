// Point.cpp
//
// Point class.
//
// 5 june 1998	MB	Started
// 2006-4-14 DD for generic composite
//
// (C) Datasim Education BV 1998-2006

#include "Point.hpp"
#include <math.h>

void Point::init(double xs, double ys)
{ // Initialize the point

	x = xs;
	y = ys;
}

// Constructors and destructor
Point::Point(): Shape()
{ // Default constructor

	init(0.0, 0.0);
}

Point::Point(double xs, double ys): Shape()
{ // Normal constructor with coordinates
 
	init(xs, ys);
}


	
Point::Point(const Point &source): Shape(source)
{ // Copy constructor

	init(source.x, source.y);
}

Point:: ~Point()
{ // Destructor

} 

// Selectors
double Point::X() const
{// Return x
	return x;
}

double Point::Y() const
{// Return y
	return y;
}


double Point::Distance(const Point& p2) const
{ // Calculate distance between this point and second point 
  // To compute this, the law of Pythagoras is used: sqrt(dx^2 + dy^2)

	// If coordinates are equal, return distance of 0.0 
	if ((*this)==p2) return 0.0;   

	// Difference in x direction
	double dif_x = (x - p2.x);	

	// Difference in y direction 
	double dif_y = (y - p2.y);  

	// Calculate squares of coordinates
	dif_x *= dif_x;		
	dif_y *= dif_y;

	// Return square root
	return ::sqrt(dif_x + dif_y); 
}

Point Point::MidPoint(const Point& p2) const
{ // Calculate the point between the two points

	return Point( (x+p2.x)*0.5 , (y+p2.y)*0.5 );
}

// Operator overloading
bool Point::operator == (const Point& p2) const
{ // Return true if all coordinates are equal

	if ( (x==p2.x) && (y==p2.y) ) return true;

	return false;
}
// Modifiers
void Point::X(double NewX)
{// Set x
	x = NewX;
}

void Point::Y(double NewY)
{// Set y
	y = NewY;
}

// Operators
bool Point::operator != (const Point& p2) const
{ // Return false if all coordinates are equal
   
	return !(*this==p2);
}

Point& Point::operator = (const Point &source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	// Call base class assignment
	Shape::operator = (source);

	// Copy state
	init(source.x, source.y);    

	return *this;
}


