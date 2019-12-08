// EEulerIbvpSolver.hpp
//
// Solvers for initial boundary value problems. We 
// use an abstract base class; derived class implement
// specific behaviour.
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef EEulerIBVPSOLVER_HPP
#define EEulerIBVPSOLVER_HPP


#include "ibvpsolver.hpp"

class ExplicitEulerIBVP : public IBVPFDM
{
private:

		double tmp1, tmp2;			// Work variables
		double alpha, beta, gamma;	// Coefficients in FD scheme

public:
	ExplicitEulerIBVP();
	ExplicitEulerIBVP(IBVP& source, long NSteps, long JSteps);

	// Hook function for Template Method pattern 
	void calculateBC();

	void calculate();
	
};


#endif