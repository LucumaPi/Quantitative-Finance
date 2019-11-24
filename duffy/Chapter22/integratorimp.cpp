// integratorimp.cpp
//
// Classes that actually do integartion of one-dimensional functions.
//
// Last modification dates:
//
//	DD 2003-11-28 Kick-of code
//
// (C) Datasim Education BV 2004
//

#include "integratorimp.hpp"
#include <cmath>



// Rule for integrating nasty functions; based on Duffy 1980

double TanhRule::value(const NumIntegrator& f) const
{

	// Get all the stuff from the client in order to do my job

	Range<double> r = f.getInterval();
	double A = r.low();
	double B = r.high();


	int N = f.numberSteps();
	double res = 0.0;
	double nd = double(N);
	double h = r.spread() / nd;
	for (double x = A + (0.5 * h); x < B; x += h)
	       res += tanh(f.calculate(x) * 0.5 * h);

	   return 2.0 * res;
}



double MidpointRule::value(const NumIntegrator& f) const
{

	// Get all the stuff from the client in order to do my job

	Range<double> r = f.getInterval();
	double A = r.low();
	double B = r.high();


	int N = f.numberSteps();
	double res = 0.0;
	double nd = double(N);
	double h = r.spread() / nd;
	for (double x = A + (0.5 * h); x < B; x += h)
	      res += f.calculate(x);

	   return res*h;
}





