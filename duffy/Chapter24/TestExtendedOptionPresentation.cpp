// TestExtendedOption.cpp
//
// Test program for the  solutions of European options
//
// (C) Datasim Component Technology BV 2003-2006
//

#include "ExtendedOptionPresentation.hpp"
#include "arraymechanisms.cpp"
#include "range.cpp"
#include <iostream>

int main()
{ // All options are European

	// Call option on a stock
	ExtendedOption callOption;
	cout << "Call option on a stock: " << callOption.Price(60.0) << endl;
	
	// Put option on a stock index
	ExtendedOption indexOption;
	indexOption.otyp = "P";
	indexOption.K = 95.0;
	indexOption.T = 0.5;
	indexOption.r = 0.06;
	indexOption.sig = 0.20;

	double q = 0.0; // 0.05;		// Dividend yield
	//indexOption.b = indexOption.r - q;
	indexOption.b = indexOption.r; // stock

	cout << "Put option on an index: " << indexOption.Price(100.0) << endl;


	Range<double> extent (0.01, 210.01);
	long NumberSteps = 210;

	ExtendedOptionPresentation myPresent(indexOption, extent, NumberSteps);

	OptionValueType val = Value;
	myPresent.displayinExcel(val);

	val = Delta;
	myPresent.displayinExcel(val);

	val = Gamma;
	myPresent.displayinExcel(val);

	val = Vega;
	myPresent.displayinExcel(val);

	val = Theta;
	myPresent.displayinExcel(val);

	val = Rho;
	myPresent.displayinExcel(val);

	val = Coc;
	myPresent.displayinExcel(val);

	return 0;
}
