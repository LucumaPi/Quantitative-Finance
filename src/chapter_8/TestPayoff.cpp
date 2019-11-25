// TestPayoff.cpp
//
// Testing the one-factor payoff classes
//
// (C) Datasim Education BV 1998 - 2005
//

#include "CallPayoff.hpp"
#include "BullSpreadPayoff.hpp"
#include <iostream>

int main()
{
	
	CallPayoff call(20.0);
	
	std::cout << "Give a stock price (plain Call): ";
	double S;
	std::cin >> S;

	std::cout << "Call Payoff is: " << call.payoff(S) << std::endl;
	
	double K1 = 30.0;		// Strike price of bought call
	double K2 = 35.0;		// Strike price of sell call
	double costBuy = 3.0;	// Cost to buy a call
	double sellPrice = 1.0;	// Sell price for call
	BullSpreadPayoff bs(K1, K2, costBuy, sellPrice);	// Hull example

	std::cout << "Give a stock price (BullSpread): ";
	std::cin >> S;

	std::cout << "Bull Spread Payoff is: " << bs.payoff(S) << std::endl;
	std::cout << "Bull Spread Profit is: " << bs.profit(S) << std::endl;

	return 0;
}
