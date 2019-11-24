// parabolicFDM.cpp
//
// Finite difference method for Parabolic PDE.
//
// Last modification dates:
//
//	2000-7-30 DD kick-off code. The member 'theta' is for a future version
//	2000-8-1 DD more improvements, specific use of Array code
//	2000-8-2 DD getting ready for Robert and Jasmin
//	2001-1-30 DD debugging and checking (heavy overhaul)
//	2001-2-10 DD 'improvements'
//	2002-1-8 DD Cleaning up mostly
//  2002-4-9 DD Later on the discrete A, B, C and F can be replaced by one generic function
//  2002-17-5 RM coth added to ParabolicFDM class (RM = R. Mirani)
//  2002-17-5 RM functions ::A, ::B and ::C changed to internal note 1 format
//  2002-17-5 RM some small errors in ::init()
//  2002-21-5 RM current now initialized (to 0) in constructor
//	2002-21-5 RM Completely new advance() function
//  2002-21-5 RM initial condition IC() added
//  2002-21-5 RM function start() now computes the complete result
//  2002-22-5 RM pde is not a pointer! All calls pde->function() changed to pde.function()
//  2002-23-5 RM factor 0.5*k added in finished to prevent roundof errors screwing up stopping condition
//  2002-16-6 RM bug in advance: stock price domain assumed to start at 0
//	2006-1-9 DD New structure and more in line with othe C++ code
//	2006-1-9 DD Major redesign
//	2006-1-13 DD BUG FIX BAH, it was an error in Unary - in Vector, don't 
//	ask how much good drinking time lost
//	2006-1-16 DD incorporate American exercise feature
//
// (C) Datasim Component Technology BV 2000-2006
//


#ifndef FDM_CPP
#define FDM_CPP


#include "ParabolicFDM.hpp"

#include <math.h>

template <class X, class T, class V> void ParabolicFDM<X,T,V>::CheckAmericanConstraintPut(Vector<V, long>& fullSolution)
{
	//========********** AMERICAN OPTION PUT *************
	for (long mj = fullSolution.MinIndex(); mj <= fullSolution.MaxIndex(); mj++)
	{
		fullSolution[mj] =(fullSolution[mj] > Strike - XARR[mj+1]) ? fullSolution[mj] : Strike - XARR[mj+1];
	}
}

template <class X, class T, class V> void ParabolicFDM<X,T,V>::CheckAmericanConstraintCall(Vector<V, long>& fullSolution)
{
	//========********** AMERICAN OPTION CALL*************
	for (long mj = fullSolution.MinIndex() + 1; mj <= fullSolution.MaxIndex(); mj++)
	{
		fullSolution[mj] =(fullSolution[mj]>XARR[mj] - Strike) ? fullSolution[mj] : XARR[mj] - Strike;
	}
}

template <class X, class T, class V> V ParabolicFDM<X,T,V>::coth(const V& x) const
{ // Hyperbolic cotangent function

	V tmp=::exp(-2*x);
	return (1.0 + tmp)/(1.0 - tmp);
}

template <class X, class T, class V> V ParabolicFDM<X,T,V>::A(const X& x, const T& t) const
{ // Sub-diagonal term in matrix in semi-discrete scheme

	// alpha - beta
	
	return (fitting_factor(x,t)/(h*h) - (0.5 * pde.convection(x,t))/(h));
}


template <class X, class T, class V> V ParabolicFDM<X,T,V>::B(const X& x, const T& t) const
{ // Main diagonal term in matrix in semi-discrete scheme

	// - 2 * alpha + b

	
	return - 2.0 * (fitting_factor(x,t)/(h*h)) + pde.zeroterm(x,t);
}

template <class X, class T, class V>V ParabolicFDM<X,T,V>::C(const X& x, const T& t) const
{ // Super-diagonal term in matrix in semi-discrete scheme

	// alpha + beta
	return (fitting_factor(x,t)/(h*h)) + (0.5 * pde.convection(x,t))/(h);
	
	
}

template <class X, class T, class V>V ParabolicFDM<X,T,V>::F(const X& x, const T& t) const
{ // Right-hand side of matrix equation in semi-discrete scheme

	return (pde.RHS(x,t));
	
}


