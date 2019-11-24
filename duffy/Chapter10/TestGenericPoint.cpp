// TestGenericPoint.cpp
//
// Testing generic points
//
// (C) Datasim Education BV 2006
//

// The file that actually contains the code must be included
#include "point.cpp"
#include <iostream.h>
//using namespace std;

int main()
{

	Point<double, double> p1(1.0, 1.0);
	Point<double, double> p2;			// Default point

	cout << "p1: " << p1 << endl;
	cout << "p2: " << p2 << endl;

	cout << "Distance between points: " << p1.Distance(p2) << endl;

	return 0;
}
