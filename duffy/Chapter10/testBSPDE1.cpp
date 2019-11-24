// testBSPDE1.cpp
//
// Testing 1 factor BS model.
//
// (C) Datasim Education BV 2005
//

#include "fdmdirector.cpp"
#include "arraymechanisms.cpp"

#include <iostream>
#include <string>
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

// Excel output as well
void printInExcel(const Vector<double, long>& x,							// X array
					const list<string>& labels,							// Names of each vector
					const list<Vector<double, long> >& functionResult)	// The list of Y values
{ // Print a list of Vectors in Excel. Each vector is the output of
  // a finite difference scheme for a scalar IVP

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!


	// Don't make the string names too long!!
	excel.CreateChart(x, labels, functionResult, string("FDM Scalar IVP"),
						string("Time Axis"), string ("Value"));


}



double mySigma (double x, double t)
{

	double sigmaS = 0.30 * 0.30;

	return 0.5 * sigmaS * x * x;
}

double myMu (double x, double t)
{
	double r = 0.06;
	double D = 0.00;

	return (r - D) * x;
}

double myB (double x, double t)
{
	double r = 0.06;

	return  -r;
}

double myF (double x, double t)
{
	return 0.0;
}

double myBCL (double t)
{
 //return 0.0; // C
	
	double K = 10;
	double r = 0.06;
	double T = 1.0;
	return K * ::exp(-r * (T - t));
}

double myBCR (double t)
{
	double Smax = 100;
//	return Smax;

	
	return 0.0; // P
}

double myIC (double x)
{
	double K = 10;
	
	if (x < K)
		return -(x - K);

	return 0.0;

}


int main()
{
	using namespace BlackScholesOneFactorIBVP;

	// Assignment of functions
	sigma = mySigma;
	mu = myMu;
	b = myB;
	f = myF;
	BCL = myBCL;
	BCR = myBCR;
	IC = myIC;

	double T = 1.0;	int J= 200; int N = 4000-1;
	double Smax = 100.0;
	FDMDirector fdir(Smax, T, J, N);
	fdir.Start();

L1:
	fdir.doit();
	//	print(fdir.current());

	if (fdir.isDone() == false)
		goto L1;

	Vector<double, long> xresult(J+1, 1);
	xresult[xresult.MinIndex()] = 0.0;
	double h = Smax / (double) (J);

	for (long j = xresult.MinIndex()+1; j <= xresult.MaxIndex(); j++)
	{
			xresult[j] = xresult[j-1] + h;
	}

	print (xresult);
	//print(fdir.current());

	printOneExcel(xresult, fdir.current(), string("Value"));

	return 0;
}
