// ivpSolver.cpp
//
//	Last modification dates:
//
//	DD 2003-4-5 Kick off
//	DD 2003-7-25 Predictor-corrector added
//	DD 2005-9-20 New derived classes
//	DD 2005-9-22/23 Finish off
//
// (C) Datasim Component Technology BV 2003-2006
//


#ifndef IVPSolver_cpp
#define IVPSolver_cpp

#include "ivpsolver.hpp"
#include <math.h>


IVPFDM:: IVPFDM()
{

	ivp = 0;
	N = 10;

	k = ivp -> interval.spread()/double(N);
	res = Vector<double, long> (N+1, 1);	// Size = N + 1, start index = 1

}

IVPFDM:: IVPFDM(IVP& source, long NSteps)
{

	ivp = &source;
	N = NSteps;

	k = ivp -> interval.spread()/double(N);
	res = Vector<double, long> (N+1, 1);	// Size = N + 1, start index = 1

}


IVPFDM:: IVPFDM(const IVPFDM& source)
{	

	ivp = source.ivp;
	N = source.N;

	k = ivp -> interval.spread()/double(N);
	
	res = source.res;

}


IVPFDM::~IVPFDM()
{

}

 	
IVPFDM&  IVPFDM::operator = (const  IVPFDM& source)
{

	if (this == &source)
		return *this;

	ivp = source.ivp;
	N = source.N;

	k = source.k;
	res = source.res;

	return *this;
}

// Modifier functions
void IVPFDM::steps(long Nsteps)
{
	
	N = Nsteps;

	// Don't forget to update redundant attributes!
	k = ivp -> interval.spread()/double(N);

	res = Vector<double, long> (N+1, 1);	// Size = N + 1, start index = 1
	
}

// Output
double IVPFDM::stepSize() const
{
	
	return k;
}


Vector<double, long> IVPFDM::result()
{ // The result of the calculation

	// Template Method pattern here
	
	// Invariant part

	res[res.MinIndex()] = (ivp -> startValue());

	// Variant part; pure virtual hook functions
	calculate ();

	return res;
}


#endif

		