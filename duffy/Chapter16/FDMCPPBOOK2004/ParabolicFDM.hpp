// parabolicFDM.hpp
//
// Finite difference method for Parabolic PDE. It is
//  specific to Duffy's fitted scheme.
// 
// (C) Datasim Component Technology BV 2000-2006
//


#ifndef FDM_HPP
#define FDM_HPP


#include "parabolicpde.cpp"
//#include "NumericMatrix.cpp"
#include "doublesweep.cpp" // 2003
#include "LUSolver.cpp"		// !! for convenience, 2006

// Early exercise feature possible
enum OptionType {EuropeanCallType, EuropeanPutType, AmericanCallType, AmericanPutType};

template <class X, class T, class V> class ParabolicFDM
{ // Finite difference method for solving parabolic PDE
  // X == x-direction value; T == t direction value; V == value space of unknown
private:

	//The function coth
	V coth(const V& x) const;

	// The corresponding PDE (where all the functions are 'hiding')
	ParabolicPDE<X, T, V> pde;

	// Input parameters
	long J;		// Number of x steps
	long N;		// Number of t steps
	V theta;	// Time discretistion (Implicit == 1, CN == 0.5, Explicit == 0)

	// Dynamic attribute
	T current;	// Current time level

	// Calculated values
	V h;		// Mesh size in x
	T k;		// Mesh size in t
	
	Vector<X, long> XARR;	// The array of x (S) values
	Vector<T, long> TARR;	// The array of t values

	NumericMatrix<V, long> meshValues;
	long currentRow;

// Matrix coefficients

	// Special functions for setting up tridiagonal matrices
	V A(const X& x, const T& t) const;
	
	// 2002-17-5 RM ::B doesn't need Delta_t
	//V B(const X& x, const T& t, const T& Delta_t) const;
	V B(const X& x, const T& t) const;
	
	V C(const X& x, const T& t) const;
	V F(const X& x, const T& t) const ; // RHS function

	V IC(const X& x) const;	// initial condition
	
	V fitting_factor (const X& x, const T& t) const;

	// Vectors representing the diagonals of the tridiagonal matrix
	// The length of each vectors is [1, N-1]
	Vector<V,long> Adiscrete (const T& t) const;
	Vector<V,long> Bdiscrete(const T& t) const;
	Vector<V,long> Cdiscrete(const T& t) const;
	Vector<V,long> Fdiscrete(const T& t) const; // RHS function

	// Vectors at levels n and n+1, range [1, NSteps+1]
	Vector<double, long> vecOld;
	Vector<double, long> vecNew;
	Vector<double, long> solution;

	void init();	// Initialise all arrays/matrices
	void CheckAmericanConstraintCall(Vector<V, long>& fullSolution); // Early exercise
	void CheckAmericanConstraintPut(Vector<V, long>& fullSolution); // Early exercise

	OptionType exerciseType;

public:
	ParabolicFDM(const ParabolicPDE<X,T,V>& context, long Xintervals, long Tintervals,
				 int FDMchoice, OptionType otype = EuropeanType); 

	// The computational scenario
	void start();					// Initial condition specified
	void advance();					// Next time level
	bool finished();			// Have we reached t == T?

	Vector<X, long> xarr() { return XARR; }	// The array of x (S) values
	Vector<T, long> tarr() { return TARR; }	// The array of t (Time) values

	// Results
	Vector<V, long>& line();			// Current vector output (n+1)
	Vector<V, long>& linePrevious();	// Previous time Current vector output(n)

	NumericMatrix<V, long>& result();	// Solution so far
	
};

#endif