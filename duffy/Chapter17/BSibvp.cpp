// BSibvp.cpp
//
// Modelling PDE as C++ classes. This is a model in 2 space
// dimensions where we assume that Dirichlet boundary conditions are in 
// force.
// 
// This is the two-factor Black Scholes implementaton (basket).
//
// In a component environment (e.g. C#) we could define intefaces and 
// abstract base classes.
//
// Last Modification:
//
//	2005-12-12 DD Initial code
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef BSIBVP_CPP
#define BSIBVP_CPP

#include "bsibvp.hpp"	// Template class



BSIBVP::BSIBVP()
{

}


BSIBVP (const Range<double>& xrange, const Range<double>& yrange, 
		const Range<double>& trange) : IBVP(xrange, yrange, trange)
{

}

// Selector functions// Coefficients of parabolic second order operator
double BSIBVP::diffusion1(double BSIBVP::x, double BSIBVP::y, double BSIBVP::t) const
{

double s = opt->sig1;
	return 0.5 * s * s * x * x;

} // Coefficient of second derivative

double BSIBVP::diffusion2(double BSIBVP::x, double BSIBVP::y, double BSIBVP::t) const 
{   
	
	double s = opt->sig1;
	return 0.5 * s * s * x * x;

} // Coefficient of second derivative


 double BSIBVP::convection1(double BSIBVP::x, double BSIBVP::y, double BSIBVP::t) const 
 {    
		return (opt->r) - (opt->D1);

 }	// Coefficient of first derivative


 double BSIBVP::convection2(double BSIBVP::x, double BSIBVP::y, double BSIBVP::t) const 
 {    
	 return (opt->r) - (opt->D2);
 
 }	// Coefficient of first derivative

 double BSIBVP::crossTerm(double BSIBVP::x, double BSIBVP::y, double BSIBVP::t) const 
 {    
		return (opt->rho) * (opt->sig1) * (opt->sig2) * x * y;

 }	// Mixed derivative term

 double BSIBVP::zeroTerm(double BSIBVP::x, double BSIBVP::y, double BSIBVP::t) const 
 {    
		return - (opt->r);

 }	// Coefficient of zero derivative

 double BSIBVP::RHS(double BSIBVP::x, double BSIBVP::y, double BSIBVP::t) const 
 {    
		return 0.0;
 }			// Inhomogeneous forcing term

// Boundary and initial conditions
 double BSIBVP::BCLeft(double BSIBVP::y, double BSIBVP::t) const 
 {    
 
 }			// Left hand boundary condition
 
 double BSIBVP::BCRight(double BSIBVP::y, double BSIBVP::t) const 
 {    
 
 }			// Right hand boundary condition

 double BSIBVP::BCUnder(double BSIBVP::y, double BSIBVP::t) const 
 {    
 
 }			// Left hand boundary condition

 double BSIBVP::BCRUpper(double BSIBVP::y, double BSIBVP::t) const 
 {    
 
 }			// Right hand boundary condition

 double BSIBVP::IC(double BSIBVP::x, double BSIBVP::y) const 
 {    
 
	 // Severe information hiding

	 return opt->payoff(x, y);
 }				// Initial condition

#endif