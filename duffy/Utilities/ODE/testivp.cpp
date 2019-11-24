// tstivp.cpp
//
// 2005-9-20 DD kick off
//

#include "ivp.cpp"
//#include "ivpimp.cpp"
#include "ivpsolver.hpp"
#include "arraymechanisms.cpp"
#include <list>
#include <string>
#include <iostream>
using namespace std;

#include "exceldriver.cpp"

void printOneExcel(Vector<double, long> & x,						
					Vector<double, long>& functionResult,
					string& title)
{ 
	// N.B. Excel has a limit of 8 charts; after that you get a run-time error

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!

	excel.CreateChart(x, functionResult, title, "X", "Y");

	
}

void printInExcel(const Vector<double, long>& x,						// X array
					const list<string>& labels,							// Names of each vector
					const list<Vector<double, long> >& functionResult)	// The list of Y values
{ // Print a list of Vectors in Excel. Each vector is the output of
  // a finite difference scheme for a scalar IVP

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!


	
	excel.CreateChart(x, labels, functionResult, string("FDM IVP"),
						string("Time Axis"), string ("Value"));

	// Don't make the string names too long!!
//	excel.CreateChart(x, labels, functionResult, "Benchmark FDM", "Time", "FDM Value");


}

int main()
{
	// Bottom-up construction of objects

	// Parameter class 
	Option myOpt(0.20, 0.06);

	// Derived implementation class
	BSImp bs;
	bs.opt = myOpt;

	// Now the client class IVP
	IVPImp* myImp = &bs;

	IVP i1;
	i1.imp = myImp;
	i1.A = 1.0;

	std::cout << i1.a(1.0);
	std::cout << i1.f(1.0);

	// FD schemes
	EEulerIVP fdmE(i1,8.0);
	Vector<double, long> answer = fdmE.result();
	//print(answer);

	/// Another Implementation
	// Derived implementation class
	STDImp stdImp;
	
	// Now the client class IVP
	IVPImp* myImp2 = &stdImp;

	Range<double> range(0.0, 1.0);
	double initialValue = 1.0;
	IVP i2(*myImp2, range, initialValue);

	list<string> labels;							// Names of each vector
	list<Vector<double, long> > functionResult;		// The list of Y values

	int nSteps = 20;
	// FD scheme
	EEulerIVP fdmEA(i2, nSteps);
	Vector<double, long> answerA = fdmEA.result();
//	print(answerA);

	labels.push_back("Explicit Euler");
	functionResult.push_back(answerA);

	IEulerIVP fdmI(i2, nSteps);
	Vector<double, long> answer2 = fdmI.result();
	cout << "Implicit Euler\n";
	print(answer2);


	labels.push_back("Implicit Euler");
	functionResult.push_back(answer2);

	ExtrapEulerIVP fdmEx(i2, nSteps);
	Vector<double, long> answer3 = fdmEx.result();
//	print(answer3);

//	labels.push_back("Extrapolated Euler");
//	functionResult.push_back(answer3);

	FittedIVP fitted(i2, nSteps);
	Vector<double, long> answer4 = fitted.result();
//	print(answer4);

	labels.push_back("Fitted Implicit Euler");
	functionResult.push_back(answer4);

	FittedBoxIVP fittedbox(i2, nSteps);
	Vector<double, long> answer5 = fittedbox.result();
//	print(answer5);

	labels.push_back("Fitted Box");
	functionResult.push_back(answer5);

	PredictorCorrectorIVP pc(i2, nSteps);
	Vector<double, long> answer6 = fittedbox.result();
//	print(answer6);

	labels.push_back("Predictor Corrector");
	functionResult.push_back(answer6);

	// Print in Excel
	Vector<double, long> xresult(nSteps + 1, 1);
	xresult[xresult.MinIndex()] = 0.0;

	
	for (long j = xresult.MinIndex()+1; j <= xresult.MaxIndex(); j++)
	{
			xresult[j] = xresult[j-1] + fdmI.stepSize();
	}

	print (xresult);

	//print(fdir.current());

	printOneExcel(xresult, answerA, string("EE"));
	printOneExcel(xresult, answer3, string("Extrap Euler"));
	printOneExcel(xresult, answer4, string("Fitted Implicit"));
	printOneExcel(xresult, answer5, string("Fitted CN"));
	printOneExcel(xresult, answer2, string("IE"));
	printOneExcel(xresult, answer6, string("PredictorCorrector"));

	printInExcel(xresult, labels, functionResult);

	return 0;
}