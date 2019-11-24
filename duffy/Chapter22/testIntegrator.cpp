// TestIntegrator.cpp
//
// Testing Bridge pattern for numerical integration.
//
// (C) Datasim Education BV 2004
//

#include "numintegrator.hpp"
#include "integratorimp.hpp"
#include <math.h>
#include <iostream>
using namespace std;

double myfuncx (double x)
{ return log(x) / (1.0 - x); }


double myfuncx2 (double x)
{ return log(x) / (1.0 - x*x); }




int main()
{

	// Choose your specific integrator
	IntegratorImp* imp = new TanhRule;

	// Build NumIntegrator function
	Range<double> r(0.0, 1.0);			// Region of integration
	int N = 200;							// Number of subdivisions
	
	NumIntegrator context(myfuncx, r, (*imp), N);

	double result = context.value();

	cout << "And the value is: " << result << endl;

	// Choose another specific integrator
	IntegratorImp* imp2 = new MidpointRule;
	context = NumIntegrator(myfuncx, r, (*imp2), N);

	result = context.value();
	cout << "And the value is: " << result << endl;

	delete imp;
	delete imp2;

	return 0;
}
