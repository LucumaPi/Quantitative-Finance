// Main.cpp
//
// Test program for basic shape hierarchy
//
// (C) Datasim Education BV 1998

#include "Point.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "ShapeComposite.hpp"


using namespace std;

void print(const ShapeComposite& sc)
{ // Print the shape composite

	ShapeComposite::const_iterator i;

	for (i=sc.Begin(); i!=sc.End(); i++)
	{
		cout<<*(dynamic_cast<Point*>(*i))<<" ";
	}
	cout<<endl<<endl;
}

void main()
{
	ShapeComposite sc;
	cout<<"Empty composite: "<<sc.Count()<<endl;
	print(sc);

	sc.AddBack(new Point(1.0, 3.0));
	cout<<"1 shape: "<<sc.Count()<<endl;
	print(sc);

	sc.AddBack(new Point(2.0, 3.0));
	cout<<"2 shapes: "<<sc.Count()<<endl;
	print(sc);

	sc.AddFront(new Point(0.0, 3.0));
	cout<<"3 shapes: "<<sc.Count()<<endl;
	print(sc);

	ShapeComposite sc2(sc);

	print(sc2);

	sc.RemoveLast();
	cout<<"Remove last: "<<sc.Count()<<endl;
	print(sc);

	sc.RemoveAll();
	cout<<"Remove all: "<<sc.Count()<<endl;
	print(sc);
}
