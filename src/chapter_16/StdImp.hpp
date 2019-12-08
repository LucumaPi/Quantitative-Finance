// Stdimp.hpp
//
// Implementation class for one-factor initial boundary
// value problems.
//
// YOu can customise the class to test your own one-factor PDEs
//
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef STDIMP_HPP
#define STDIMP_HPP

#include "ibvpimp.hpp"

// Domain-independent class for Parabolic IBVP
class STDIBVPImp : public IBVPImp
{


public:

	
		// Selector functions
		// Coefficients of parabolic second order operator

		STDIBVPImp();

		double diffusion(double x, double t) const; // Coefficient of second derivative

		double convection(double x, double t) const;	// Coefficient of first derivative

		double zeroterm(double x, double t) const;	// Coefficient of zero derivative

		double RHS(double x, double t) const;			// Inhomogeneous forcing term

		// Boundary and initial conditions
		double BCL(double t) const;			// Left hand boundary condition

		double BCR(double t) const;			// Right hand boundary condition

		double IC(double x) const;			// Initial condition

};


#endif
