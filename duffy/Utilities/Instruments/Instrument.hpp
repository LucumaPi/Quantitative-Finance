// Instrument.hpp
//
// Classes for instruments. One-factor model!!
//
// (C) Datasim Education BV 2006
//

#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include "OneFactorPayoff.hpp"
#include <iostream>
using namespace std;


class Instrument
{
public:

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

	Option()
	{

	}

	void print()
	{

		cout << "Interest: " << r << endl;
		cout << "Vol: " << sig << endl;
		cout << "Stike: " << K << endl;
		cout << "Expiry: " << T << endl;
		cout << "Cost of carry: " << b << endl;
		cout << "Option type: " << type << endl;
		cout << "Far field: " << SMax << endl;
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

		cout << "Interest rate: ";
		cin >> dr;

		cout << "Volatility: ";
		cin >> dsig;

		cout << "Strike Price: ";
		cin >> dK;
		dSMax = 4.0 * dK;		// Magix Number !!!!

		cout << "Expiry: ";
		cin >> dT;

		// Should ask what kind of option (as in Haug 1998)
		cout << "Cost of carry: ";
		cin >> db;

		Option* result = new Option;

		cout << "Payoff 1) Call, 2) Put: ";
		int ans;
		cin >> ans;
		if (ans == 1)
		{
			result-> type = 'C';
			(*result).OptionPayoff = 	OneFactorPayoff(dK, MyCallPayoffFN);
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