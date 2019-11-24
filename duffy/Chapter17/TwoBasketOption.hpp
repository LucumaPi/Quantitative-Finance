// TwoBasketOption.hpp
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
// Some Extensions (for the reader):
//
// 1. Support for call as well as put options, we could 
// have Neumann BC at S = SMax
// 2. Approximating boundary condition differently. Now we
// give the BC as the exact solution of 1-factor Black Scholes
// 3. Support for different kinds of payoff functions as in chapter 24.
// Ideally, the PDE is always the same and it is just its BCs and payoffs
// that vary. This is a good candidate for Template Method and Strategy
// patterns.
//
// Extensions to FDM also possible; this is another file in this directory
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef TwoBasketOption_HPP
#define TwoBasketOption_HPP
 
#include "ibvp.hpp"			// Template class
#include "BasicOption.hpp"	// Exact one-factor model
#include "instrument.hpp"	// Data for option

class TwoBasketOption: public IBVP
{
//private:

public:		// For convenience
		TwoFactorOptionData opt; // Nasty parameters hidden in here
		// Later, use pointers

		// Two instances on Lower and Down boundaries
		BasicOption leftOption;
		BasicOption downOption;

		void init();	// Initialise member data
	
public:

		TwoBasketOption();

		TwoBasketOption(const Range<double>& xrange, const Range<double>& yrange, const Range<double>& trange,
			 const TwoFactorOptionData& data);

		// Selector functions
		// Coefficients of parabolic second order operator
		virtual double diffusion1(double S1, double S2, double t) const ; // Coefficient of second derivative
		virtual double diffusion2(double S1, double S2, double t) const ; // Coefficient of second derivative

		virtual double convection1(double S1, double S2, double t) const ;	// Coefficient of first derivative
		virtual double convection2(double S1, double S2, double t) const ;	// Coefficient of first derivative

		virtual double crossTerm(double S1, double S2, double t) const ;	// Mixed derivative term
		virtual double zeroTerm(double S1, double S2, double t) const ;	// Coefficient of zero derivative

		virtual double RHS(double S1, double S2, double t) const ;			// Inhomogeneous forcing term

		// Boundary and initial conditions. We are asssuming Dirichlet BC
		// but in general things are a bit different
		virtual double BCLeft(double S2, double t);	    		// Left hand boundary condition
		virtual double BCRight(double S2, double t);			// Right hand boundary condition

		virtual double BCUnder(double S1, double t);			// Left hand boundary condition
		virtual double BCUpper(double S1, double t);			// Right hand boundary condition

		virtual double IC(double S1, double S2) const ;			// Initial condition

};

#endif
