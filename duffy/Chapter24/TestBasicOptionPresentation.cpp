// TestBasicOptionPresentation.cpp
//
// Test program for the  solutions of European options
//
// (C) Datasim Component Technology BV 2003-2006
//

#include "BasicOption.hpp"
#include "BasicOptionPresentation.hpp"
#include <iostream>

int main()
{ // All options are European

	

	// Put option on a stock index
	BasicOption indexOption;
	indexOption.otyp = "P";
	indexOption.K = 10.0;
	indexOption.T = 0.25;
	indexOption.r = 0.10;
	indexOption.sig = 0.40;

//	double q = 0.05;		// Dividend yield
	double q = 0.0;
	indexOption.b = indexOption.r - q;

	Range<double> extent (0.0, 50.0);
	long NumberSteps = 50;

	BasicOptionPresentation myPresent(indexOption, extent, NumberSteps);

	OptionValueType val = Value;
	myPresent.displayinExcel(val);

	val = Delta;
	myPresent.displayinExcel(val);


	return 0;
}
