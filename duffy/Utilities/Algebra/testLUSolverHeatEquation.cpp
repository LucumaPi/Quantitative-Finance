// testLUSolverHeatEquation.cpp
//
// 2005-9-20 DD kick off
// 2005-9-26 DD new stuff fo IBVP
// 2005-10-9 DD code for exact solution of heat equation
// 2005-12-1 DD Heat equation null test exact solution from
// Smith 1978 page 15
// 2006-1-12 DD Former code modified in order to compare with
// a Crank-Nicolson solutuion solved at each time level using
// LU or DoubleSweep
//
// Good example to show how to present in Excel
//
// (C) Datasim Education BV 2005-2006
//
#include "ExcelMechanisms.hpp"
#include "vector.cpp"
#include "Mesher.hpp"
#include "StringConversions.hpp"
#include "LUSolver.cpp" // Template class
#include "DoubleSweep.cpp" // They are templates
#include <math.h>
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

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
//		return 2.0 * x;
		return -1.0;
	}

	//return 2.0 * (1.0 - x);
	return 1.0;
}



int main()
{

	// Now do the LU decomposition of this problem (NEW 2006)

	long J = 20;
	
	cout << "Number of space subdivisions: ";
	cin >> J;

	cout << "Number of time subdivisions: ";
	long N; cin >> N;

	double h = 1.0 / double(J);
	double k = 1.0 / double(N);

	/////// LU STUFF FIRST ////////////
	// Constructors with size, start index and value (Diagonals of matrix)
	// N.B. This is the Crank Nicolson scheme

	double A = 0.0; // LHS
	double B = 1.0;	// RHS

	double lambda =  k /(h*h);  
	cout << "Lambda " << lambda;

	// J intervals, thus J-1 UNKNOWN internal points
	Vector<double, long> a(J-1,1,	-lambda);
	Vector<double, long> b(J-1,1,	(2.0 + 2.0*lambda));
	Vector<double, long> c(J-1,1,	-lambda);
	Vector<double, long> r(J-1, 1);	// Right-hand side NOT CONSTANT ANYMORE

	// Create the mesh
	Range<double> range(A, B);
	Vector<double, long> XARR = range.mesh(J);
	print(XARR);

	// Initial condition
	Vector<double, long> vecOld	(XARR.Size(), XARR.MinIndex());	// At time n
//	print(vecOld);

	// For LU 
	Vector<double, long> vecNew(XARR.Size(), XARR.MinIndex());	// At time n+1
	// For DoubleSweep
	Vector<double, long> vecNew2(XARR.Size(), XARR.MinIndex());	// At time n+1

	vecOld[vecOld.MinIndex()] = 0.0;
	vecOld[vecOld.MaxIndex()] = 0.0;
	for (long j = vecOld.MinIndex()+1; j <= vecOld.MaxIndex()-1; j++)
	{
		vecOld[j] = InitialCondition(XARR[j]);
	}

	print(vecOld);
//	printOneExcel(XARR, vecOld);

	// OK, let's start
	double current = k;
	long n = 1;
L2:
	// Update at new time level n+1
	vecNew[vecNew.MinIndex()] = 0.0;
	vecNew[vecNew.MaxIndex()] = 0.0;
	vecNew2[vecNew2.MinIndex()] = 0.0;
	vecNew2[vecNew2.MaxIndex()] = 0.0;

	for (long jj = r.MinIndex(); jj <= r.MaxIndex(); jj++)
	{
		// Examine!! indices in vecOld, it's tricky but CORRECT
		r[jj] = (lambda*vecOld[jj]) + (2.0 - (2.0*lambda))*vecOld[jj+1] 
								+ (lambda*vecOld[jj+2]);
	}

	// Calculate RHS

	LUTridiagonalSolver<double, long> mySolver(a, b, c, r);

//	cout << "coeffs";
/*	print(a);
	print(b);
	print(c);
	print(r);

	int rr; cin >> rr;*/

	// The matrix must be diagonally dominant; we call the
	// assert macro and the programs stops

///	assert (mySolver.diagonallyDominant() == true);
	
	Vector<double, long> result = mySolver.solve();
//	print(result);
	for (long ii = vecNew.MinIndex()+1; ii <= vecNew.MaxIndex()-1;ii++)
	{
		vecNew[ii] = result[ii-1];
	}

	vecOld = vecNew;
//	print(vecNew);
//	int ff; cin >> ff;

//	print(XARR);
//	print(vecNew);
//	int y; cin >> y;
	//printOneExcel(XARR, vecNew);

	double LHS = vecNew2[vecNew2.MinIndex()];
	double RHS = vecNew2[vecNew2.MaxIndex()];
	DoubleSweep<double, long> mySweep( a, b, c, r, LHS, RHS);
	Vector<double, long> result2 = mySweep.solve();
//	print(result2);
//	cout << "double"; int fff; cin >> fff;
	for (long p = vecNew2.MinIndex()+1;p <=  vecNew2.MaxIndex()-1; p++)
	{
		vecNew2[p] = result2[p-1];
	}
	vecOld = vecNew2;

	n++;
	if (n < N)
	{
		current += k;
		goto L2;
	}
cout << "\n Difference " << lInfinityNorm(vecNew, vecNew2);
//print(vecNew2);
//print(vecNew);
	printOneExcel(XARR, vecNew, string("LU"));
	printOneExcel(XARR, vecNew2, string("Sweep"));

	return 0;
}