// Testrectangle.cpp
//
// Good and bad rectangles, using inheritance and
// composition.
//
// (C) Copyright Datasim BV 2005
//

#include "../src/Rectangle.cc"

int main()
{

	std::cout << "Bad square: " << std::endl;
	BadSquare bs;
	bs.print();

	// Now change the size
	bs.setHeight(2.0);
	bs.print();

	std::cout << "Good square: " << std::endl;
	GoodSquare gs;
	gs.print();

	// Now change the size
	gs.setSize(2.0);
	gs.print();

	return 0;
}










