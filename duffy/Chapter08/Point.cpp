// Point.cpp
//
// Header file for Points in two dimensions. A given Point has 3 coordinates
// for compatibility with other systems. However, it is not possible to
// influence the third coordinate and furthermore, the delivered functionality
// is typically two-dimensional.
//
// Last Modifications:
// chap04 AM Kick off
// chap05 AM Changed using const and reference
// chap05 AM Added copy constructor
// 2005-5-20 DD modified POINT -> Point
//
// (C) Copyright Datasim BV 1995 - 2005

#include "Point.hpp"

// Private functions
void Point::init(double dx, double dy)
{
	x = dx;
	y = dy;
}

Point::Point()
{// Default constructor
	init(0.0, 0.0);
}

Point::Point(double newx, double newy)
{// Initialize using newx and newy
	init(newx, newy);
}

Point::Point(const Point& pt)
{// Copy constructor
	x = pt.x;
	y = pt.y;
}

Point::~Point()
{
}

double Point::getX() const
{
	return x;
}

double Point::getY() const
{
	return y;
}

// Arithmetic functions
Point Point::add(const Point& p) const
{
	return Point(x + p.x, y + p.y);
}

Point Point::subtract(const Point& p) const
{
	return Point(x - p.x, y - p.y);
}

Point Point::scale(const Point& p) const
{ // Scale a Point by another Point
	return Point(x * p.x, y * p.y);
}



// Copy
Point& Point::copy(const Point& p)
{// Copy p in current
	x = p.x;
	y = p.y;

	return *this;
}

// Output
ostream& operator << (ostream& os, const Point& p)
{ // Output to screen

	os << "Point: (" << p.getX() << ", " << p.getY() << ")" << endl;

	return os;

}
