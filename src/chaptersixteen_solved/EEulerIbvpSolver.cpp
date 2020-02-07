// EEulerIbvpSolver.cpp
//
// Solvers for initial boundary value problems. We 
// use an abstract base class; derived class implement
// specific behaviour.
//
// 2005-9-36 DD kick-off
// 2005-10-1 DD next rev.
// 2005-10-11 DD last revision?
// 2005-11-30 DD New cpp file
// 2005-12-5 DD h^-2 --> DJJ
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef EEulerIBVPSOLVER_CPP
#define EEulerIBVPSOLVER_CPP

#include "EEulerIbvpSolver.hpp"
#include <iostream>
using namespace std;

ExplicitEulerIBVP::ExplicitEulerIBVP(): IBVPFDM()
{
}

ExplicitEulerIBVP::ExplicitEulerIBVP(IBVP& source, long NSteps, long JSteps)
		: IBVPFDM(source, NSteps, JSteps)
{

}

// Hook function for Template Method pattern 
void ExplicitEulerIBVP::calculateBC()
{ // Tells how to calculate sol. at n+1

		vecNew[vecNew.MinIndex()] = ibvp->BCL(tprev);
		vecNew[vecNew.MaxIndex()] = ibvp->BCR(tprev);

}


void ExplicitEulerIBVP::calculate()
{ // Tells how to calculate sol. at n+1

		// Explicit Euler schemes		

			cout << "Explicit Euler calc\n";


			for (long i = vecNew.MinIndex()+1; i <= vecNew.MaxIndex()-1; i++)
			{
				tmp1 = k*(ibvp->diffusion(xarr[i], tprev));
				tmp2 = (k*h*0.5 * (ibvp->convection(xarr[i], tprev)));

				// Coefficients of the U terms
				alpha = tmp1 - tmp2;
				beta = h2 - (2.0*tmp1) + (k*h2*(ibvp->zeroterm(xarr[i], tprev)));
				gamma = tmp1 + tmp2;

				vecNew[i] = ( (alpha * vecOld[i-1])
									+ (beta * vecOld[i])
									+ (gamma * vecOld[i+1]) )/h2 // * DJJ // djj = h^-2
									- (k*(ibvp -> RHS(xarr[i], tprev)));
			}
}


#endif