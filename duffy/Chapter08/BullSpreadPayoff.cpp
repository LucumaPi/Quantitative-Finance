// BullSpreadPayoff.cpp
//
// BullSpreadPayoff class.
//
// 5 june 1998	MB	Started
// 2005-5-16 DD Modified from Shape hierarchy
//
// (C) Datasim Education BV 1998 - 2005

#include "BullSpreadPayoff.hpp"


// Constructors and destructor
BullSpreadPayoff::BullSpreadPayoff(): Payoff()
{ // Default constructor

	K1 = K2 = 100.0; // Prototype value
	buyValue = 3.0;
	sellValue = 1.0;
}

BullSpreadPayoff::BullSpreadPayoff(double strike1, double strike2,
						double BuyVal, double SellVal): Payoff()
{ // Normal constructor with coordinates
 
	K1 = strike1;
	K2 = strike2;

	buyValue = BuyVal;
	sellValue = SellVal;
}


BullSpreadPayoff::BullSpreadPayoff(const BullSpreadPayoff& source): Payoff(source)
{ // Copy constructor

	K1 = source.K1;
	K2 = source.K2;

	buyValue = source.buyValue;
	sellValue = source.sellValue;
}

BullSpreadPayoff:: ~BullSpreadPayoff()
{ // Destructor

} 

// Selectors
double BullSpreadPayoff::Strike1() const
{// Return K1

	return K1;
}

double BullSpreadPayoff::Strike2() const
{// Return K2

	return K2;
}

// Modifiers
void BullSpreadPayoff::Strike1(double NewStrike1)
{// Set K1

	K1 = NewStrike1;
}

void BullSpreadPayoff::Strike2(double NewStrike2)
{// Set K2

	K2 = NewStrike2;
}

BullSpreadPayoff& BullSpreadPayoff::operator = (const BullSpreadPayoff &source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	// Call base class assignment
	Payoff::operator = (source);

	// Copy state
	K1 = source.K1;  
	K2 = source.K2;  

	buyValue = source.buyValue;
	sellValue = source.sellValue;

	return *this;
}


double BullSpreadPayoff::payoff(double S) const
{ // Based on Hull's book


		if (S >= K2)
			return K2 - K1;
		if (S <= K1)
			return 0.0;

		// In the interval [K1, K2]
		return S - K1;
}

double BullSpreadPayoff::profit(double S) const
{ // Profit

	return payoff(S) - (buyValue - sellValue);

}
