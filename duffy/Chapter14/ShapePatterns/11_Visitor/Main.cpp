// Main.cpp
//
// Test program for basic shape hierarchy
//
// (C) Datasim Education BV 1998

#include "Point.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "TranslateVisitor.hpp"
#include "PrintVisitor.hpp"

using namespace std;

void main()
{
	// Create a print visitor
	PrintVisitor print;

	Point p1(0.0, 0.0);
	Line l1(Point(5, 10), Point(9, 3));
	Circle c1(Point(5, 7), 20);
	ShapeComposite sc;

	// Build Shapecomposite
	sc.AddBack(p1.Clone());
	sc.AddBack(l1.Clone());
	sc.AddBack(c1.Clone());

	print.Visit(p1); cout<<endl;
	print.Visit(l1); cout<<endl;
	print.Visit(c1); cout<<endl;
	print.Visit(sc); cout<<endl;

	// Create translate visitor to translate over 1,3
	TranslateVisitor v1(Point(1,3));
	TranslateVisitor v2(Point(-1,-3));

	// Translate the point, line and circle
	v1.Visit(p1);
	v1.Visit(l1);
	v1.Visit(c1);
	v1.Visit(sc);

	cout<<endl<<"Translated (1,3): "<<endl;
	print.Visit(p1); cout<<endl;
	print.Visit(l1); cout<<endl;
	print.Visit(c1); cout<<endl;
	print.Visit(sc); cout<<endl;

	// Translate back
	p1.Accept(v2);
	l1.Accept(v2);
	c1.Accept(v2);
	sc.Accept(v2);

	cout<<endl<<"Translated (-1,-3): "<<endl;
	p1.Accept(print); cout<<endl;
	l1.Accept(print); cout<<endl;
	c1.Accept(print); cout<<endl;
	sc.Accept(print); cout<<endl;
}
