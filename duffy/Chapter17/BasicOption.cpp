// BasicOption.cpp
//
//	Author: Daniel Duffy
//
// 2005-10-15 DD new class for C++ book
// 2006-2-1 DD pathological cases U = 0 and T = 0 for C and P
// 2006-2-2 DD implemented the payoff function for call and put
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef BasicOption_cpp
#define BasicOption_cpp

double MyMax(double d1, double d2)
{
	if (d1 > d2)
		return d1;

	return d2;
}

#include "BasicOption.hpp"
#include <math.h>
#include <iostream>

//////////// Gaussian functions /////////////////////////////////

double BasicOption::n(double x) const
{ 

	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);

}


double BasicOption::N(double x) const
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


// Kernel Functions (Haug)
double BasicOption::CallPrice(double U) const
{
	

	
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;


	return (U * exp((b-r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));

}

double BasicOption::PutPrice(double U) const
{

//	cout << "Put price" << T << ", " << U << ", " << K << ", " << b << ", " << sig << endl;
	
	double tmp = sig * sqrt(T);
	
	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r * T)* N(-d2)) - (U * exp((b-r)*T) * N(-d1));

}

double BasicOption::CallDelta(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;


	return exp((b-r)*T) * N(d1);
}

double BasicOption::PutDelta(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * (N(d1) - 1.0);
}



/////////////////////////////////////////////////////////////////////////////////////

void BasicOption::init()
{	// Initialise all default values

	// Default values
	r = 0.08;
	sig= 0.30;
	K = 65.0;
	T = 0.25;
	b = r;			// Black and Scholes stock option model (1973)

	otyp = "C";		// European Call Option (this is the default type)



}

void BasicOption::copy(const BasicOption& o2)
{

	r	= o2.r;
	sig = o2.sig;	
	K	= o2.K;
	T	= o2.T;
	b	= o2.b;
	
	otyp = o2.otyp;


	
}

BasicOption::BasicOption() 
{ // Default call option

	init();
}

BasicOption::BasicOption(const BasicOption& o2)
{ // Copy constructor

	copy(o2);
}

BasicOption::BasicOption (const string& optionType)
{	// Create option type

	init();
	otyp = optionType;

	if (otyp == "c")
		otyp = "C";

}



BasicOption::~BasicOption()
{

}


BasicOption& BasicOption::operator = (const BasicOption& option2)
{

	if (this == &option2) return *this;

	copy (option2);

	return *this;
}

// Functions that calculate option price and sensitivities
double BasicOption::Price(double U) const 
{

	if (otyp == "C")
	{
		return CallPrice(U);
	}
	else
		return PutPrice(U);

}

double BasicOption::Delta(double U) const 
{
	if (otyp == "C")
		return CallDelta(U);
	else
		return PutDelta(U);

}


// Modifier functions
void BasicOption::toggle()
{ // Change option type (C/P, P/C)

	if (otyp == "C")
		otyp = "P";
	else
		otyp = "C";
}

void BasicOption::dumpPrint() const
{

	cout << "Interest rate: " << r << endl;
	cout << "Volatility: " << sig << endl;
	cout << "Strike price: " << K << endl;
	cout << "Expiry date: " << T << endl;
	cout << "Cost of carry: " << b << endl;
	cout << "Option type: " << otyp << endl;

}

double BasicOption::payoff(double U) const
{
	if (otyp == "C")
	{
		return MyMax(U - K, 0.0);
	}
	else
	{
		return MyMax(K - U, 0.0);
	}
}


#endif

