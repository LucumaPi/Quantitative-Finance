// BSibvp.hpp
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
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef BSIBVP_HPP
#define BSIBVP_HPP

#include "ibvp.hpp"	// Template class


class BSIBVP : public IBVP
{
private:

		TwoFactorOption* opt;
	
private:

		BSIBVP();

public: 
		BSIBVP (const Range<double>& xrange, const Range<double>& yrange, 
					const Range<double>& trange);

		// Selector functions
		// Coefficients of parabolic second order operator
		virtual double diffusion1(double x, double y, double t) const ; // Coefficient of second derivative
		virtual double diffusion2(double x, double y, double t) const ; // Coefficient of second derivative

		virtual double convection1(double x, double y, double t) const ;	// Coefficient of first derivative
		virtual double convection2(double x, double y, double t) const ;	// Coefficient of first derivative

		virtual double crossTerm(double x, double y, double t) const ;	// Mixed derivative term
		virtual double zeroTerm(double x, double y, double t) const ;	// Coefficient of zero derivative

		virtual double RHS(double x, double y, double t) const ;			// Inhomogeneous forcing term

		// Boundary and initial conditions
		virtual double BCLeft(double y, double t) const ;			// Left hand boundary condition
		virtual double BCRight(double y, double t) const ;			// Right hand boundary condition

		virtual double BCUnder(double y, double t) const ;			// Left hand boundary condition
		virtual double BCRUpper(double y, double t) const ;			// Right hand boundary condition

		virtual double IC(double x, double y) const ;				// Initial condition

};

#endif
