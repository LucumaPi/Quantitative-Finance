// TestSTD.cpp
//
// 2005-9-26 DD new stuff fo IBVP
// 2005-10-9 DD code for exact solution of heat equation
// 20-5-12-5 DD For heat equation, output in Excel

#include <duffy/IBVP.hh>
#include <duffy/STDImp.hh>
#include <duffy/IBVPSolver.hh>
#include <duffy/EEulerIBVPSolver.hh>
#include <duffy/IEulerIBVPSolver.hh>
#include <duffy/ArrayMechanisms.hh>
#include <duffy/MatrixMechanisms.hh>
//#include <duffy/ExcelMechanisms.hh>
#include <string>
#include <iostream>

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

	std::cout << "Number of space divisions: ";
	std::cin >> J;

	std::cout << "Number of time divisions: ";
	std::cin >> N;


	// ExplicitEulerIBVP fdm(i2, N, J);
//	print(fdm.result());
	

	ImplicitEulerIBVP fdm2(i2, N, J);
//	print(fdm2.result());

	// Display in Excel
//	std::cout << "calling function " << std::endl;
//	print(fdm2.TValues());
	try
	{
		std::cout << "...";
		//printMatrixInExcel(fdm2.result(), fdm2.TValues(), fdm2.XValues(), 
		//				std::string("IEuler"));
	//	printMatrixInExcel(fdm.result(), fdm.TValues(), fdm.XValues(), 
		//				std::string("EEuler"));
	//	printMatrixDifferenceInExcel(fdm.result(), fdm2.result(), fdm2.TValues(), fdm2.XValues(),
			//						std::string("Diff"));

	}
	catch (const std::string& errorString)
	{
		std::cout << errorString << std::endl;
	}

	std::cout << "called function " << std::endl;

	return 0;
}