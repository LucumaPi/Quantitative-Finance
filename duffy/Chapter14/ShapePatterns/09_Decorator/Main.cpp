// Main.cpp
//
// Test program for basic shape hierarchy
//
// (C) Datasim Education BV 1998

#include "Point.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "NameDecorator.hpp"
#include "ShapeComposite.hpp"

using namespace std;

void main()
{
	// Create a print visitor

	NameDecorator p1(Point(0.0, 0.0), "point");
	NameDecorator l1(Line(Point(5, 10), Point(9, 3)), "line");
	NameDecorator c1(Circle(Point(5, 7), 20), "circle");


	// Build Shapecomposite
	ShapeComposite sc;
	sc.AddBack(p1.Clone());
	sc.AddBack(l1.Clone());
	sc.AddBack(c1.Clone());



	// Print the shape called circle
	ShapeComposite::iterator it;
	NameDecorator* nd;

	cout<<endl<<"Find shape with name: circle"<<endl;
	for (it=sc.Begin(); it!=sc.End(); it++)
	{ // Search the composite

		nd=dynamic_cast<NameDecorator*>(*it);
		if (nd!=NULL)
		{
			if (nd->GetName()=="circle")
			{
				cout << (*nd);
			}
		}
	}

	for (it=sc.Begin(); it!=sc.End(); it++)
	{ // Search the composite

		nd=dynamic_cast<NameDecorator*>(*it);
		if (nd!=NULL)
		{
			cout << (*nd);
		}
	}

}
