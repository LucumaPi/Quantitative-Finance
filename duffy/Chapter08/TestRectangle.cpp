// Testrangle.cpp
//
// Good and bad rectangles, using inheritance and
// composition.
//
// (C) Copyright Datasim BV 2005
//

#include "rectangle.cpp"

#include <iostream>
using namespace std;


int main()
{

	cout << "Bad square: " << endl;
	BadSquare bs;
	bs.print();

	// Now change the size
	bs.setHeight(2.0);
	bs.print();

	cout << "Good square: " << endl;
	GoodSquare gs;
	gs.print();

	// Now change the size
	gs.setSize(2.0);
	gs.print();

	return 0;
}










