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
		yaxis = Range<double> (0.0, 1.0);
		taxis = Range<double> (0.0, 1.0);

}

IBVP::IBVP (const Range<double>& xrange, const Range<double>& yrange, const Range<double>& trange)
{
		xaxis = xrange;
		yaxis = yrange;

		taxis = trange;
}



		
// The domain in which the PDE is 'played'
Range<double>& IBVP::xrange() 
{
			return xaxis;
}

Range<double>& IBVP::yrange() 
{
			return yaxis;
}

Range<double>& IBVP::trange() 
{
			return taxis;
}

