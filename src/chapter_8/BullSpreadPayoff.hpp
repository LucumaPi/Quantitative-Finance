// BullSpreadPayoff.hpp
//
// Class for payoff for call options (1 factor)
//
// (C) Datasim Education BV 1998 - 2005

#ifndef BullSpreadPayoff_hpp
#define BullSpreadPayoff_hpp

#include "Payoff.hpp"

class BullSpreadPayoff: public Payoff
{ 
private:

	double K1;	// Strike price 1
	double K2;	// Strike price 2

	double buyValue;	// cost to buy
	double sellValue;	// sell value
public:

	// Constructors and destructor
	BullSpreadPayoff();									// Default constructor
	BullSpreadPayoff(double strike1, double strike2,
						double BuyVal, double SellVal);			
	BullSpreadPayoff(const BullSpreadPayoff& source);			// Copy constructor
	virtual ~BullSpreadPayoff();							// Destructor

	// Selectors
	double Strike1() const;							// Return strike price
	double Strike2() const;							// Return strike price

	// Modifiers
	void Strike1(double NewStrike1);					// Set strike price
	void Strike2(double NewStrike2);					// Set strike price

	BullSpreadPayoff& operator = (const BullSpreadPayoff& source);	// Assignment operator

	// Implment the pure virtual payoff function from base class
	double payoff(double S) const; // For a given spot price

	double profit(double S) const;			// Profit

};

#endif // BullSpreadPayoff_hpp
