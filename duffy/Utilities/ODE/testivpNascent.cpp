// tstivp.cpp
//
// 2005-9-20 DD kick off
//

#include "ivp.cpp"
//#include "ivpimp.cpp"
#include "ivpsolver.hpp"
#include "arraymechanisms.cpp"
#include "nascentdelta.hpp"
#include <list>
#include <string>
#include <iostream>
using namespace std;

double InterestRate(double x)
{
	return 0.6;
}

double NascentDeltaModifed(double x)
{
	// Coupon payment at 0.5 of a year

	double div = 1.0;
	return div * NormalNascentDelta(x - 0.5);
//	return div * CauchyNascentDelta(x - 0.5);
//	return div * RectangleNascentDelta(x - 0.5);
//	return div * CauchyPhiNascentDelta(x - 0.5);


}

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

	FunctionBasedImp fbImp;
	fbImp.RHS = NascentDeltaModifed;
	fbImp.Coeff = InterestRate; // Interest rate

	// Now the client class IVP
	IVPImp* myImp = &fbImp;
	
	Range<double> range(0.0, 2.0); // Two years
	IVP i2(*myImp, range, 2.0);

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
	Vector<double, long> yresult(nSteps + 1, 1);

	xresult[xresult.MinIndex()] = 0.0;
	yresult[yresult.MinIndex()] = NascentDeltaModifed(0.0);

	
	for (long j = xresult.MinIndex()+1; j <= xresult.MaxIndex(); j++)
	{
			xresult[j] = xresult[j-1] + fdmI.stepSize();
			yresult[j] = NascentDeltaModifed (xresult[j]);
	}

	print (xresult);

	//print(fdir.current());

	printOneExcel(xresult, answerA, string("EE"));
	printOneExcel(xresult, answer3, string("Extrap Euler"));
	printOneExcel(xresult, answer4, string("Fitted Implicit"));
	printOneExcel(xresult, answer5, string("Fitted CN"));
	printOneExcel(xresult, answer2, string("IE"));
	printOneExcel(xresult, answer6, string("PredictorCorrector"));
	printOneExcel(xresult, yresult, string("Nascent "));

	printInExcel(xresult, labels, functionResult);

	return 0;
}