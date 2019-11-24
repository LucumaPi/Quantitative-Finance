// Testpoint.cpp
//
// Simple examples of using Point class.
//
// (C) Datasim Education BV 2006

#include "point.hpp"

#include <iostream>

int main()
{

	// Create a point
	Point p1;

	// Modify it cordinates
	p1.X(2.0);
	p1.Y(3.0);

	// Print it
	cout << "[" << p1.X() << "," << p1.Y() << "]" << endl;

	// Midpoint
	Point pL(0.0, 0.0);
	Point pR(1.0, 1.0);

	cout << pL; cout << pR;

	Point PM = pL.MidPoint(pR);
	cout << "Midpoint " << PM << endl;

	return 0;
}
