// TestTrinomial.cpp
//
// Simple test program for Trinomial method
//
// (C) Datasim Eduction BV 2006
//

#include "TrinomialTree.hpp"
#include <iostream>
using namespace std;

int main()
{

	// Declare and initialise the parameters
	TrinomialParameters myData;

	// Clewlow p. 55 C = 8.42534 for N = 3
	myData.sigma = 0.2;
	myData.T = 1.0;		// One year
	myData.r = 0.06;
	myData.K = 100;
	myData.div = 0.03;
	myData.type = 'C';
	myData.exercise = false;
	myData.NumberOfSteps = 3;

	cout << "How many timesteps: ";
	cin >> myData.NumberOfSteps;

	// Now define option-related calculations
	using namespace Datasim;			
	TrinomialTree myTree(myData);
	cout << myTree.Price(100) << endl;

	// Clewlow p. 14 check against binomial method C = 10.1457
	myData.sigma = 0.2;
	myData.T = 1.0;		// One year
	myData.r = 0.06;
	myData.K = 100;
	myData.div = 0.0;
	myData.type = 'C';
	myData.exercise = false;
	//myData.NumberOfSteps = 3;

	cout << myTree.Price(100) << endl;

	// Clewlow p. 63 American Put
	myData.sigma = 0.2;
	myData.T = 1.0;		// One year
	myData.r = 0.06;
	myData.K = 100;
	myData.div = 0.0;
	myData.type = 'P';				// Put
	myData.exercise = true;
	//myData.NumberOfSteps = 3;

	cout << myTree.Price(100) << endl;
	return 0;
}
