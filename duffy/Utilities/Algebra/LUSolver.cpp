// matrixsolvermechanisms.cpp
//
// Classes and functions for solving linear systems of equations 
// (numerical linear algebra).
//
// Modification Dates:
//
//	DD 2003-1-14 First code (tridiagonal)
//	DD 2003-1-16 DD small corrections: still to code 2 member functions
//	DD 2003-8-2 LU decomposition of tridiagonal systems; 2 functions
//	(Boolean checks added)
//  DD 2003-8-5 Matrix iterative solvers (Jacobi, Gauss Seidel)
//	DD 2003-8-21 Debugging and good testing
//	DD 2003-9-1 Debugging Jacobi
//	DD 2004-4-10 New implementation using the Template Method pattern
//	DD 2004-4-11 Implement PSOR as a derived class. Lots of reuse
//  DD 2005-10-6 LU version for C++ Intro book. Optimised, no copy of arrays
//  DD 2005-10-15 Function to test diagonal dominance
//	DD 2006-1-10 Clean up cout stuff
//
// (C) Datasim Education BV 2003-2006

#ifndef LUSolver_CPP
#define LUSolver_CPP

#include "LUSolver.hpp"

template <class V, class I> void LUTridiagonalSolver<V,I>::calculateBetaGamma()
{ // Calculate beta and gamma

	// Size == J

	// Constructor derived from Array (size, startIndex [,value])
	beta = Vector<V,I> (Size, 1);
	gamma = Vector<V,I> (Size - 1, 1);

	beta[1] = b[1];
	gamma[1] = c[1] / beta[1];

	for (I j = 2; j <= Size-1; j++)
	{
		beta[j] = b[j] - (a[j] * gamma[j-1]);
		gamma[j] = c[j]/beta[j];

	}
	
	beta[Size] = b[Size] - (a[Size] * gamma[Size-1]);

}

template <class V, class I> void LUTridiagonalSolver<V,I>::calculateZU()
{ // Calculate z and u

	z = Vector<V,I> (Size, 1);
	u = Vector<V,I> (Size, 1);

	// Forward direction
	z[1] = r[1] / beta[1];

	for (I j = 2; j <= Size; j++)
	{
		z[j] = (r[j] - (a[j]*z[j-1]) ) / beta[j];
	
	}

	// Backward direction
	u[Size] = z[Size];

	for (I i = Size - 1; i >= 1; i--)
	{
		u[i] = z[i] - (gamma[i]*u[i+1]);
	
	}

}
	

template <class V, class I> LUTridiagonalSolver<V,I>::LUTridiagonalSolver()
{
	
	a = Vector<V,I> (1);
	b = Vector<V,I> (1);
	c = Vector<V,I> (1);
	r = Vector<V,I> (1);

	Size = 1;
}

template <class V, class I>	LUTridiagonalSolver<V,I>::LUTridiagonalSolver(Vector<V,I>& lower, Vector<V,I>& diagonal, Vector<V,I>& upper, Vector<V,I>& RHS)
{

	a = lower;
	b = diagonal;
	c = upper;
	r = RHS;

	Size = diagonal.Size();

}

template <class V, class I>	LUTridiagonalSolver<V,I>::LUTridiagonalSolver(const LUTridiagonalSolver<V,I>& source) 
{

	a = source.a;
	b = source.b;
	c = source.c;
	r = source.r;

	Size = source.Size;

}

	
template <class V, class I> LUTridiagonalSolver<V,I>::~LUTridiagonalSolver()
{

}
 	
// Assignment operator 
template <class V, class I>	LUTridiagonalSolver<V,I>& LUTridiagonalSolver<V,I>::operator = (const LUTridiagonalSolver<V,I>& source)
{
	
	if (this == &source)
		return *this;

	a = source.a;
	b = source.b;
	c = source.c;
	r = source.r;

	Size = source.Size;
}


// Calculate the solution to Au = r
template <class V, class I> Vector<V,I> LUTridiagonalSolver<V,I>::solve()
{
	//cout << "Solving " << endl;

	calculateBetaGamma();		// Calculate beta and gamma
	calculateZU();				// Calculate z and u

	return u;
	
}

template <class V, class I> bool LUTridiagonalSolver<V,I>::diagonallyDominant() const
{
	if (::fabs(b[1]) < ::fabs(c[1]))
		return false;

	if (::fabs(b[Size]) < ::fabs(a[Size]))
		return false;

	for (I j = 2; j <= Size-1; j++)
	{
		if (::fabs(b[j]) < ::fabs(a[j]) + ::fabs(c[j]) )
			return false;
	}

	
	return true; 
}

#endif