// Main.cpp
//
// Test program for basic shape hierarchy
//
// (C) Datasim Education BV 1998

#include "Point.hpp"
#include "Line.hpp"
#include "Circle.hpp"

using namespace std;

void testPoint()
{
	cout<<endl<<endl<<"Point tests:"<<endl<<endl;

	Point p1;
	Point p2(1.0, 2.0);
	Point p3(Degree(30.0), 10.0);
	Point p4(Radian(PI), 5.0);
	Point p5(p4);

	cout<<"p1:                     "<<p1<<endl;
	cout<<"p2(1.0, 2.0):           "<<p2<<endl;
	cout<<"p3(Degree(30.0), 10.0): "<<p3<<endl;
	cout<<"p4(Radian(PI), 5.0):    "<<p4<<endl;
	cout<<"p5(p4):                 "<<p5<<endl<<endl;

	cout<<"p4==p5?: "<<(p4==p5)<<endl;
	cout<<"p4!=p5?: "<<(p4!=p5)<<endl;
	cout<<"p1==p4?: "<<(p1==p4)<<endl;
	cout<<"p1!=p4?: "<<(p1!=p4)<<endl<<endl;

	p1.X(2.0);
	p1.Y(1.0);
	cout<<"Setting p1 to (2.0, 1.0) using x- and y-properties: "<<p1<<endl;
	cout<<"Distance between p1 and origin(0,0): "<<p1.Distance()<<endl;
	cout<<"Distance between p1 and p2: "<<p1.Distance(p2)<<endl;
	cout<<"Midpoint between p1 and p2: "<<p1.MidPoint(p2)<<endl;
}

void testLine()
{
	cout<<endl<<endl<<"Line tests:"<<endl<<endl;

	Line l1;
	Line l2(Point(10.0, 5.0), Point(5.0, 10.0));
	Line l3(l2);

	cout<<"l1:                                     "<<l1<<endl;
	cout<<"l2(Point(10.0, 5.0), Point(5.0, 10.0)): "<<l2<<endl;
	cout<<"l3(l2):                                 "<<l3<<endl<<endl;

	cout<<"Length of l2:   "<<l2.Length()<<endl;
	cout<<"Midpoint of l2: "<<l2.MidPoint()<<endl;
}

void testCircle()
{
	cout<<endl<<endl<<"Circle tests:"<<endl<<endl;

	Circle c1;
	Circle c2(Point(4.0, 5.0), 2.0);
	Circle c3(Point(1.0, 1.0), Point(3.0, 3.0));
	Circle c4(c3);

	cout<<"c1:                                   "<<c1<<endl;
	cout<<"c2(Point(4.0, 5.0), 2.0):             "<<c2<<endl;
	cout<<"c3(Point(1.0, 1.0), Point(3.0, 3.0)): "<<c3<<endl;
	cout<<"c4(c3):                               "<<c4<<endl<<endl;

	cout<<"Area of c2: "<<c2.Area()<<endl;
	cout<<"Diameter of c2: "<<c2.Diameter()<<endl;
	cout<<"Point(5.0, 4.0) in c2?: "<<c2.Contains(Point(5.0, 4.0))<<endl;
	cout<<"Point(1.0, 4.0) in c2?: "<<c2.Contains(Point(1.0, 4.0))<<endl;
	cout<<"Distance op Point(5.0, 4.0) to c2?: "<<c2.Distance(Point(5.0, 4.0))<<endl;
	cout<<"Distance op Point(1.0, 4.0) to c2?: "<<c2.Distance(Point(1.0, 4.0))<<endl;
}

void main()
{
	testPoint();
	testLine();
	testCircle();
}