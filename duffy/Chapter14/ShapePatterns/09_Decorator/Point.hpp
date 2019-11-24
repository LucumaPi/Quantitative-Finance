// Point.hpp
//
// Point class.
//
// (C) Datasim Education BV 1998

#ifndef Point_hpp
#define Point_hpp

#include "Shape.hpp"
#include "DistanceStrategy.hpp"

class Point: public Shape
{ 
private:
	void init(double xs, double ys);

	// Properties for x- and y-coordinates
	double x;
	double y;

static DistanceStrategy* pStrategy;

public:

	// Constructors and destructor
	Point();									// Default constructor
	Point(double xs, double ys);				// Construct with coordinates
	Point(const Angle& angle, double radius);	// Construct with polar coordiantes (angle in radians)
	Point(const Point& source);					// Copy constructor
	virtual ~Point();							// Destructor

	// Selectors
	double X() const;							// Return x
	double Y() const;							// Return y
	double Distance() const;					// Calculate distance between point and origin
	double Distance(const Point& p2) const;		// Calculate distance between two points
	Point MidPoint(const Point& p2) const;		// Calculate the point between the two points

	// Modifiers
	void X(double NewX);							// Set x
	void Y(double NewY);							// Set y

	// Operator overloading
	bool operator == (const Point& p2) const;	// Return true if all coordinates are equal
	bool operator != (const Point& p2) const;	// Return false if not all coordinates are equal

	// Special copy function to create a copy of a shape when you only have a shape pointer
	virtual Shape* Clone() const;		// Create a copy of the shape

	Point& operator = (const Point& source);	// Assignment operator

	// Static functions
	static void SetStrategy(DistanceStrategy* strategy);

	// Friends
	friend std::ostream& operator << (std::ostream& os, const Point& p);	// Output point to ostream
};

#endif // Point_hpp
