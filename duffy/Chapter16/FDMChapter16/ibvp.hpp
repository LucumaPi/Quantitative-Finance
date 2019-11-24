// ibvp.hpp
//
// Modelling PDE as C++ classes. This is a simple model in one space
// dimension where we assume that Dirichlet boundary conditions are in 
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
#include "ibvpImp.hpp"


class IBVP
{
private:
	Range<double> xaxis;		// Space interval
	Range<double> taxis;		// Time  interval

	IBVPImp* imp;				// Bridge implementation

private:

		IBVP();

public: 
		IBVP (IBVPImp& executor, const Range<double>& xrange,
					const Range<double>& trange);

		// Selector functions
		// Coefficients of parabolic second order operator
		double diffusion(double x, double t) const; // Coefficient of second derivative

		double convection(double x, double t) const;	// Coefficient of first derivative

		double zeroterm(double x, double t) const;	// Coefficient of zero derivative

		double RHS(double x, double t) const;			// Inhomogeneous forcing term

		// Boundary and initial conditions
		double BCL(double t) const;			// Left hand boundary condition

		double BCR(double t) const;			// Right hand boundary condition

		double IC(double x) const;			// Initial condition

		
		// The domain in which the PDE is 'played'
		Range<double>& xrange(); 

		Range<double>& trange();

};

#endif
