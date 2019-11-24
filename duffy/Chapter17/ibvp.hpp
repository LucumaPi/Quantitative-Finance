// ibvp.hpp
//
// Modelling PDE as C++ classes. This is a model in 2 space
// dimensions where we assume that Dirichlet boundary conditions are in 
// force.
// 
// In a component environment (e.g. C#) we could define intefaces and 
// abstract base classes.
//
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef IBVP_HPP
#define IBVP_HPP

#include "range.cpp"	// Template class


class IBVP
{
private:

	Range<double> xaxis;		// Space x = S1 interval
	Range<double> yaxis;		// Space y = S2 interval
	Range<double> taxis;		// Time  interval

	// NOT: IBVPImp* imp;				// Bridge implementation
	// In this implementation we use inheritance because of time constraints

public:

		IBVP();

		IBVP (const Range<double>& xrange, const Range<double>& yrange, 
					const Range<double>& trange);

		// Selector functions
		// Coefficients of parabolic second order operator
		virtual double diffusion1(double x, double y, double t) const = 0; // Coefficient of second derivative
		virtual double diffusion2(double x, double y, double t) const = 0; // Coefficient of second derivative

		virtual double convection1(double x, double y, double t) const = 0;	// Coefficient of first derivative
		virtual double convection2(double x, double y, double t) const = 0;	// Coefficient of first derivative

		virtual double crossTerm(double x, double y, double t) const = 0;	// Mixed derivative term
		virtual double zeroTerm(double x, double y, double t) const = 0;	// Coefficient of zero derivative

		virtual double RHS(double x, double y, double t) const = 0;			// Inhomogeneous forcing term

		// Boundary and initial conditions
		virtual double BCLeft(double y, double t) = 0;			// Left hand boundary condition
		virtual double BCRight(double y, double t) = 0;			// Right hand boundary condition

		virtual double BCUnder(double y, double t) = 0;			// Left hand boundary condition
		virtual double BCUpper(double y, double t) = 0;			// Right hand boundary condition

		virtual double IC(double x, double y) const = 0;		// Initial condition

		
		// The domain in which the PDE is 'played'
		Range<double>& xrange(); 
		Range<double>& yrange(); 

		Range<double>& trange();

};

#endif
