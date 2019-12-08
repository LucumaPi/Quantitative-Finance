// TestOneFactorPayoff.cpp
//
// Testing the one-factor payoff classes. In 
// this case we are using strategies.
//
// (C) Datasim Education BV 1998 - 2005
//

#include <iostream>

#include <duffy/OneFactorPayoff.hh>

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
	
	std::cout << "Give a stock price (plain Call): ";
	double S;
	std::cin >> S;

	std::cout << "Call Payoff is: " << pay1.payoff(S) << std::endl;

	OneFactorPayoff pay2(20.0, PutPayoffFN);
	
	std::cout << "Give a stock price (plain Put): ";
	std::cin >> S;

	std::cout << "Put Payoff is: " << pay2.payoff(S) << std::endl;

	

	return 0;
}
