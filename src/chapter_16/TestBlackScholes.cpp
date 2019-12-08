// TestBlackScholes.cpp
//
// 2005-9-20 DD kick off
// 2005-9-26 DD new stuff fo IBVP
// 2005-10-9 DD code for exact solution of heat equation
// 2005-12-9 DD Customised for BS n = 1 now
//
// Solver for one-factor Black Scholes equation. The output
// is in the form of a matrix (rows == t, columns == S).
//
// (C) Datasim Education BV 2006

#include "ibvp.hpp"
#include "ibvpsolver.hpp"
#include "BSImp.hpp"
#include "EEulerIbvpSolver.hpp"
#include "IEulerIbvpSolver.hpp"
#include "arraymechanisms.cpp"
#include "matrixmechanisms.cpp"
#include "Instrument.hpp"
#include "ExcelMechanisms.hpp"
#include "DatasimException.hpp"
#include <math.h>
#include <list>
#include <string>
#include <iostream>
using namespace std;

InstrumentFactory* GetInstrumentFactory()
{
	//cout << "Instrument Factory : 1=Console ";
	//int exStyle = 1; cin >> exStyle;
	// Only 1 factory in this version, like model T
	//if(exStyle == 1)
		return new ConsoleInstrumentFactory;
	
}

int main()
{
	// NOTE: We build up the object network based on the
	// UML class diagram in figure (16.1) (see chapter 16)

	// A. The Continuous Problem

	// Black Scholes example
	InstrumentFactory* myFactory = GetInstrumentFactory();
	Option* myOption = myFactory->CreateOption();
	myOption -> print();

	//cout << "1) European or 2) American style: ";
	//int exStyle = 1; cin >> exStyle;

	// Derived implementation class
	BSIBVPImp bsImp(*myOption);	// The BS PDE
	
	// Now the client class IVP
	IBVPImp* myImp = &bsImp;	// Pointer to base class

	/////////////////////// Geometry //////////////////////////

	// Define region in (S, t) space
	Range<double> rangeX(0.0, myOption->SMax);

	Range<double> rangeT(0.0, myOption ->T); // Time horizon
	/////////////////////// Geometry ////////////////////////////

	IBVP currentImp(*myImp, rangeX, rangeT);

	// B. Finite Difference Schemes
	long J = 5;
	long N = 50;
	cout << "Number of space divisions: ";
	cin >> J;

	cout << "Number of time divisions: ";
	cin >> N;

	cout << "Scheme 1) Explicit 2) Implicit: ";
	int ftype; cin >> ftype;
	ExplicitEulerIBVP fdm(currentImp, N, J);
	ImplicitEulerIBVP fdm2(currentImp, N, J);
	IBVPFDM* myFDM = &fdm;
	if (ftype != 1)
	{ 
		cout << "Implicit Euler ...\n";

		myFDM = &fdm2;
	}
	else
	{
		myFDM = &fdm;
	}


	// Display in Excel

	cout << "Output: 1) Cell(matrix), 2) list of line graphs: ";
	int choice; cin >> choice;


	if (choice == 1)
	{
		try
		{
			printMatrixInExcel(myFDM->result(), fdm.TValues(), fdm.XValues(), 
						string("BSEulerE"));

			//print(myFDM->result());
		}
		catch (DatasimException& e)
		{
			e.print();
			return 0;
		}
	}
	if (choice == 2)
	{
		cout << "Frequency of output: "; int f; cin >> f;
		
		try 
		{   // Matrix is (N+1)X(J+1), TValues == N+1, XValues == J+1
			printMatrixChartsInExcel(f, myFDM->result(), fdm.TValues(), fdm.XValues(),
					string("BSEulerI"));

		//	print(myFDM->result());
		}
		catch (DatasimException& e)
		{
			e.print();
			return 0;
		}
	}

	
	return 0;
}