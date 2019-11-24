// ExtendedOption.cpp
//
// Class that represents exact solutions to European options.
//
//	Last modification dates:
//	2002-12-7 DanielDuffy first code
//	2002-12-8 DD tested call and put options for a range of Euro types
//	Some new functions for interoperability
//	2002-12-10 DD almost finished with the code for the European exact option formulae.
//  2005-10-16 DD For intro C++ book
//  2005-10-18 DD last test, everything OK?
//
// (C) Datasim Component Technology BV 2003
//

#ifndef ExtendedOption_cpp
#define ExtendedOption_cpp

#include "ExtendedOption.hpp"
#include <math.h>
#include <iostream>


// Kernel Functions (Haug)
double ExtendedOption::CallPrice(double U) const
{

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;


	return (U * exp((b-r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));

}

double ExtendedOption::PutPrice(double U) const
{

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;
	return (K * exp(-r * T)* N(-d2)) - (U * exp((b-r)*T) * N(-d1));

}

double ExtendedOption::CallDelta(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;


	return exp((b-r)*T) * N(d1);
}

double ExtendedOption::PutDelta(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * (N(d1) - 1.0);
}

double ExtendedOption::CallGamma(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return ( n(d1) * exp((b-r)*T) ) / (U * tmp);
	
}

double ExtendedOption::PutGamma(double U) const
{
	return CallGamma(U);
}


double ExtendedOption::CallVega(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;

	return (U * exp((b-r)*T) * n(d1) * sqrt(T) );
}

double ExtendedOption::PutVega(double U) const
{
	return CallVega(U);
}

double ExtendedOption::CallTheta(double U) const
{

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	double t1 =  (U * exp((b-r)*T ) * n(d1) * sig * 0.5 )/ sqrt(T);
	double t2 =  (b-r)*(U * exp((b-r)*T) * N(d1));
	double t3 =  r * K * exp(-r * T) * N(d2);

	return -(t1 + t2 + t3);
}


double ExtendedOption::PutTheta(double U) const
{

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	double t1 =  (U * exp( (b-r)*T ) * n(d1) * sig * 0.5 )/ sqrt(T);
	double t2 =  (b-r)*(U * exp((b-r)*T) * N(-d1));
	double t3 =  r * K * exp(-r * T) * N(-d2);

	return t2 + t3 - t1;
}

double ExtendedOption::CallRho(double U) const
{

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	if (b != 0.0)
		return T * K * exp(-r * T) * N(d2);
	else
		return - T * CallPrice(U);

}


double ExtendedOption::PutRho(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	if (b != 0.0)
		return - T * K * exp(-r * T) * N(-d2);
	else
		return - T * PutPrice(U);
}


double ExtendedOption::CallCoc(double U) const
{

	double tmp = sig * sqrt(T);
	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;

	return T * U * exp( (b-r)*T ) * N(d1);
}


double ExtendedOption::PutCoc(double U) const
{
	double tmp = sig * sqrt(T);
	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;

	return - T * U * exp((b-r)*T) * N(-d1);
}

double ExtendedOption::CallElasticity(double percentageMovement, double U) const		
{

	return (CallDelta(U) * U) /  percentageMovement;
}

double ExtendedOption::PutElasticity(double percentageMovement, double U) const
{
	return (PutDelta(U) * U) /  percentageMovement;
}

double ExtendedOption::CallStrike(double U) const
{ // As a function of the strike price

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return - exp(-r * T) * N(d2);
}

double ExtendedOption::PutStrike(double U) const
{
	double tmp = sig * sqrt(T);
	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return exp(-r * T) * N(-d2);
}

double ExtendedOption::CallSecondStrike(double U) const
{ // As a function of the strike price

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return ( n(d2) * exp(-r* T) )/( K * sig * sqrt(T) );
}

double ExtendedOption::PutSecondStrike(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return ( n(d2) * exp(-r* T) )/( K * sig * sqrt(T) );		
}

/////////////////////////////////////////////////////////////////////////////////////

void ExtendedOption::init() 
{	// Initialise all default values


	r = 0.08;
	sig = 0.30;
	K = 65.0;
	T = 0.25;
	b = r;

	otyp = "C";	
}

void ExtendedOption::copy(const ExtendedOption& o2)
{

	r = o2.r;
	sig = o2.sig;
	K = o2.K;
	T = o2.T;
	b = o2.b;

	otyp = o2.otyp;	
}

ExtendedOption::ExtendedOption() 
{ // Default call option

	init();
}

ExtendedOption::ExtendedOption(const ExtendedOption& o2)
{ // Copy constructor

	copy(o2);
}

ExtendedOption::ExtendedOption (const string& optionType)
{	// Create option type

	init();
	otyp = optionType;

	// Finger trouble option
	if (otyp == "c")
		otyp = "C";

}


ExtendedOption::ExtendedOption (const string& optionType, const string& underlying)
{ // Create option type

	init();
	otyp = optionType;
}

ExtendedOption::~ExtendedOption()
{

}


ExtendedOption& ExtendedOption::operator = (const ExtendedOption& option2)
{

	if (this == &option2) return *this;

	copy (option2);

	return *this;
}

// Functions that calculate option price and sensitivities
double ExtendedOption::Price(double U) const 
{

	cout << "European option\n";

	if (otyp == "C")
	{
		return CallPrice(U);
	}
	else
		return PutPrice(U);

}

double ExtendedOption::Delta(double U) const 
{
	if (otyp == "C")
		return CallDelta(U);
	else
		return PutDelta(U);

}


double ExtendedOption::Gamma(double U) const 
{
	if (otyp == "C")
		return CallGamma(U);
	else
		return PutGamma(U);

}

double ExtendedOption::Vega(double U) const 
{
	if (otyp == "C")
		return CallVega(U);
	else
		return PutVega(U);

}

double ExtendedOption::Theta(double U) const 
{
	if (otyp == "C")
		return CallTheta(U);
	else
		return PutTheta(U);

}

double ExtendedOption::Rho(double U) const 
{
	if (otyp == "C")
		return CallRho(U);
	else
		return PutRho(U);

}


double ExtendedOption::Coc(double U) const 
{ // Cost of carry

	if (otyp == "C")
		return CallCoc(U);
	else
		return PutCoc(U);

}

double ExtendedOption::Elasticity(double percentageMovement,double U) const
{ // Elasticity

	if (otyp == "C")
		return CallElasticity(percentageMovement,U);
	else
		return PutElasticity(percentageMovement, U);

}



// Modifier functions
void ExtendedOption::toggle()
{ // Change option type (C/P, P/C)

	if (otyp == "C")
		otyp = "P";
	else
		otyp = "C";
}


//////////// Gaussian functions /////////////////////////////////

double ExtendedOption::n(double x) const 
{ 

	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);

}

double ExtendedOption::N(double x) const 
{ // The approximation to the cumulative normal distribution


	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	double k = 1.0/(1.0 + (0.33267 * x));
	
	if (x >= 0.0)
	{
		return 1.0 - n(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	}
	else
	{
		return 1.0 - N(-x);
	}

}


#endif