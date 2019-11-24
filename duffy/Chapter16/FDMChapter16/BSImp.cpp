// BSImp.cpp
//
// Implementation class for one-factor initial boundary
// value problems.
//
// In this case, Black Scholes equation.
//
// Class for the Black Scholes Parabolic IBVP. You can customise 
// it to suit your needs. e.g. time and asset dependent volatility.
// Notice that the functions in the IBVP uses constant Properties 
// from an Option object.
//
// Note: in BCL() and BCR() you comment out code depending on whether
// you use Call or Put. Diriclet boundary conditions only.
//
// Last Modification Dates:
//
// 2005-9-26 DD Kick off
// 2005-11-26 DD Finish
// 2005-11-27 DD New cpp structure
//
// (C) Datasim Component Technology BV 2000-2006


#include "BSImp.hpp"			
#include <math.h>
#include "OneFactorPayoff.hpp"		// Payoff function hierarchy
#include "Instrument.hpp"			// Basic Option hierarchy
	

BSIBVPImp::BSIBVPImp(Option& option) 
{
	opt = &option;
}

double BSIBVPImp::diffusion(double x, double t) const
{ // simulates diffusion

	double v = (opt -> sig); // volatility
			
	return 0.5 * v * v * x * x;

}

double BSIBVPImp::convection(double x, double t) const
{ // simulates drift


	return (opt -> r) * x; // r == interest rate
}

double BSIBVPImp::zeroterm(double x, double t) const	// Coefficient of zero derivative
{
	return - (opt -> r);	
}

double BSIBVPImp::RHS(double x, double t) const		// Inhomogeneous forcing term
{
	return 0.0;
}

// Boundary and initial conditions
double BSIBVPImp::BCL(double t) const					// Left hand boundary condition
{

	if (opt->type == 'C')
	{
		return 0.0;	//C
	}
	else
	{
		return (opt->K) * ::exp(- (opt->r) * ((opt->T) - t)); // P
	}
			
}

double BSIBVPImp::BCR(double t) const					// Right hand boundary condition
{
	if (opt->type == 'C')
	{
		return opt->SMax; // Magic number
	}
	else
	{
		return 0.0; //P
	}
}

double BSIBVPImp::IC(double x) const					// Initial condition
{
	return (*opt).OptionPayoff.payoff(x);
}

