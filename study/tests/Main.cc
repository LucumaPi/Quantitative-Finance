// GenericMain.cpp
//
// Test program for basic shape hierarchy. Now using
// generic composite.
//
// (C) Datasim Education BV 1998

#include <duffy/Point.hh>
#include <duffy/Line.hh>
#include <duffy/GenericComposite.hh> // New!! template class
//#include "GenericVisitor.hpp" // New!! template class

void print(const GenericComposite<Shape>& sc)
{ // Print the shape composite

	GenericComposite<Shape>::const_iterator i;

	for (i=sc.Begin(); i!=sc.End(); i++)
	{
		const type_info& pp = typeid(*i);
		std::cout << pp.name() << std::endl;
	}

	std::cout << std::endl << std::endl;
}

int main()
{
	GenericComposite<Shape> sc;
	std::cout << "Empty composite: " << sc.Count() << std::endl;
	print(sc);

	Shape* s = new Point(1.0, 3.0);

	sc.AddBack(*s);
	std::cout << "1 shape: " << sc.Count() << std::endl;
	print(sc);

	Shape* s1 = new Line(Point(), Point());
	sc.AddBack(*s1);
	std::cout << "2 shapes: " << sc.Count() << std::endl;
	print(sc);

	Shape* s2 = new Line(Point(1,1), Point(1,2));
	sc.AddFront(*s2);
	std::cout << "3 shapes: " << sc.Count() << std::endl;
	print(sc);

	sc.RemoveLast();
	std::cout << "Remove last: " << sc.Count() << std::endl;
	print(sc);

	sc.RemoveAll();
	std::cout << "Remove all: " << sc.Count() << std::endl;
	print(sc);

	return 0;
}