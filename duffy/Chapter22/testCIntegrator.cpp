// TestCIntegrator.cpp
//
// Testing numerical integration using C functions.
//
// (C) Datasim Education BV 2004-2006
//

#include <math.h>
#include <iostream>
using namespace std;
/*
double myFunc (double x)
{ return x*x*x; }


double myFunc (double x)
{ return (1.0 + cos(x)) * (log (1.0 + cos(x))); }*/

//double myFunc (double x)
//{ return ::exp(+10.0*x) - 1.0; }
//double myFunc (double x)
//{ return 1.0 - ::exp(-10.0*x); }

//double myFunc (double x)
//{ return x/(10.0*(1.0 + x)); }

//double myFunc (double x)
//{ return (x - 1.0)/(10.0*x); }

double myFunc (double x)
{ // CGMY

	double a = 1.0; double b = 10.0; double c = 10.0; double alpha = -1.0;;

	if (x <= 0.0)
	{
		return a*::exp(-b*::fabs(x)) / pow(::fabs(x), 1.0+alpha);
	}
	if (x > 0.0)
	{
		return a*::exp(-c*::fabs(x)) / pow(::fabs(x), 1.0+alpha);
	}

	//return 0.0;

}

//double myFunc (double x)
//{ return (1.0 - ::exp(-10.0*x))/::exp(-10.0*x); }


//double myFunc (double x)
//{ return ::exp(-x)* cos(x); }

double myFunc2 (double x)
{ return log(x) / (1.0 - x); }

//double myFunc (double x)
//{ return (1.0 + cos(x)) * (log (1.0 + cos(x))); }

double MidpointRuleValue(double (*f)(double x), double A, double B, int N) 
{ // Integrate f on the interval [A, B] using the midpoint rule

	double res = 0.0;
	double h = (B - A)/ double (N);
	for (double x = A + (0.5 * h); x < B; x += h)
	{

	      res += f(x);
	}
	 
	return res*h;
}

double TanhRuleValue(double (*f)(double x), double A, double B, int N) 
{ // Integrate f on the interval [A, B] using the Tanh rule for 1d case

	double res = 0.0;
	double h = (B - A)/ double (N);
	for (double x = A + (0.5 * h); x < B; x += h)
	{
		res += tanh( (*f)(x) * 0.5 * h);
	}

   return 2.0 * res;
}

int main()
{

	int N = 20200;							// Number of subdivisions
	
	double A = 0.0;
//	double B = 2.0 * 3.1415;
//	double B = ::exp(10.0);
//	double B = 2888222.0;
	double B = 1.0;

	double d = MidpointRuleValue(myFunc, A, B, N);
	cout << "Approximate integral Midpoint rule is: " << d << endl;
	double d1 = TanhRuleValue(myFunc, A, B, N);
	cout << "Approximate integral Tanh rule is: " << d1 << endl;


	//double d2 = MidpointRuleValue(myFunc2, A, B, N);
	//cout << "Approximate integral is: " << d2 << ", Exact: " << - (3.1415)*(3.1415)/6.0 << endl;
	

	return 0;
}