template <class X, class T, class V> V ParabolicFDM<X,T,V>::fitting_factor(const X& x, const T& t) const
{ // Il'in fitting function

	V tmp = pde.convection(x,t) * h * 0.5;
	return tmp * coth(tmp/(pde.diffusion(x,t))); // Uses hyperbolic cotangent
}

// Fully-discrete coefficients
template <class X, class T, class V> Vector<V,long> ParabolicFDM<X,T,V>::Adiscrete(const T& t) const
{ // Array of A's in semi-discrete scheme

	// Create an array a[1..J-1]

	Vector<V,long> result(J-1, 1);
	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		result[j] = A(XARR[j+1], t);		
	}

	return result;
		
}

template <class X, class T, class V> Vector<V,long > ParabolicFDM<X,T,V>::Bdiscrete(const T& t) const
{ // Array of B's in semi-discrete scheme

	// Create an array b[1..J-1]
		
	Vector<V,long > result(J-1, 1);
	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		result[j] = B(XARR[j+1], t);	
	}

	return result;
}



template <class X, class T, class V> Vector<V,long > ParabolicFDM<X,T,V>::Cdiscrete(const T& t) const
{ // Array of C's in semi-discrete scheme

	// Create an array c[1..J-1]
	Vector<V,long > result(J-1, 1);
	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		result[j] = C(XARR[j+1], t);	
	}

	return result;
}

template <class X, class T, class V> Vector<V,long > ParabolicFDM<X,T,V>::Fdiscrete(const T& t) const
{ // Right-hand side in semi-discrete scheme


	// Create an array f[1..J-1]
	Vector<V,long > result (J-1, 1);

	
	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		result[j] = F(XARR[j+1], t);
	}

	return result;

}

template <class X, class T, class V> void ParabolicFDM<X,T,V>::init()
{ // Initialise all variables, arrays and matrices

	// 1. Mesh stuff
	h = X(pde.first().spread()) /  V(J);
	k = T(pde.second().spread())/  V(N);
	
	// Make 2 arrays of in range [1..J+1] and [1..N+1]
	
	XARR = pde.first().mesh(J);
	TARR = pde.second().mesh(N);

	vecOld = Vector<V, long> (XARR.Size(), XARR.MinIndex());
	vecNew = Vector<V, long> (XARR.Size(), XARR.MinIndex());

	meshValues = NumericMatrix<V, long>(N+1, J+1);

	solution = Vector<V, long>(XARR.Size()- 2, 1);
}

template <class X, class T, class V> ParabolicFDM<X,T,V>::ParabolicFDM
		(const ParabolicPDE<X,T,V>& context, long Xintervals, long Tintervals,
		 int choice, OptionType otype)
{
	pde = context;

	current = pde.second().low();
	
	// Number of intervals in spatial axis
	J = Xintervals;
	
	// Number of intervals in temporal axis
	N = Tintervals;

	// Ratio between explicit and implicit
	theta = 0.5; // default is CN
	if (choice == 1) theta = 0.0;
	if (choice == 2) theta = 1.0;
	
	// Early exercise
	exerciseType = otype;


	// Initialize the run
	init();

}

// The computational scenario
template <class X, class T, class V> void ParabolicFDM<X,T,V>::start()
{ // Fill in initial data

	// Initialise at the boundaries
	vecOld[vecOld.MinIndex()] = pde.BCL(current);
	vecOld[vecOld.MaxIndex()] = pde.BCR(current);

	// Set initial condition
	for (long j = vecOld.MinIndex()+1; j <= vecOld.MaxIndex()-1; j++)
	{
		vecOld[j] = pde.IC(XARR[j]);
	}

//	print(vecOld);
//	int t; cin >> t;

	// Add initial vector to matrix
	currentRow = 1;
	meshValues.Row(currentRow, vecOld);

	// Compute the results
	while(!finished())
	{
		advance();
//		vecOld = vecNew;
	}
	
}

