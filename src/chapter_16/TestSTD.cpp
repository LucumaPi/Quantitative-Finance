// TestSTD.cpp
//
// 2005-9-26 DD new stuff fo IBVP
// 2005-10-9 DD code for exact solution of heat equation
// 20-5-12-5 DD For heat equation, output in Excel

#include "ibvp.hpp"
#include "STDImp.hpp"
#include "IbvpSolver.hpp"
#include "EEuleribvpsolver.hpp"
#include "IEuleribvpsolver.hpp"
#include "arraymechanisms.cpp"
#include "matrixmechanisms.cpp"
#include "ExcelMechanisms.hpp"
#include <math.h>
#include <list>
#include <string>
#include <iostream>
using namespace std;

int main()
{

	// A. The Continuous Problem
	// Derived implementation class
	STDIBVPImp stdImp;
	
	// Now the client class IVP
	IBVPImp* myImp2 = &stdImp;

	double xmax = 1.0;
	Range<double> rangeX(0.0, xmax);
	Range<double> rangeT(0.0, 1.0);

	IBVP i2(*myImp2, rangeX, rangeT);

	// B. Finite Difference Schemes
	long J = 10;
	long N = 302;

	cout << "Number of space divisions: ";
	cin >> J;

	cout << "Number of time divisions: ";
	cin >> N;


//	ExplicitEulerIBVP fdm(i2, N, J);
//	print(fdm.result());
	

	ImplicitEulerIBVP fdm2(i2, N, J);
//	print(fdm2.result());

	// Display in Excel
//	cout << "calling function " << endl;
//	print(fdm2.TValues());
	try
	{
		cout << "...";
		printMatrixInExcel(fdm2.result(), fdm2.TValues(), fdm2.XValues(), 
						string("IEuler"));
	//	printMatrixInExcel(fdm.result(), fdm.TValues(), fdm.XValues(), 
		//				string("EEuler"));
	//	printMatrixDifferenceInExcel(fdm.result(), fdm2.result(), fdm2.TValues(), fdm2.XValues(),
			//						string("Diff"));

	}
	catch (const std::string& errorString)
	{
		cout << errorString << endl;
	}

	cout << "called function " << endl;


	return 0;
}