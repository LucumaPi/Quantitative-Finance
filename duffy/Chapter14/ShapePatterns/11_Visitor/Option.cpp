// EurpeanOption.cpp
//
//	Author: Daniel Duffy
//
// Last modification dates:
//
//	DD 2004-1-12 Fitted for observer pattern
//
// (C) Datasim Component Technology BV 2003-2004
//



#include "Option.hpp"
//#include "CDOVisitor.hpp"

#include <math.h>
#include <iostream>
#include <string>

//////////// Gaussian functions /////////////////////////////////

double Option::n(double x) const
{ 

	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);

}

double Option::N(double x) const
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
double Option::CallPrice() const
{

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;


	return (U * exp((b-r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));

}

double Option::PutPrice() const
{

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r * T)* N(-d2)) - (U * exp((b-r)*T) * N(-d1));

}

double Option::CallDelta() const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;


	return exp((b-r)*T) * N(d1);
}

double Option::PutDelta() const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * (N(d1) - 1.0);
}



/////////////////////////////////////////////////////////////////////////////////////

void Option::init()
{	// Initialise all default values

	// Default values
	r = 0.08;
	sig= 0.30;
	K = 65.0;
	T = 0.25;
	U = 60.0;		// U == stock in this case
	b = r;			// Black and Scholes stock option model (1973)

	otyp = "C";		// European Call Option (this is the default type)



}

void Option::copy(const Option& o2)
{

	r	= o2.r;
	sig = o2.sig;	
	K	= o2.K;
	T	= o2.T;
	U	= o2.U;
	b	= o2.b;
	
	otyp = o2.otyp;


	
}

Option::Option() 
{ // Default call option

	init();
}

Option::Option(const Option& o2)
{ // Copy constructor

	copy(o2);
}

Option::Option (const string& optionType)
{	// Create option type

	init();
	otyp = optionType;

	if (otyp == "c")
		otyp = "C";

}



Option::~Option()
{

}

// Functions associated with Observer pattern
/*void Option::Update(Observable* obj)
{

	// !!!!! Don't FORGET TO TURN RTTI ON IN THE PROJECT SETTINGS
	Asset* pAsset = dynamic_cast<Asset*>(obj);
	if(pAsset != 0)
	{
		cout << "Asset has changed : " << pAsset->getStock();

		// Now update the REDUNDANT variable U
		U = pAsset -> getStock();

		cout << ", Price: " << Price() << endl;
	}
	else
	{
		cout << "Unknown observable" << endl;
	}

}
*/
Option& Option::operator = (const Option& option2)
{

	if (this == &option2) return *this;

	copy (option2);

	return *this;
}

// Functions that calculate option price and sensitivities
double Option::Price() const 
{

	if (otyp == "C")
	{
		return CallPrice();
	}
	else
		return PutPrice();

}

double Option::Delta() const 
{
	if (otyp == "C")
		return CallDelta();
	else
		return PutDelta();

}



// Modifier functions
void Option::toggle()
{ // Change option type (C/P, P/C)

	if (otyp == "C")
		otyp = "P";
	else
		otyp = "C";
}


// Special copy function to create a copy of a Product when you only have a Product pointer
Product* Option::Clone() const
{ // Create a copy of the Product

	return new Option(*this);
}
/*
void Option::Accept(CDOVisitor& v)
{// Accept a visitor

	v.Visit(*this);
}
*/