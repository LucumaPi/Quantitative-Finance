// GenericMain.cpp
//
// Test program for basic shape hierarchy. Now using
// generic composite.
//
// (C) Datasim Education BV 1998

#include "Point.hpp"
#include "Line.hpp"
#include "GenericComposite.cpp" // New!! template class
//#include "GenericVisitor.hpp" // New!! template class
using namespace std;

void print(const GenericComposite<Shape>& sc)
{ // Print the shape composite

	GenericComposite<Shape>::const_iterator i;

	for (i=sc.Begin(); i!=sc.End(); i++)
	{
		const type_info& pp = typeid(*i);
		cout << pp.name() << endl;
	}

	cout<<endl<<endl;
}

int main()
{
	GenericComposite<Shape> sc;
	cout<<"Empty composite: "<<sc.Count()<<endl;
	print(sc);

	Shape* s = new Point(1.0, 3.0);

	sc.AddBack(*s);
	cout<<"1 shape: "<<sc.Count()<<endl;
	print(sc);

	Shape* s1 = new Line(Point(), Point());
	sc.AddBack(*s1);
	cout<<"2 shapes: "<<sc.Count()<<endl;
	print(sc);

	Shape* s2 = new Line(Point(1,1), Point(1,2));
	sc.AddFront(*s2);
	cout<<"3 shapes: "<<sc.Count()<<endl;
	print(sc);

	sc.RemoveLast();
	cout<<"Remove last: "<<sc.Count()<<endl;
	print(sc);

	sc.RemoveAll();
	cout<<"Remove all: "<<sc.Count()<<endl;
	print(sc);


	return 0;
}
