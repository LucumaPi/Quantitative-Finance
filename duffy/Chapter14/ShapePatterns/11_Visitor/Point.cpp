// Point.cpp
//
// Point class.
//
// 5 june 1998	MB	Started
//
// (C) Datasim Education BV 1998

#include "Point.hpp"
#include "OriginPoint.hpp"
#include "ExactDistance.hpp"
#include "ShapeVisitor.hpp"

DistanceStrategy* Point::pStrategy = ExactDistance::Instance();

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

Point::Point(const Angle& angle, double radius)
{ // Construct point using polar coordinates

	init(radius*angle.cos(), radius*angle.sin());
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

double Point::Distance() const
{ // Calculate distance between point and origin(0,0)

	return Distance(*OriginPoint::instance());
}

double Point::Distance(const Point& p2) const
{ // Calculate distance between this point and second point 
  // To compute this, we use the strategy

	return pStrategy->Distance(*this,p2);
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

// Special copy function to create a copy of a shape when you only have a shape pointer
Shape* Point::Clone() const
{// Create a copy of the shape
	return new Point(*this);
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

void Point::Accept(ShapeVisitor& v)
{// Accept a visitor
	v.Visit(*this);
}

std::ostream& operator << (std::ostream& os, const Point& p)
{ // Output point to ostream

	os<<"Point("<<p.x<<", "<<p.y<<")";
	return os;
}

void Point::SetStrategy(DistanceStrategy* strategy)
{
	pStrategy = strategy;
}