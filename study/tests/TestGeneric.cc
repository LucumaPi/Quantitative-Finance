// TestGenericPoint.cpp
//
// Testing generic points
//
// (C) Datasim Education BV 2006
//

// The file that actually contains the code must be included
#include <duffy/PointTemplate.hh>

int main()
{

	Point<double, double> p1(1.0, 1.0);
	Point<double, double> p2;			// Default point

	std::cout << "p1: " << p1 << std::endl;
	std::cout << "p2: " << p2 << std::endl;

	std::cout << "Distance between points: " << p1.Distance(p2) << std::endl;

	return 0;
}
