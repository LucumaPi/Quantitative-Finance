// Instrument.hpp
//
// Classes for instruments. One-factor model!!
//
// (C) Datasim Education BV 2006
//

#ifndef INSTRUMENT_HH
#define INSTRUMENT_HH

#include "OneFactorPayoff.hh"
#include <iostream>

class Instrument
{
public: // Abstract Base class for all derivatives
};

class Option : public Instrument
{
public:
	// PUBLIC, PURE FOR PEDAGOGICAL REASONS
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double b;		// Cost of carry	
	double SMax;	// Far field condition
	char type;		// Call or put

	Option() {}

	void print()
	{

		std::cout << "Interest: " << r << std::endl;
		std::cout << "Vol: " << sig << std::endl;
		std::cout << "Strike: " << K << std::endl;
		std::cout << "Expiry: " << T << std::endl;
		std::cout << "Cost of carry: " << b << std::endl;
		std::cout << "Option type: " << type << std::endl;
		std::cout << "Far field: " << SMax << std::endl;
	}

	// An option uses a polymorphic payoff object
	OneFactorPayoff OptionPayoff;
};

class InstrumentFactory
{
public:

	virtual Option* CreateOption() const = 0;

};

class ConsoleInstrumentFactory : public InstrumentFactory
{
public:

	Option* CreateOption() const
	{
		double dr;		// Interest rate
		double dsig;	// Volatility
		double dK;		// Strike price
		double dT;		// Expiry date
		double db;		// Cost of carry	
		double dSMax;	// Far field boundary

		std::cout << "Interest rate: ";
		std::cin >> dr;

		std::cout << "Volatility: ";
		std::cin >> dsig;

		std::cout << "Strike Price: ";
		std::cin >> dK;
		dSMax = 4.0 * dK;		// Magix Number !!!!

		std::cout << "Expiry: ";
		std::cin >> dT;

		// Should ask what kind of option (as in Haug 1998)
		std::cout << "Cost of carry: ";
		std::cin >> db;

		Option* result = new Option;

		std::cout << "Payoff 1) Call, 2) Put: ";
		int ans;
		std::cin >> ans;
		if (ans == 1)
		{
			result-> type = 'C';
			(*result).OptionPayoff = OneFactorPayoff(dK, MyCallPayoffFN);
		}
		else
		{
			result-> type = 'P';
			(*result).OptionPayoff = OneFactorPayoff(dK, MyPutPayoffFN);
		}

		result->r	= dr;
		result->sig = dsig;
		result->K	= dK;
		result->T	= dT;
		result->b	= db;
		result->SMax = dSMax;

		return result;

	}
};

#endif