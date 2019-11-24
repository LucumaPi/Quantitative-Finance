// TestCubicSpline.cpp
//
// Test cubic spline interpolator
//
// (C) Datasim Education BV 2006
//

#include "Vector.cpp"
#include "ExcelMechanisms.hpp"
#include <math.h>
#include <string>
using namespace std;

double func(double x)
{
	//return x*x*x + x*x;
	return ::sqrt(x);	// Compared with Schaum 
}

double NormalPdf(double x) 
{ // Probability function for Gauss fn.

	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);

}


double NormalCdf(double x)
{ // The approximation to the cumulative normal distribution


	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	double k = 1.0/(1.0 + (0.33267 * x));
	
	if (x >= 0.0)
	{
		return 1.0 - NormalPdf(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	}
	else
	{
		return 1.0 - NormalCdf(-x);
	}

}



#include "CubicSpline.hpp"
#include "ArrayMechanisms.cpp"

int main()
{

	long N = 16;
	double a = -4.0;		// Left of interval
	double b = 4.0;			// Right of interval
	double h = (b-a)/double(N);
	long startIndex = 0;

	Vector<double, long> xarr(N+1, startIndex,0.0);
	Vector<double, long> yarr(N+1, startIndex,0.0);

	for (long j = xarr.MinIndex(); j <= xarr.MaxIndex(); j++)
	{
		xarr[j] = a + h * double(j);
		//yarr[j] = func(xarr[j]);
		yarr[j] = NormalPdf(xarr[j]);

	}
	
	//print(xarr); print(yarr); int t; cin >> t;

	CubicSplineInterpolator csi(xarr, yarr, SecondDeriv);

	double result = csi.Solve(1.70);
	cout << "Interpolated value: " << (result);


	// Display arrays in Excel
	//printOneExcel(xarr, csi.Curve(), string("default curve"));

	// Now choose 1st order derivative at zero
	double leftBC = 1.0;
	double rightBC = -1.0;
	CubicSplineInterpolator csi2(xarr, yarr, FirstDeriv, leftBC, rightBC);

	// Display arrays in Excel
	printOneExcel(xarr, csi2.Curve(), string("curve 2"));
	return 0;
}