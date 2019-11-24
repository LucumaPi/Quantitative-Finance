// Option2.hpp
//
// Class that represents  solutions to European options. This is
// an implementation using basic C++ syntax only. It has been 
// written for pedagogical reasons
//
// In this cass an option 'listens' to changes in an asset price and
// hence we are applying the Observer pattern.
//
// (C) Datasim Component Technology BV 2003-2004
//

#ifndef Option_hpp
#define Option_hpp

#include "product.hpp"
#include <string>
using namespace std;


class Option : public Product
{
public:				// For TEST purposes only

	void init();	// Initialise all default values
	void copy(const Option& o2);

	// 'Kernel' functions for option calculations
	double CallPrice() const;
	double PutPrice() const;
	double CallDelta() const;
	double PutDelta() const;
	double CallGamma() const;
	double PutGamma() const;
	double CallVega() const;
	double PutVega() const;
	
	// Gaussian functions
	double n(double x) const;
	double N(double x) const;


	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double U;		// Current underlying price (e.g. stock, forward)
	double b;		// Cost of carry

	string otyp;	// Option name (call, put)
	string unam;	// Name of underlying asset

//	Asset* underlying;

public:	// Public functions
	Option();							// Default call option
	Option(const Option& option2);	// Copy constructor
	Option (const string& optionType);	// Create option type
	virtual ~Option();	

	// Functions associated with Observer pattern
//	void Update(Observable* obj);


	Option& operator = (const Option& option2);

	// Functions that calculate option price and sensitivities
	double Price() const;
	double Delta() const;
	double Gamma() const;
	double Vega() const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

	// Special copy function to create a copy of a Product when you only have a Product pointer
	Product* Clone() const;		// Create a copy of the Product
//	virtual void Accept(CDOVisitor& v) { v.Visit(*this);}	// Accept a visitor


};

#endif