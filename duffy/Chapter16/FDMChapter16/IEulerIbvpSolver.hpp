// IEulerIvpSolver.hpp
//
// Solvers for initial boundary value problems. We 
// use an abstract base class; derived class implement
// specific behaviour.
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef IEulerBVPSOLVER_HPP
#define IEulerBVPSOLVER_HPP

#include "ibvpsolver.hpp"

class ImplicitEulerIBVP : public IBVPFDM
{
private:
		// We must build these in constructors

		// Notice that we store the data that 'belongs' to
	    // this class. It is private and will not pollute the
	    // other classes.
		Vector<double, long> A, B, C; // Lower, diagonal, upper
		Vector<double, long> F;	  // Right-hand side of matrix
		

public:
	ImplicitEulerIBVP();

	ImplicitEulerIBVP(IBVP& source, long NSteps, long JSteps);

	void calculateBC();
	
	void calculate();

};

#endif