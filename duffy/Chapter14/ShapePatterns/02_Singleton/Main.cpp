// Main.cpp
//
// Test program for basic shape hierarchy
//
// (C) Datasim Education BV 1998

#include "Point.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "OriginPoint.hpp"

using namespace std;

void main()
{
	Point p(3.0, 5.0);
 
	cout<<"Point: "<<p<<endl;
	cout<<"OriginPoint: "<<*OriginPoint::instance()<<endl;
	cout<<"Distance p to origin: "<<p.Distance()<<endl<<endl;

	OriginPoint::instance()->X(1.0);
	OriginPoint::instance()->Y(2.0);
	cout<<"OriginPoint changed to (1, 2): "<<*OriginPoint::instance()<<endl;
	cout<<"Distance p to origin: "<<p.Distance()<<endl<<endl;
}
