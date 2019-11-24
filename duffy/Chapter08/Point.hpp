// Point.hpp
//
// Header file for Points in two dimensions. A given Point has 3 coordinates
// for compatibility with other systems. However, it is not possible to
// influence the third coordinate and furthermore, the delivered functionality
// is typically two-dimensional.
//
// (C) Copyright Datasim BV 1995 - 2005

#ifndef Point_HPP
#define Point_HPP

#include <iostream>
using namespace std;

class Shape
{
};

class Point : public Shape
{
private:
	double x;	// X coordinate
	double y;	// Y coordinate

	void init(double dx, double dy);

public:
	// Constructors
	Point();								// Default constructor
	Point(double xval, double yval);		// Initialize with x and y value
	Point(const Point& pt);					// Copy constructor
	~Point();								// Destructor

	// Accessing functions
	double getX() const;					// The x-coordinate
	double getY() const;					// The y-coordinate

	// Arithmetic functions
	Point add(const Point& p) const;		// Return current + p
	Point subtract(const Point& p) const;	// Return current - p
	Point scale(const Point& pt) const;		// Return current * p


	// Copy
	Point& copy(const Point& p);			// Copy p in current

};

	ostream& operator << (ostream& os, const Point& p);

#endif // Point_HXX

