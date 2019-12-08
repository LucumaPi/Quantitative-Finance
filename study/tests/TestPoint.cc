// Testpoint.cpp
//
// Simple examples of using Point class.
//
// (C) Datasim Education BV 2006

#include <duffy/Point.hh>

int main()
{

	// Create a point
	Point p1;

	// Modify it cordinates
	p1.X(2.0);
	p1.Y(3.0);

	// Print it
	std::cout << "[" << p1.X() << "," << p1.Y() << "]" << std::endl;

	// Midpoint
	Point pL(0.0, 0.0);
	Point pR(1.0, 1.0);

	std::cout << pL; std::cout << pR;

	Point PM = pL.MidPoint(pR);
	std::cout << "Midpoint " << PM << std::endl;

	return 0;
}