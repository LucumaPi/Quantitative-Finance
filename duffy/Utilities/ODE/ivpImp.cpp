// ivpimp.cpp
//
// Modelling IVP as a Bridge. Will be the prototype for
// more relevant PDE in QF.
// Get it working. 
// 
// This code implments the functions in IVP class. The
// Bridge implementation with pure functions.
//
//	2005-9-20 DD Kick-off
//	2005-9-27 DD new class with function pointers
//
// (C) Datasim Education BV 2005
//
// u' + a(x)u = f(x)
//

#ifndef IVPImp_cpp
#define IVPImp_cpp

#include <iostream>
#include <math.h>
using namespace std;

class IVPImp
{
public:
		// The coefficient of the zero-order term
		virtual double a(double x) = 0;

		// The coefficient of the inhomogeneous term
		virtual double f(double x) = 0;

};

// The Standard implementation of IVP. This is what you
// can use for testing

class STDImp : public IVPImp
{
public:
		STDImp() {}

		double a(double x)
		{ // simulates diffusion

			return 5.0;
		
		}

		double f(double x)
		{ // simulates drift

			return ::sin(x);
		}
};

struct Option
{
		
		double sig;
		double r;
		
		Option() {sig = 0.1; r = 0.06;}
		Option (double vol, double interest) { sig = vol; r = interest; }
};

class BSImp : public IVPImp
{
public:
		Option opt;

		BSImp() {}

		double a(double x)
		{ // simulates diffusion

			cout << "\nIn BS a " << opt.sig << ":";

			double v = opt.sig;
			
			return 0.5 * v * v * x * x;
		}

		double f(double x)
		{ // simulates drift

			cout << "\nIn BS f " << opt.r;

			return opt.r * x;
		}
};

class FunctionBasedImp : public IVPImp
{
public:
		double (*RHS) (double x);
		double (*Coeff) (double x);

public:

		FunctionBasedImp() {}

		double a(double x)
		{ // simulates diffusion

			return (*RHS)(x);
		
		}

		double f(double x)
		{ // simulates drift

			return (*Coeff)(x);

		}
};

#endif
