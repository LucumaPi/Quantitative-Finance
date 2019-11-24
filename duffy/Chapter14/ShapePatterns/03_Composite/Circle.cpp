// Circle.cpp
//
// Class for circles.
//
// Modification dates:
// 5 june 1998	MB	Started
//
// (C) Datasim Education BV 1998

#include "Circle.hpp"

void Circle::init(const Point& p, double r)
{ // Initialize circle

	centerpoint = p;	
	radius = r;
}

// Constructors and destructor
Circle::Circle(): Shape()
{ // Default constructor

	init(Point(0.0, 0.0), 1.0);
}

Circle::Circle(const Point& cp, double r): Shape()
{// Construct with centre point and radius
 
	init(cp, r);
}

Circle::Circle(const Point& p1, const Point& p2)
{ // Construct circle with two points

	init(p1.MidPoint(p2), p1.Distance(p2)*0.5);
}

Circle::Circle(const Circle& source): Shape(source)
{ // Copy constructor

	init(source.centerpoint, source.radius);
}

Circle::~Circle()
{ // Destructor
}
	
// Selectors
Point Circle::CenterPoint() const
{// Return the centerpoint
	return centerpoint;
}

double Circle::Radius() const
{// Return the radius
	return radius;
}

double Circle::Area() const
{ // Calculate area

	return radius*radius*PI;
}

double Circle::Diameter() const
{ // Calculate diameter

	return 2*radius;
}

bool Circle::Contains(const Point& p) const
{ // Return true if p lies within the circle

	// Calculate distance between p and centerpoint of circle
	double dst=p.Distance(centerpoint);
	
	// Point is within the circle if distance <= radius
	if (dst<=radius) return true;
	
	return false;
}

double Circle::Distance(const Point& p) const
{ // The distance between the circle and a point

	// If in the circle then distance is 0.0
	if (Contains(p)==true) return 0.0;

	// Else the distance is distance to centrepoint minus the radius
	return centerpoint.Distance(p)-radius;
}
		
// Operator overloading
Circle& Circle::operator = (const Circle& source)
{ // Assignment operator

	// Exit if same object
	if(this==&source) return *this;

	// Call base class assignment
	Shape::operator = (source);
    
	// Copy state
	init(source.centerpoint, source.radius);
        
	return *this;
}

std::ostream& operator << (std::ostream& os, const Circle& c)
{ // Output circle to ostream

	os<<"Circle("<<c.centerpoint<<", "<<c.radius<<")";
	return os;
}
