// Circle.hpp
//
// Class for circles.
//
// (C) Datasim Education BV 1998

#ifndef Circle_hpp
#define Circle_hpp

#include "Point.hpp"

class Circle: public Shape
{
private:
	// Private functions
	void init(const Point& cp, double rds);

	// Properties for centerpoint as radius
	Point centerpoint;				// Center point 
	double radius;					// Radius

public:

	// Constructors and destructor
	Circle();									// Default constructor
	Circle(const Point& cp, double r);			// Construct with centerpoint and radius
	Circle(const Point& p1, const Point& p2);	// Construct circle with two points
	Circle(const Circle& source);				// Copy constructor
	virtual ~Circle();							// Destructor

	// Selectors
	Point CenterPoint() const;					// Return the centerpoint
	double Radius() const;						// Return the radius
	double Area() const;						// Calculate the area
	double Diameter() const;					// Calculate diameter
	bool Contains(const Point& p) const;		// Does the circle contain the point
	double Distance(const Point& p) const;		// The distance between the circle and a point

	// Modifiers
	void CenterPoint(const Point& pt);			// Set the centerpoint

	// Special copy function to create a copy of a shape when you only have a shape pointer
	virtual Shape* Clone() const;		// Create a copy of the shape

	// Operator overloading
	Circle& operator = (const Circle& source);	// Assignment operator

	void Accept(ShapeVisitor& v);	// Accept a visitor

	// Friends
	friend std::ostream& operator << (std::ostream& os, const Circle& c);	// Output circle to ostream
};

#endif	// Circle_hpp