// testLU.cpp
//
// Testing matrix solvers (LU decomposition)
//
// (C) Datasim Education BV 2003-2006

#include "LUSolver.cpp"
#include "vector.cpp"
#include <iostream>
#include <assert.h>
#include "arraymechanisms.cpp"
using namespace std;


int main()
{
	size_t J = 400;
	int j = 1;

L1:

	// First test case, trivial solution == 1 (the sanity check)
	// Constructors with size, start index and value (Diagonals of matrix)
/*	Vector<double, long> a(J,1,	0.0);
	Vector<double, long> b(J,1,	0.5);
	Vector<double, long> c(J,1,	0.0);
*/

	Vector<double, long> a(J,1,	1.0);
	Vector<double, long> b(J,1,	2.0);
	Vector<double, long> c(J,1,	1.0);
	Vector<double, long> r(J, 1, 0.0);				// Right-hand side
/*

	Vector<double, long> a(J,1,	1.0);
	Vector<double, long> b(J,1,	0.0); // OOPS
	Vector<double, long> c(J,1,	1.0);
	Vector<double, long> r(J, 1, 0.0);				// Right-hand side
*/
	
	for (long i = 1; i <= J; i++)
	{
		r[i] = 1;
	}
	

/*	print(a);
	print(b);
	print(c);
	print(r);*/



	LUTridiagonalSolver<double, long> mySolver(a, b, c, r);

	// The matrix must be diagonally dominant; we call the
	// assert macro and the programs stops

	assert (mySolver.diagonallyDominant() == true);
	
	Vector<double, long> result = mySolver.solve();
	
	if (j < 10000)
	{
		j++;
		cout << j;
		goto L1;
	}

//	print(result);


	return 0;
}
