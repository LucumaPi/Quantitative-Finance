// ibvp.cpp
//
// Modelling PDE as C++ classes. This is a simple model in one space
// dimension where we assume that Dirichlet boundary conditions are in 
// force.
// 
// In a component environment (e.g. C#) we could define intefaces and 
// abstract base classes.
//
// Last Modification Dates:
//
// 2005-9-26 DD Kick off
// 2005-10-26 DD Finish off
// 2005-10-27 DD new cpp file
// 2005-12-12 DD for 2d basket option case. No Bridge but inheritance now
//
// (C) Datasim Component Technology BV 2000-2006

#include "ibvp.hpp"


IBVP::IBVP()
{
		xaxis = Range<double> (0.0, 1.0);
		taxis = Range<double> (0.0, 1.0);

}

IBVP::IBVP (IBVPImp& executor, const Range<double>& xrange, const Range<double>& trange)
{
		imp = &executor;
		xaxis = xrange;

		taxis = trange;
}


double IBVP::diffusion(double x, double t) const
{ // Coefficient of second derivative

	return imp->diffusion(x,t);
}

double IBVP::convection(double x, double t) const
{ // Coefficient of first derivative

	return imp->convection(x,t);
}


double IBVP::zeroterm(double x, double t) const
{	// Coefficient of zero derivative

	return imp->zeroterm(x,t);
}


double IBVP::RHS(double x, double t) const
{ // Inhomogeneous forcing term

	return imp->RHS(x,t);
}


// Boundary and initial conditions
double IBVP::BCL(double t) const
{ // Left hand boundary condition

	return imp->BCL(t);
}


double IBVP::BCR(double t) const
{ // Right hand boundary condition

	return imp->BCR(t);
}


double IBVP::IC(double x) const
{ // Initial condition

	return imp->IC(x);
}


		
// The domain in which the PDE is 'played'
Range<double>& IBVP::xrange() 
{
			return xaxis;
}



Range<double>& IBVP::trange() 
{
			return taxis;
}

