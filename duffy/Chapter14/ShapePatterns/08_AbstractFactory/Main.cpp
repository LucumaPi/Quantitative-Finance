// Main.cpp
//
// Test program for basic shape hierarchy
//
// (C) Datasim Education BV 1998

#include "Point.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "ShapeComposite.hpp"
#include "ConsoleFactory.hpp"

using namespace std;

ShapeFactory* CreateFactory()
{
	// Normally you would have to make a choice which factory
	// to instantiate
	return new ConsoleFactory();
}

void main()
{
	ShapeFactory* Factory;

	Factory = CreateFactory();

	Point* p;
	Circle* c;
	Line* l;

	p = Factory->CreatePoint();
	c = Factory->CreateCircle();
	l = Factory->CreateLine();

	std::cout << (*p) << std::endl;
	std::cout << (*c) << std::endl;
	std::cout << (*l) << std::endl;

	delete p;
	delete c;
	delete l;
	delete Factory;
}
