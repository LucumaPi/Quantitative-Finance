// testNamespace.cpp
//
// Testing the use of C++ namespaces. This models
// certain parts of the Black Scholes equations we wish
// to use.
//
// (C) Datasim Education BV 2005
//
// This namespace is meant as one of a number that yiu can choose 
// from in a main(), for example.
//

#include <math.h>
#include <string>
#include <iostream>
using namespace std;

namespace NSEuropeanOption
{

	// Data
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double U;		// Current underlying price (e.g. stock, forward)
	double b;		// Cost of carry

	string otyp;	// Option name (call, put)

double n(double x) 
{ 

	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);

}

double N(double x)
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
double CallPrice() 
{

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;


	return (U * exp((b-r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));

}

double PutPrice()
{

	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r * T)* N(-d2)) - (U * exp((b-r)*T) * N(-d1));

}

double Price()
{

	if (otyp == "C")
	{
		return CallPrice();
	}
	else
		return PutPrice();

}

}	// End of namespace


int main()
{
	using namespace NSEuropeanOption;
	r = 0.08;
	sig= 0.30;
	K = 65.0;
	T = 0.25;
	U = 60.0;		// U == stock in this case
	b = r;			// Black and Scholes stock option model (1973)

	otyp = "C";		// European Call Option (this is the default type)

	cout << "Option price: " << Price() << endl;

	return 0;
}
