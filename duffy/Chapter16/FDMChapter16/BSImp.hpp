// BSImp.hpp
//
// Implementation class for one-factor initial boundary
// value problems.
//
// Class for the Black Scholes Parabolic IBVP. You can customise 
// it to suit your needs. e.g. time and asset dependent volatility.
// Notice that the functions in the IBVP uses constant Properties 
// from an Option object.
//
// Note: in BCL() and BCR() you comment out code depending on whether
// you use Call or Put. Diriclet boundary conditions only.
//
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef BSIBVPIMP_HPP
#define BSIBVPIMP_HPP


#include "ibvpimp.hpp"
#include "Instrument.hpp"


class BSIBVPImp : public IBVPImp
{
public:
	
		Option* opt;
		
		BSIBVPImp(Option& option);

		double diffusion(double x, double t) const;
		

		double convection(double x, double t) const;
		

		double zeroterm(double x, double t) const;	// Coefficient of zero derivative
		

		double RHS(double x, double t) const;		// Inhomogeneous forcing term
		

		// Boundary and initial conditions
		double BCL(double t) const;					// Left hand boundary condition
		

		double BCR(double t) const;					// Right hand boundary condition
		

		double IC(double x) const;					// Initial condition
	
};


#endif
