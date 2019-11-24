// testTridiagonalSolvers.cpp
//
// Testing matrix solvers (LU decomposition) and Godunov
// Double Sweep method
//
// 2006-1-10 DD Kick-off
//
// (C) Datasim Education BV 2003-2006

#include "LUSolver.cpp"
#include "DoubleSweep.cpp" // They are templates
#include "vector.cpp"
#include <iostream>
#include <assert.h>
#include "arraymechanisms.cpp"
#include "ExcelDriver.hpp"
#include "ExcelMechanisms.hpp"
#include "range.cpp"
using namespace std;

/* Solve BVP u'' = 1 in (0, 1) with u(0) = u(1) = 0
   Solution u(x) = x(x-1)/2 
   Solve by FDM */

int main()
{
	long J = 20;
	cout << "Number of steps J ";
	cin >> J;
	
	double h = 1.0 / double(J);

	// u(j-1) - 2u(j) + u(j+1) = h^2, j = 1, ..., J-1

	/////// LU STUFF FIRST ////////////
	// Constructors with size, start index and value (Diagonals of matrix)
	
	double A = 0.0; // LHS
	double B = 1.0;	// RHS

	// J intervals, thus J-1 UNKNOWN internal points
	Vector<double, long> a(J-1,1,	1.0);
	Vector<double, long> b(J-1,1,	-2.0);
	Vector<double, long> c(J-1,1,	1.0);
	Vector<double, long> r(J-1, 1, h*h);				// Right-hand side
	cout << "DD";
	/*
	for (long i = 1; i <= J; i++)
	{
		r[i] = 1;
	}*/
	
	LUTridiagonalSolver<double, long> mySolver(a, b, c, r);

	// The matrix must be diagonally dominant; we call the
	// assert macro and the programs stops

	assert (mySolver.diagonallyDominant() == true);
	
	Vector<double, long> result = mySolver.solve();

	Range<double> range(A, B);
	Vector<double, long> xarr = range.mesh(J);

	print(result);

	// Vector 'result' minus its end points
	Vector<double, long> fullVector(xarr.Size(), xarr.MinIndex());

	fullVector[fullVector.MinIndex()] = 0.0; // LHS BC
	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		fullVector[j+1] = result[j];
	}
	fullVector[fullVector.MaxIndex()] = 0.0; // RHS BC

	////////////// Double Sweep //////////////////////
	Vector<double, long> aa(J-1,1,	1.0);
	Vector<double, long> bb(J-1,1,	-2.0);
	Vector<double, long> cc(J-1,1,	1.0);
	Vector<double, long> rr(J-1,1,	h*h);	// Right-hand side

	// Boundary conditions
	double LHS = 0.0;
	double RHS = 0.0;

	DoubleSweep<double, long> mySweep( aa, bb, cc, rr, LHS, RHS);
	Vector<double, long> result2 = mySweep.solve();

	Vector<double, long> diff = result - result2;
	cout << "\nError " << lInfinityNorm(diff) << endl;
	Range<double> rangeShrunk(A+h, B-h);
	Vector<double, long> xarr2 = rangeShrunk.mesh(J-2);

	Vector<double, long> fullVector2(xarr.Size(), xarr.MinIndex());
	fullVector2[fullVector2.MinIndex()] = 0.0; // LHS BC
	for (long jj = result.MinIndex(); jj <= result.MaxIndex(); jj++)
	{
		fullVector2[jj+1] = result[jj];
	}

	fullVector2[fullVector2.MaxIndex()] = 0.0; // RHS BC
	printOneExcel(xarr, fullVector); // V2 exception handling
//	printOneExcel(xarr, fullVector2); // V2 exception handling
	
	return 0;
}
