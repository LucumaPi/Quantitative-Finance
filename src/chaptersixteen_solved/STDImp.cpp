// STDImp.cpp
//
// Implementation class for one-factor initial boundary
// value problems.
//
// Last Modification Dates:
//
// 2005-9-26 DD Kick off
// 2005-11-26 DD Finish
// 2005-11-27 DD New cpp structure
// 2005-12-5 DD Seperate cpp files
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef STDIMP_CPP
#define STDIMP_CPP

#include "STDImp.hpp"			

// Selector functions
// Coefficients of parabolic second order operator

STDIBVPImp::STDIBVPImp() {}

double STDIBVPImp::diffusion(double x, double t) const // Coefficient of second derivative
{
	return 1.0;

}

double STDIBVPImp::convection(double x, double t) const	// Coefficient of first derivative
{
		return 0.0;
}

double STDIBVPImp::zeroterm(double x, double t) const	// Coefficient of zero derivative
{
		return 0.0;	
		
}

double STDIBVPImp::RHS(double x, double t) const			// Inhomogeneous forcing term
{
	return 0.0;
}

// Boundary and initial conditions
double STDIBVPImp::BCL(double t) const			// Left hand boundary condition
{
	return 0.0;

}

double STDIBVPImp::BCR(double t) const			// Right hand boundary condition
{
	return 0.0;
}

double STDIBVPImp::IC(double x) const			// Initial condition
{
	//return 0.0;
	if (x >= 0.0 && x <= 0.5)
	{
		return 2.0 * x;
	}

	return 2.0 * (1.0 - x);
			

		/*	if (x < 0.9)
				return 0.0;
			return 1.0; */
						
			
}

#endif