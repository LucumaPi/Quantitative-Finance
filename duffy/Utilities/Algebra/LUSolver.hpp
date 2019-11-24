// LUSolver.hpp
//
// Classes and functions for solving linear systems of equations 
// (numerical linear algebra). We use:
//
//	Direct methods (LU decomposition)
//
// (C) Datasim Education BV 2003-2006

#ifndef LUSolver_HPP
#define LUSolver_HPP

#include "vector.cpp"			// Arrays with mathematical properties
#include "numericmatrix.cpp"	// Matrices with numerical properties


template <class V, class I> class LUTridiagonalSolver
{ // Solve tridiagonal matrix equation
private:

	// Defining arrays (input)
	// V2 optimise so to work with pointers
	Vector<V,I> a;	// The lower-diagonal array [1..J]
	Vector<V,I> b;	// The diagonal array [1..J] "baseline array"
	Vector<V,I> c;	// The upper-diagonal array [1..J]
	Vector<V,I> r;	// The right-hand side of the equation Au = r [1..J]

	// Work arrays

	// Coefficients of Lower and Upper matrices: A = LU
	// V2 use of Templated static vectors, but we must be careful
	Vector<V,I> beta;	// Range [1..J]
	Vector<V,I> gamma;	// Range [1..J-1]
	// Solutions of temporary and final problems
	Vector<V,I> z;		// Range [1..J]
	Vector<V,I> u;		// Range [1..J]

	long Size;

	void calculateBetaGamma();		// Calculate beta and gamma
	void calculateZU();				// Calculate z and u
	

public:
	LUTridiagonalSolver();
	LUTridiagonalSolver(Vector<V,I>& lower_A, Vector<V,I>& diagonal_B, Vector<V,I>& upper_C, Vector<V,I>& rhs_R);
	LUTridiagonalSolver(const LUTridiagonalSolver<V,I>& source); 
	
	virtual ~LUTridiagonalSolver();
 	
	// Assignment operator 
	LUTridiagonalSolver<V,I>& operator = (const LUTridiagonalSolver<V,I>& source);

	// Calculate the (final) solution to Au = r
	Vector<V,I> solve();

	bool diagonallyDominant() const;


};


#endif