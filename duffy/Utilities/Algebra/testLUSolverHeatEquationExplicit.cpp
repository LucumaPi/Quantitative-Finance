// testLUSolverHeatEquationExplicit.cpp
//
// 2005-9-20 DD kick off
// 2005-9-26 DD new stuff fo IBVP
// 2005-10-9 DD code for exact solution of heat equation
// 2005-12-1 DD Heat equation null test exact solution from
// Smith 1978 page 15
// 2006-1-12 DD Former code modified in order to compare with
// a Crank-Nicolson solutuion solved at each time level using
// LU or DoubleSweep
// 2006-1-13 DD reduce scope, now Explicit
// 2006-1-14 DD Now working!
//
// Good example to show how to present in Excel
//
// (C) Datasim Education BV 2005-2006
//
#include "ExcelMechanisms.hpp"
#include "vector.cpp"
#include "StringConversions.hpp"
#include <vector>
#include <iostream>
using namespace std;
#include "matrixmechanisms.cpp"

//
//	See chapter 4 of FDM book for Fourier series solution
// 
// Use special code names for specific exact solutions
//
// We have three functions for presentation
//


//	1. Get the solution at one point (x,t)
//									: output double
//	2. Get the solution at a space array and one time (xarr, t)
//									: output Vector
//	3. Get solution for a space array for a number of time levels
//									: output list<Vector>
//
// This idea can be applied to other problems. For example, we could
// use function pointers 
//	
//				double (*f) (doible x, double t)
//
// Here are the steps for the IBV problem
//
//		Ut = Uxx for 0 < x < 1, t > 0
//		
//		BC U(0,t) = U(1,t) = 0, t > 0
//		IC
//				U(x,0) = 2x for 0 <= x <= 0.5
//				U(x,0) = 2(1-x) for 0.5 <= x <= 1.0
//


double InitialCondition(double x)
{
	if (x >= 0.0 && x <= 0.5)
	{
		return 2.0 * x;
	}

	return 2.0 * (1.0 - x);
			
}



int main()
{

	// Now do the LU decomposition of this problem (NEW 2006)

L1:
	long J = 20;

	cout << "Explicit Euler for 1d heat eqution\n";
	cout << "For stability, you need k <= h^2\n\n";
	
	cout << "Number of space subdivisions: ";
	cin >> J;

	cout << "Number of time subdivisions: ";
	long N; cin >> N;

	double T = 1.0;

	double h = 1.0 / double(J);
	double k = T / double(N);

	double lambda =  k /(h*h);  

	if (lambda > 1.0)
	{

		cout << "Lambda " << lambda << ", GREATER THAN 1\n";
		char ans;
		cout << "Carry on regardless (Yy/Nn)?";
		cin >> ans;
		if (ans == 'n' | ans == 'N')
		{
			goto L1;
		}
	}
	
	double A = 0.0; // LHS
	double B = 1.0;	// RHS

	// Create the mesh
	Range<double> range(A, B);
	Vector<double, long> XARR = range.mesh(J);
	
	// Initial condition
	Vector<double, long> vecOld	(XARR.Size(), XARR.MinIndex());	// At time n


	// For Explicit
	Vector<double, long> vecNewE(XARR.Size(), XARR.MinIndex());	// At time n+1

	vecOld[vecOld.MinIndex()] = 0.0;
	vecOld[vecOld.MaxIndex()] = 0.0;
	for (long j = vecOld.MinIndex()+1; j <= vecOld.MaxIndex()-1; j++)
	{
		vecOld[j] = InitialCondition(XARR[j]);
	}

	printOneExcel(XARR, vecOld,string("Initial"));

	// OK, let's start
	double current = k;
	long n = 1;
L2:
	// Update at new time level n+1
	vecNewE[vecNewE.MinIndex()] = 0.0;
	vecNewE[vecNewE.MaxIndex()] = 0.0;

	for (long jj = vecNewE.MinIndex()+1; jj <= vecNewE.MaxIndex()-1; jj++)
	{
		vecNewE[jj] = lambda*vecOld[jj-1] + (1.0 - (2.0*lambda))*vecOld[jj] 
								+ (lambda*vecOld[jj+1]);
	}

	
	vecOld = vecNewE;
	current += k;

	n++;
	if (n < N)
	{
		goto L2;
	}

	printOneExcel(XARR, vecNewE, string("Final"));

	return 0;
}