template <class X, class T, class V> void ParabolicFDM<X,T,V>::advance()
{ // Go to the next time stage and calculate. This is where all the action
  // takes place.

	// Set the time
	T t = current;


	// Calculate BC for new Vector
	vecNew[vecNew.MinIndex()] = pde.BCL(t+k);
	vecNew[vecNew.MaxIndex()] = pde.BCR(t+k);

	// Candidate for optimisation
	// Build up Matrix vectors
	Vector<V, long> A_now(J-1, 1);		// Start index 1, size J-1
	Vector<V, long> B_now(J-1, 1);
	Vector<V, long> C_now(J-1, 1);
	Vector<V, long> F_now(J-1, 1);    // forcing term at time current
	Vector<V,long> RHS(J-1, 1);		

	
	Vector<V, long> A_next(J-1, 1);		// Start index 1, size J-1
	Vector<V, long> B_next(J-1, 1);
	Vector<V, long> C_next(J-1, 1);
	Vector<V, long> F_next(J-1, 1);   // forcing term at time current + k
	
	Vector<V, long> unit(J-1, 1, 1.0);		// All elements == 1.0

	// Determine matrix- and vector-values at time current i.e. n
	V coeff_now = k * (1.0 - theta);
	A_now = Adiscrete(t)*coeff_now;
	B_now = unit + (Bdiscrete(t) * coeff_now);
	C_now = Cdiscrete(t) * coeff_now;
	F_now = - Fdiscrete(t) * coeff_now;

	// Determine matrix- and vector-values at time current + k
	V coeff_next = k * theta;

	A_next = - (Adiscrete(t+k) * coeff_next);
	B_next = unit - (Bdiscrete(t+k) * coeff_next);
	C_next = - Cdiscrete(t+k) * coeff_next;
	F_next = - Fdiscrete(t+k) * coeff_next;


	// Calculate the RHS in AU = RHS
	for(long q=RHS.MinIndex(); q<= RHS.MaxIndex(); q++)
	{
		RHS[q] = A_now[q]*vecOld[q]+B_now[q]*vecOld[q+1]+C_now[q]*vecOld[q+2];
				 + F_now[q] + F_next[q];
	}

	// Corrections
	RHS[1]	+= coeff_next *  A(XARR[2],t+k) * vecNew[vecNew.MinIndex()];
	RHS[J-1] += coeff_next * C(XARR[J],t+k) * vecNew[vecNew.MaxIndex()];


	// The objective is to calculate the 'next' vector (BALAYAGE)
//	DoubleSweep<V, long> ss( A_next, B_next, C_next, RHS, 
//			vecNew[vecNew.MinIndex()], vecNew[vecNew.MaxIndex()]);
	// Now solve the system of equations
	LUTridiagonalSolver<double, long> ss(A_next, B_next, C_next, RHS);

	
	solution = ss.solve(); // [1,J-1] ==> length J - 1

	// Test if American constraint has been satisfied
	if (exerciseType == AmericanCallType || exerciseType == AmericanPutType)
	{
		if (exerciseType == AmericanCallType)
		{
			CheckAmericanConstraintCall(solution);
		}
		else
		{
			CheckAmericanConstraintPut(solution);
		}
	}

	for (long ii = vecNew.MinIndex()+1; ii <= vecNew.MaxIndex()-1; ii++)
	{
			vecNew[ii] = solution[ii-1];
	}

	

	current += k;					// Next floor (I mean time level)
	vecOld = vecNew;
	currentRow++;
	meshValues.Row(currentRow, vecNew);
}


template <class X, class T, class V> bool ParabolicFDM<X,T,V>::finished() 
{ // Have we calculated the last vector?

		// Determine if time t = T
//if (current > pde.second().high() - 0.5*k)
	if (currentRow <= N)
	{
			return false; //true;
	}
		
	cout << "time " << current << endl;

	return true; //false;
}



// Results
template <class X, class T, class V> Vector<V,long >& ParabolicFDM<X,T,V>::line()
{ // Current vector output


	// Return the result of the run
	return vecNew;
}

template <class X, class T, class V> Vector<V,long >& ParabolicFDM<X,T,V>::linePrevious() 
{ // Current vector output


	// Return the result of the run
	return vecOld;
}

template <class X, class T, class V> NumericMatrix<V,long>& ParabolicFDM<X,T,V>::result() 
{ // Solution so far

	
	return meshValues;
}

#endif