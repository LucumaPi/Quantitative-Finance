// numIntegrator.cpp
//
//
// Last modification dates;
//
//	2003-11-28 DD kick-off
//
//
// (C) Datasim Education BV 2004

#ifndef NumIntegrator_cpp
#define NumIntegrator_cpp



#include "NumIntegrator.hpp"

#include "integratorimp.hpp"

NumIntegrator::NumIntegrator(double (*fp)(double x), const Range<double>& myRange, 
									IntegratorImp& implementor, int numberSteps)
{

		nSteps = numberSteps;
		interval = myRange;
		f = fp;

		imp = &implementor;	
}

// Choosing a new function
void NumIntegrator::function(double (*fp)(double x)) 
{
		f = fp; 
}

void NumIntegrator::range (const Range<double>& myRange)
{
		interval = myRange;
}
	


Range<double> NumIntegrator::getInterval() const
{
		return interval;
}

int NumIntegrator::numberSteps() const
{
		return nSteps;
}

double NumIntegrator::calculate(double x) const
{ // Calculate value at value == x

	return (*f)(x);
}



double NumIntegrator::value() const
{ // Get the approximate value of the integral

	
	return imp -> value(*this);
}



#endif

