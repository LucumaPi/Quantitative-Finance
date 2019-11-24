// ExtendedOption.hpp
//
// Class that represents exact solutions to European options.
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef ExtendedOption_hpp
#define ExtendedOption_hpp

#include "vector.cpp"

#include <string>
using namespace std;

class Option
{ // Abstract base class for the options in this book
public:

	virtual double Price(double U) const = 0;

};

class ExtendedOption : public Option
{
private:

	void init();	// Initialise all default values
	void copy(const ExtendedOption& o2);

	// 'Kernel' functions for option calculations
	double CallPrice(double U) const;
	double PutPrice(double U) const;
	double CallDelta(double U) const;
	double PutDelta(double U) const;
	double CallGamma(double U) const;
	double PutGamma(double U) const;
	double CallVega(double U) const;
	double PutVega(double U) const;
	double CallTheta(double U) const;
	double PutTheta(double U) const;
	double CallRho(double U) const;
	double PutRho(double U) const;
	double CallCoc(double U) const;
	double PutCoc(double U) const;
	double CallElasticity(double percentageMovement, double U) const;
	double PutElasticity(double percentageMovement, double U) const;
	double CallStrike(double U) const;	// As a functions of the strike price dc/dK FIRST derivative
	double PutStrike(double U) const;
	double CallSecondStrike(double U) const;	// As a functions of the strike price: SECOND derivative
	double PutSecondStrike(double U) const;

	// Gaussian functions
	double n(double x) const;
	double N(double x) const;


public:	// Public property section
	double r;		// Interest rate
	double sig;	// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double U;		// Current underlying price (e.g. stock, forward)
	double b;		// Cost of carry

	string otyp;	// Option name (call, put)

//	Property<string, double>* curr;		// Points to one specific property

public:	// Public functions
	ExtendedOption();							// Default call option
	ExtendedOption(const ExtendedOption& option2);	// Copy constructor
	ExtendedOption (const string& optionType);	// Create option type
	ExtendedOption (const string& optionType, const string& underlying);	// Create option type
	virtual ~ExtendedOption();	

	ExtendedOption& operator = (const ExtendedOption& option2);

	// Functions that calculate option price and sensitivities
	double Price(double U) const;
	double Delta(double U) const;
	double Gamma(double U) const;
	double Vega(double U) const;
	double Theta(double U) const;
	double Rho(double U) const;
	double Coc(double U) const;										// Cost of carry
	double Elasticity(double percentageMovement, double U ) const;		// Elasticity


	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

};


#endif