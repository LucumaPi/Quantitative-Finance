// TestOneFactorPayoff.cpp
//
// Testing the one-factor payoff classes. In 
// this case we are using strategies.
//
// (C) Datasim Education BV 1998 - 2005
//

#include <iostream>
using namespace std;

#include "OneFactorPayoff.hpp"

// C procedural functions that play role of payoffs.
// Advantage: no classes needed!

double CallPayoffFN(double K, double S) 
{
		if (S > K)
			return (S - K);
		
		return 0.0;

}

double PutPayoffFN(double K, double S) 
{
		// max (K-S, 0)
		if (K > S)
			return (K - S);
		
		return 0.0;

}

int main()
{

	OneFactorPayoff pay1(20.0, CallPayoffFN);
	
	cout << "Give a stock price (plain Call): ";
	double S;
	cin >> S;

	cout << "Call Payoff is: " << pay1.payoff(S) << endl;

	OneFactorPayoff pay2(20.0, PutPayoffFN);
	
	cout << "Give a stock price (plain Put): ";
	cin >> S;

	cout << "Put Payoff is: " << pay2.payoff(S) << endl;

	

	return 0;
}
