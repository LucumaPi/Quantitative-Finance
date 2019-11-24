// BasicOption.hpp
//
// Class that represents  solutions to European options. This is
// an implementation using basic C++ syntax only. It has been 
// written for pedagogical reasons.
//
//	The member data are public for convenience only
//
// (C) Datasim Component Technology BV 2003
//
//

#ifndef BasicOption_hpp
#define BasicOption_hpp


#include <string>
using namespace std;

class BasicOption
{
public:				// For TEST purposes only

	void init();	// Initialise all default values
	void copy(const BasicOption& o2);

	// 'Kernel' functions for option calculations
	double CallPrice(double U) const;
	double PutPrice(double U) const;
	double CallDelta(double U) const;
	double PutDelta(double U) const;

	// Gaussian functions
	double n(double x) const;
	double N(double x) const;


	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double b;		// Cost of carry

	string otyp;	// Option name (call, put)


public:	// Public functions
	BasicOption();							// Default call option
	BasicOption(const BasicOption& option2);	// Copy constructor
	BasicOption (const string& optionType);	// Create option type
	virtual ~BasicOption();	

	BasicOption& operator = (const BasicOption& option2);

	// Functions that calculate option price and sensitivities
	double Price(double U) const;
	double Delta(double U) const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

	void dumpPrint() const;

	double payoff(double U) const;

};

#endif