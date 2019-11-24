// TestTwoFactorBinomial.cpp
//
// Simple test program for Two Factor Binomial method
//
// (C) Datasim Eduction BV 2006
//

#include "TwoFactorBinomial.hpp"
#include "ArrayMechanisms.cpp"
#include <iostream>
using namespace std;

int main()
{

	// Declare and initialise the parameters
	TwoFactorBinomialParameters myData;

	// Clewlow p. 47 
	myData.sigma1 = 0.2;
	myData.sigma2 = 0.3;
	myData.T = 1.0;						// One year
	myData.r = 0.06;
	myData.K = 1.0;
	myData.div1 = 0.03;
	myData.div2 = 0.04;
	myData.rho = 0.5;
	myData.exercise = false;

	cout << "How many timesteps: ";
	long NumberOfSteps;
	cin >> NumberOfSteps;

	// Now define option-related calculations
	using namespace Datasim;			
	double S1 = 100.0;
	double S2 = 100.0;
	TwoFactorBinomial myTree(myData, NumberOfSteps, S1, S2);
	cout << myTree.Price() << endl;

	// Now examine the convergence of 2-factor Binomial method
	long size = 8;
	Vector<long, long> meshSizes(size);
	long N = 4;
	for (long j = meshSizes.MinIndex() ; j <=  meshSizes.MaxIndex(); j++)
	{
			meshSizes[j] = N;
			N *= 2;
			
	}
	print(meshSizes);
	
	Vector<double, long> result = Prices(myData, meshSizes, S1, S2);

	// Exercise for student: display in Excel
	print(result);

	return 0;
}
