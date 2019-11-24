// OneFactorPayoff.cpp
//
// Base class for OneFactorPayoffs.
//
// 5 june 1998	MB	Started
// 2005-5-16 DD Modified from Shape hierarchy
// 2005-12-9 DD Call/put payoff fns here
//
// (C) Datasim Education BV 1998 - 2006

#ifndef OneFactorPayoff_CPP
#define OneFactorPayoff_CPP

#include "OneFactorPayoff.hpp"

// Hard-coded, handy functions
double MyCallPayoffFN(double K, double S) 
{
		if (S > K)
			return (S - K);
		
		return 0.0;

}

double MyPutPayoffFN(double K, double S) 
{
		// max (K-S, 0)
		if (K > S)
			return (K - S);
		
		return 0.0;

}

// Constructors and destructor
OneFactorPayoff::OneFactorPayoff()
{ // Default constructor

	K = 0.0;
	payoffFN = 0;
}
OneFactorPayoff::OneFactorPayoff(double strike, double (*pay)(double K, double S))
{ // Default constructor

	K = strike;
	payoffFN = pay;
}

OneFactorPayoff::OneFactorPayoff(const OneFactorPayoff& source)
{ // Copy constructor

	K = source.K;
	payoffFN = source.payoffFN;
}

OneFactorPayoff:: ~OneFactorPayoff()
{ // Destructor
}

// Operator overloading
OneFactorPayoff& OneFactorPayoff::operator = (const OneFactorPayoff& source)
{ // Assignment operator

	if (this == &source)
		return *this;

	K = source.K;
	payoffFN = source.payoffFN;

	return *this;
}

// Not a pure virtual OneFactorPayoff function anymore
double OneFactorPayoff::payoff(double S) const
{ // For a given spot price
	

	return payoffFN(K, S);	// DELEGATE to strategy
}

#endif