// ibvpImp.hpp
//
// Implementation class for one-factor initial boundary
// value problems.
//
// Note that all functions are default inline for better
// performance, ease of understanding and for the simple
// reason that most of the functions are one-liners in 
// the main.
//
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef IBVPIMP_HPP
#define IBVPIMP_HPP

class IBVPImp
{

public:

	// Selector functions
	// Coefficients of parabolic second order operator
	virtual double diffusion(double x, double t) const = 0; // Coefficient of second derivative
		
	virtual double convection(double x, double t) const	= 0; // Coefficient of first derivative
			
	virtual double zeroterm(double x, double t) const = 0;	// Coefficient of zero derivative
		

	virtual double RHS(double x, double t) const = 0;		// Inhomogeneous forcing term
		

	// Boundary and initial conditions
	virtual double BCL(double t) const = 0;			// Left hand boundary condition


	virtual double BCR(double t) const = 0;		// Right hand boundary condition

	virtual double IC(double x) const = 0;		// Initial condition


};


#endif
