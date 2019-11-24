// Main.cpp
//
// Test program for basic shape hierarchy
//
// (C) Datasim Education BV 1998

#include "Point.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "ShapeComposite.hpp"
#include "ApproxDistance.hpp"
using namespace std;

void main()
{
	Point p1(10,20);
	Point p2(30,30);

	cout << "Distance is : " << p1.Distance(p2) << endl;

	Point::SetStrategy(ApproxDistance::Instance());

	cout << "Distance is : " << p1.Distance(p2) << endl;
}
