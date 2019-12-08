// ibvpsolver.hpp
//
// Solvers for initial boundary value problems. We 
// use an abstract base class; derived class implement
// specific behaviour.
//
// This class makes use of the Template Method Pattern.
//
// 2005-9-36 DD kick-off
// 2005-10-1 DD next rev.
// 2005-10-11 DD last revision?
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef IBVPSOLVER_HPP
#define IBVPSOLVER_HPP


#include "ibvp.hpp"
#include "numericmatrix.cpp"
#include "LUSolver.cpp"		// !! for convenience
#include "mesher.hpp"

#include <math.h>
#include <assert.h>

class IBVPFDM
{ // Set of finite difference to solve scalar initial
  // boundary value problems

private:

	// Utility functions
	void initMesh(long NSteps, long JSteps);
	void initIC();


protected:
	
	IBVP* ibvp;				// Pointer to 'parent'

	long N;					// The number of subdivision of interval in IBVP 
	double k;				// Step length; redundant data but is efficient	
	
	long J;					// The number of subdivisions of interval in IBVP 
	double h, h2;			// Step length; redundant data but is efficient	

	double DN;
	double DJ;
	double DJJ;

	double tprev, tnow;
	long currentIndex, maxIndex;

	Mesher m;
	Vector<double, long> xarr; // Useful work array
	Vector<double, long> tarr; // Useful work array

	// Help functions (Strategy) and redundant data
	NumericMatrix<double, long> res;		// Will contain the results of the calculations

	// Other data 
	long n;		// Current counter
	Vector<double, long> vecOld;
	Vector<double, long> vecNew;

	IBVPFDM(const IBVPFDM& source); 
	IBVPFDM& operator = (const IBVPFDM& source);

public:
	IBVPFDM();
	IBVPFDM(IBVP& source, long NSteps, long JSteps);

	virtual ~IBVPFDM();
 	

	// N.B. !!! Resulting output of size N+1 and start index 1 !!!!!!
	NumericMatrix<double, long>& result();		// The result of the calculation
	Vector<double, long> XValues() const;		// Array of x values
	Vector<double, long> TValues() const;		// Array of time values

	// Hook function for Template Method pattern 
	virtual void calculateBC() = 0; // Tells how to calculate sol. at n+1
	virtual void calculate() = 0; // Tells how to calculate sol. at n+1

};


#endif