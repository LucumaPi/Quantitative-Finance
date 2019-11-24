// TwoFactorBinomial.hpp
//
// This class represents a 2 FACTOR BINOMIAL tree model of the asset price.
// This model assumes that the asset price can reach tree values.
// When x = lnS, than the tree values can be calculated via:
// lnS = x + dx, lnS = x, lnS = x - dx. Thus S can become larger, smaller or
// stay same in a defined way.
//
// The data structure and algorithms are based on Clewlow and Stricklna 1988,
// pages 44-51.
//
// (C) Datasim Component Technology 2000-2006


#include "NumericMatrix.cpp"
#include "TwoFactorBinomialParameters.hpp"


#ifndef TwoFactorBinomial_HPP
#define TwoFactorBinomial_HPP

namespace Datasim
{

class TwoFactorBinomial
{
private:

	TwoFactorBinomialParameters* par;	// The source of the data

	long N;								// Redundant parameter, number of time steps

	// Probability parameters
	double puu, pdd, pud, pdu;

	// Mesh sizes
	double h1, h2, k;

	// Array structures
	Vector<double, long> asset1, asset2;

	// Data structure as in Clewlow; 2d matrix
	NumericMatrix<double,long> option; 


private:

	// Some constructors are private
	TwoFactorBinomial();	// Default constructor
	TwoFactorBinomial(const TwoFactorBinomial& tritree); // Copy-constructor
	// Operator overloading
	TwoFactorBinomial& operator=(const TwoFactorBinomial& tritree);	// Assignment

public:
	// Construct a tree with given option data
	TwoFactorBinomial(TwoFactorBinomialParameters& optinData,long NSteps,
										double S1, double S2); 
	virtual ~TwoFactorBinomial();	// Destructor

	// Payoff function (modify as needed)
	double Payoff(double S1, double S2) const;

	// Calculate call price
	double Price();

	
 

// Accuracy of price on number of steps
	friend Vector<double, long> Prices(TwoFactorBinomialParameters& optinData, const Vector<long, long>& meshSizes,
										double S1, double S2);
};

} // End of namespace Datasim

#endif // TwoFactorBinomial_HPP