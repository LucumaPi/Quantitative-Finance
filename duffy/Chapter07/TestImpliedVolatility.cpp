// TestImpliedVolatility.cpp
//
// Testing Implied Volatility (see Haug 1998)
//
// (C) Datasim Education BV 2006
//

#include "NonlinearSolver.hpp"
#include <math.h>
#include <iostream>
using namespace std;

//////////// Gaussian functions /////////////////////////////////
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

double CallPrice(double sig)
{
	
	// Test case Haug p. 172; student exercise to extend it
	double S = 59.0;
	double K = 60.0;
	double r = 0.067;
	double marketPrice = 2.82; // The call price
	double b = r;
	double T = 0.25;			// Three months
	
	double tmp = sig * sqrt(T);

	double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;


	double calculatedValue = (S * exp((b-r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));

	// Function in the form f(x) = 0
	return marketPrice - calculatedValue;
}


int main()
{
	// Tell where to look for solvers, in a namespace
	using namespace NS_NonlinearSolver;

	// 1. Bisection method

	// Initial interval (range for volatility)
	double a = 0.1;		// 10%
	double b = 0.25;	// 25%

	// In this version all data is public; in a later version
	// make it private
	BisectionSolver bs;
	bs.myF = CallPrice;
	bs.a = a; bs.b = b;
	bs.tol = 0.0001;

	double result = bs.solve();
	cout << "Bisection: " << result << ", " << bs.accuracy() << endl;

	bs.printStatistics();

	/* NO NEWTON BECAUSE WE DO NOT HAVE THE DERIVATIVE!
	// Newton Method
	double initialGuess = 1.2;
	NewtonRaphsonSolver nr(initialGuess);
	nr.myF = CallPrice;
	//nr.derivative = DerivativeCallPrice;
	nr.tol = 0.0001;

	double resultNR = nr.solve();
	cout << "Newton Raphson: " << resultNR << endl;

	nr.printStatistics();
	*/

	// Secant method
	double initialGuess0 = 1.2;
	double initialGuess1 = 1.6;

	SecantMethodSolver sm(initialGuess0, initialGuess1, CallPrice);
	sm.tol = 0.0001;

	double resultSM= sm.solve();
	cout << "Secant Method: " << resultSM << endl;

	sm.printStatistics();

	cout << "Steffensen's method\n";

	// Steffensen's method
	double guess = 0.2;

	SteffensensSolver steff(guess, CallPrice);
	steff.tol = 0.0001;

	double resultST= steff.solve();
	cout << "Steffensen's Method: " << resultST << endl;

	steff.printStatistics();

	cout << "Finished\n";

	return 0;
}