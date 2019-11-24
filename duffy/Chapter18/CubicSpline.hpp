// CubicSpline.hpp
//
// Class to represent cubic spline interpolation
//
// Code is default inline and we include some C utility functions
//
// Last Modification Dates:
//
// DD 2006-7-31 Kick-off code
// DD 2006-8-1 Tested: 1) BC 2nd order terms
//
// (C) Datasim Education BV 2006
//

// All equations based on my C++ book, especially chapter 18

// Description: Given a set of mesh points Xarr (0 to N), a set of function values Yarr
// (0 to N) at these mesh points (see equation (18.1)) find the cubic spline function
// that agrees with Yarr at the mesh points and having either of the Boundary conditions
// as in Equation (18.7)

#include "LUSolver.cpp" // Process involves solution of a tridiagonal matrix
#include "Vector.cpp" 
#include "ArrayMechanisms.cpp"
#include <iostream>
#include <assert.h>

/* STEPS

	1. Give Xarr and Yarr (Same dimensions!)
	2. Give B.C. (eq. 18.7))
	3. Calculate the sub, main and superdiagonal arrays of LU matrix
	4. Solve AM = b (eq. 18.8)
	5. Choose the abscissa value 'x' where you want the interpolant.
	6. Use this value in the formula for the cubic spline S
*/

enum CubicSplineBC {SecondDeriv, FirstDeriv};

class CubicSplineInterpolator
{
private:
	Vector<double, long> x;		// Abscissa x-values
	Vector<double, long> y;		// Function values
	Vector<double, long> h;		// Array of mesh sizes in x direction

	CubicSplineBC type;			// Type of BC

	Vector<double, long> M;				// Special calculated coefficients of spline
	Vector<double, long> A, B, C, r;	// Input arrays for LU decomposition

	// For first order derivatives
	double a, b;

	// Number of subdivisions
	long N;

private:
		// Private member functions
		void calculateVectors()
		{ // A, B, C and r

			if (type == SecondDeriv)
			{ 
				C[C.MinIndex()] = 0.0;
				r[r.MinIndex()] = 0.0;

				A[A.MaxIndex()] = 0.0;
				r[r.MaxIndex()] = 0.0;
			}
			else
			{
				C[C.MinIndex()] = 1.0;
				r[r.MinIndex()] = 6.0 * ((y[1] - y[0]) - a)/h[1];

				A[A.MaxIndex()] = 1.0;
				r[r.MaxIndex()] = 6.0 * (b - (y[N] - y[N-1]))/h[N];
			}
		
			double tmp;

			for (long j = 1; j <= N-1; j++)
			{ // Optimise later

				C[j+1] = h[j+1]/(h[j] + h[j+1]);
				A[j] = h[j]/(h[j] + h[j+1]);

				tmp = (y[j+1] - y[j])/h[j+1] - (y[j] - y[j-1])/h[j];

				r[j+1] = (6.0 * tmp)/(h[j] + h[j+1]);
			}

			cout << "r";
			print(r);
		}
	
	long findAbscissa(double xvar) const
	{ // Will give index of LHS value <= x. Very simple algorithm

		long index = 0;

		print(x);
		cout << "/////xvar" << xvar << endl;

		for (long j = 0; j <= N-1; j++)
		{
			//cout << x[j] << "," << x[j+1] << "[[";
			if (x[j] <= xvar && xvar <= x[j+1])
			{
				return index;
			}
			index++;
		}
		// Then x is in the interval [j, j+1]

		cout << "index//// " << index << endl;
		return index;
	}

public:
	CubicSplineInterpolator(const Vector<double, long> xarr, 
								const Vector<double, long> yarr, 
									CubicSplineBC BCType, 
										double alpha = 0.0,	double beta = 0.0)
	{

		// Arrays must have the same size
		x = xarr;
		y = yarr;
		N = xarr.Size()-1;
		type = BCType;

	
		a = alpha;	// LHS
		b = beta;	// RHS

		// Redundant internal arrays
		long si = x.MinIndex() + 1;		// !! start index
		//cout << "si" << si;
		//int t; cin >> t;
		double defVal = 0.0;

		// Calculate array of offset
		h = Vector<double, long>(N, si, defVal);
		for (long j = 1; j <= N; j++)
		{
			h[j] = x[j] - x[j-1];
		}
		//print(h); cin >> t;

		// All arrays have start index 1
		// Compared to the equations in the book, M(j) --> M(j+1)
		M = Vector<double, long>(N+1, si, defVal); // Solution
		A = Vector<double, long>(N+1, si, defVal);
		B = Vector<double, long>(N+1, si, defVal + 2.0);
		C = Vector<double, long>(N+1, si, defVal);
		r = Vector<double, long>(N+1, si, defVal);


		// Calculate the elements 
		calculateVectors();

		print(A); print(B); print(C); int y; cin >> y;

		LUTridiagonalSolver<double, long> mySolver(A, B, C, r);

		// The matrix must be diagonally dominant; we call the
		// assert macro and the programs stops

		assert (mySolver.diagonallyDominant() == true);
	
		M = mySolver.solve();
		std::cout << "solution";
		print(M);


	}

	double Solve(double xvar) const
	{ // Find the interpolated valued at a value x)

		long j = findAbscissa(xvar);	// will give index of LHS value <= x
		cout << "index " << j << endl;
		// Now use the formula
		double tmp = xvar - x[j];
		double tmpA = x[j+1] - xvar;
		double tmp3 = tmp * tmp * tmp;
		double tmp4 = tmpA * tmpA * tmpA;

		double A = (y[j+1] - y[j])/h[j+1] - (h[j+1] * (M[j+2] - M[j+1]))/6.0;
		double B = y[j] - (M[j+1] * h[j+1] * h[j+1])/6.0; 

		double result = (M[j+1] * tmp4)/(6.0 * h[j+1])
							+ (M[j+2] * tmp3)/(6.0 * h[j+1])
								+ (A * tmp)
									+ B;
		return result;

	}
	
	Vector<double, long> Curve(const Vector<double, long>& xarr) const
	{ // Create the interpolated curve

		Vector<double, long> result(xarr.Size(), xarr.MinIndex());

		for (long j = xarr.MinIndex(); j <= xarr.MaxIndex(); j++)	
		{

			result[j] = Solve(xarr[j]);
		}

		return result;
	}

	Vector<double, long> Curve() const
	{ // Create the interpolated curve, MEMBER DATA AS ABSCISSAE

		return Curve(x);
	}
	
};


