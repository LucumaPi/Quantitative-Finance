// Point.hpp
//
// Point class.
//
// (C) Datasim Education BV 1998-2006

#ifndef PointNew_HH
#define PointNew_HH

#include "Shape.hh"

class Point: public Shape
{ 
private:
	void init(double xs, double ys);

	// Properties for x- and y-coordinates
	double x;
	double y;

public:

	// Constructors and destructor
	Point();									// Default constructor
	Point(double xs, double ys);				// Construct with coordinates
	Point(const Point& source);					// Copy constructor
	virtual ~Point();							// Destructor

	// Selectors
	double X() const;							// Return x
	double Y() const;							// Return y
	double Distance(const Point& p2) const;		// Calculate distance between two points
	Point MidPoint(const Point& p2) const;		// Calculate the point between the two points

	// Modifiers
	void X(double NewX);							// Set x
	void Y(double NewY);							// Set y

	// Operator overloading
	bool operator == (const Point& p2) const;	// Return true if all coordinates are equal
	bool operator != (const Point& p2) const;	// Return false if not all coordinates are equal

	Point& operator = (const Point& source);	// Assignment operator
};
#endif // PointNew_HH