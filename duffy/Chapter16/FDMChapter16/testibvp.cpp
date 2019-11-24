// tstbivp.cpp
//
// 2005-9-20 DD kick off
// 2005-9-26 DD new stuff fo IBVP
// 2005-10-9 DD code for exact solution of heat equation
//

#include "ibvp.hpp"
#include "ibvpsolver.cpp"
#include "arraymechanisms.cpp"
#include "matrixmechanisms.cpp"
#include "Instrument.hpp"
#include "exceldriver.cpp"
#include <math.h>
#include <list>
#include <string>
#include <iostream>
using namespace std;

InstrumentFactory* GetInstrumentFactory()
{

	// Only 1 factory in this version, like model T
	return new ConsoleInstrumentFactory;
}

int main()
{

	// A. The Continuous Problem
	// Derived implementation class
	STDIBVPImp stdImp;
	
	// Now the client class IVP
	IBVPImp* myImp2 = &stdImp;

	double Smax = 200.0;
	Range<double> rangeX(0.0, Smax);
	Range<double> rangeT(0.0, 1.0);

	IBVP i2(*myImp2, rangeX, rangeT);

	// B. Finite Difference Schemes
	long J = 5;
	long N = 50;
	ExplicitEulerIBVP fdm(i2, N, J);
//	print(fdm.result());
	

	int kk;
	cin >> kk;

	ImplicitIBVP fdm2(i2, N, J);
//	print(fdm2.result());

	// Display in Excel

	Mesher m(rangeX, rangeT);
	Vector<double, long> XARR = m.xarr(6);
//	Vector<double, long> vec = fdm.result()[2];
//	printOneExcel(XARR, vec, string("explicit");

//	Vector<double, long> vec2 = fdm2.result()[2];
//	printOneExcel(XARR, vec2, string("implicit");


	// Black Scholes example
	InstrumentFactory* myFactory = GetInstrumentFactory();
	Option* myOption = myFactory->CreateOption();

	// Derived implementation class
	BSIBVPImp bs (*myOption);
	bs.opt = myOption;

	// Now the client class IBVP
	IBVPImp* myImp3 = &bs;
	IBVP i3(*myImp3, rangeX, rangeT);
	ExplicitEulerIBVP fdm3(i3, N, J);
	print(fdm3.result());

//	printHE001();
//	printHE0012();

	return 0;
}