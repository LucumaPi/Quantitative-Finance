// MultiAssetPayoff.hpp
//
// Generic MultiAssetPayoff class with an embedded Strategy
// patterns. This means that we can create lightweight
// strategies and is less 'copy-and-paste' dependent than
// using inheritance.
//
// (C) Datasim Education BV 1998 - 2005

#ifndef MultiAssetPayoff_hpp
#define MultiAssetPayoff_hpp

#include <iostream>
using namespace std;

#include "MultiAssetPayoffStrategy.hpp"

class MultiAssetPayoff
{
private:
	MultiAssetPayoffStrategy* ps;
public:
	// Constructors and destructor
	MultiAssetPayoff(MultiAssetPayoffStrategy& pstrat);							// Default constructor
	MultiAssetPayoff(const MultiAssetPayoff& source);		// Copy constructor
	virtual ~MultiAssetPayoff();					// Destructor
	
	// Operator overloading
	MultiAssetPayoff& operator = (const MultiAssetPayoff& source);	// Assignment operator

	// Not a pure virtual MultiAssetPayoff function anymore
	virtual double Payoff(double S1, double S2) const; // For given spot prices S1, S2
};

#endif // MultiAssetPayoff_hpp