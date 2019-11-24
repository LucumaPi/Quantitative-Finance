// testComplexLUSolver.cpp
//
// Testing matrix solvers (LU decomposition). In this
// case we use complex-valued matrices.
//
// (C) Datasim Education BV 2003-2006

#include "LUSolver.cpp"
#include "vector.cpp"
#include "complex.hpp"
#include "arraymechanisms.cpp"
//using namespace std;


int main()
{
	size_t J = 10;


	Vector<Complex, long> a(J,1,	Complex(1.0, 0.0));
	Vector<Complex, long> b(J,1,	Complex(2.0, 0.0));
	Vector<Complex, long> c(J,1,	Complex(1.0, 0.0));
	Vector<Complex, long> r(J,1,	Complex(0.0, 0.0));				// Right-hand side

	
	for (long i = 1; i <= J; i++)
	{
		r[i] = Complex(1.0, 0.0);
	}
	

	print(a);
	print(b);
	print(c);
	print(r);

	LUTridiagonalSolver<Complex, long> mySolver(a, b, c, r);
	Vector<Complex, long> result = mySolver.solve();
	print(result);

	J = 2;
	Vector<Complex, long> A(J,1,	Complex(1.0, 0.0));
	Vector<Complex, long> B(J,1,	Complex(0.0, 1.0));
	Vector<Complex, long> C(J,1,	Complex(1.0, 0.0));
	Vector<Complex, long> R(J,1,	Complex(0.0, 0.0));				// Right-hand side
	R[1] = Complex(0.0, 2.0);

	LUTridiagonalSolver<Complex, long> mySolver2(A, B, C, R);
	Vector<Complex, long> result2 = mySolver2.solve();
	print(result2);

	return 0;
}
