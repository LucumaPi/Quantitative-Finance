// NumIntegrator.hpp
//
// A class that integrates a real-valued function of one variable.
// We have used the Bridge pattern to allow us flexibility in choosing 
// how to integrate the function numericallly.
//
//
// (C) Datasim Education BV 2004

#ifndef NumIntegrator_hpp
#define NumIntegrator_hpp



#include "range.cpp"

class IntegratorImp;


class NumIntegrator
{

private:

	
	int nSteps;				// Number of subdivisions of interval
	Range<double> interval;	// Interval of interest

	double (*f)(double x);	// C style function	

	IntegratorImp* imp;		// The 'real' integrator

public:
	NumIntegrator(double (*fp)(double x), const Range<double>& myRange, IntegratorImp& implementor,
						int numSteps = 30);


	// Modifiers
	void function(double (*fp)(double x)); 
	void range (const Range<double>& myRange);
	
	// Selectors
	int numberSteps() const;
	Range<double> getInterval() const;
	double calculate(double x) const;		// Calculate value at value == x

	// Calculating the integral of the function. Functions that are
	// delegated to the Bridge implementation.
	double value() const;
	// Vector<double, int> mesh() const;
	// double accuracy() const;	


};



#endif

