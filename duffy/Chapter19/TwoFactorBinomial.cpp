// TwoFactorBinomial.cpp
//
// This class represents a trinomial tree model of the asset price.
// This model assumes that the asset price can reach tree values.
// When x = lnS, than the tree values can be calculated via:
// lnS = x + dx, lnS = x, lnS = x - dx. Thus S can become larger, smaller or
// stay same with a defined way.
//
// Started 30 october 2000 (JT)
// 2006-8-5 DD Update and rewrite
// 2006-8-7 DD done for 2-factor binomial method
//
// (C) Datasim Component Technology 2000-2006

#include "TwoFactorBinomial.hpp"
#include "Vector.cpp"
#include "arraymechanisms.cpp"
#include "matrixmechanisms.cpp"
#include <math.h>
#include <iostream>
using namespace std;

#ifndef TwoFactorBinomial_CPP
#define TwoFactorBinomial_CPP

namespace Datasim
{



// Constructors and destructor
 
TwoFactorBinomial::TwoFactorBinomial()
{// Default constructor

	// No body
}

 
TwoFactorBinomial::TwoFactorBinomial(const TwoFactorBinomial& tritree)
{// Copy-constructor

	// No body

}

 
TwoFactorBinomial::TwoFactorBinomial(TwoFactorBinomialParameters& optionData, long NSteps,
									 double S1, double S2)
{ // The most important constuctor

	par = &optionData;

	N = NSteps;

	// Mesh sizes, Clewlow (2.43)-(2.44)
	k = par->T/double(N);			// DeltaT
	h1 = par->sigma1 * ::sqrt(k);	// DeltaX1
	h2 = par->sigma2 * ::sqrt(k);	// DeltaX2

	cout << "deltas t, S... " << k << ", " << h1 << ", " << h2 << endl;

	// Parameters (prob)
	double nu1 = par->r - par->div1 - (0.5 * par->sigma1 * par->sigma1);
	double nu2 = par->r - par->div2 - (0.5 * par->sigma2 * par->sigma2);

	cout << "nu1... " << nu1 << ", " << nu2 << endl;

	double a = h1*h2; double b = h2 * nu1 * k; double c = h1 * nu2 * k;
	double d = par->rho * par->sigma1 * par->sigma2 * k;

	//cout << "a ..." << a << ", " << b << ", " << c << ", " << d << endl;

	double disc = ::exp(-(par->r) * k);

	puu = disc * 0.25 * (a + b + c + d)/a; // eq. (2.45)
	pud = disc * 0.25 * (a + b - c - d)/a;
	pdu = disc * 0.25 * (a - b + c - d)/a;
	pdd = disc * 0.25 * (a - b - c + d)/a;

	cout << "puu ..." << puu << ", " << pud << ", " << pdu << ", " << pdd << endl;

	// Asset arrays
	// Initialise asset prices at *maturity*. Norice that the start index is a negative number
	asset1 = Vector<double,long>(2*N+1,-N);
	asset2 = Vector<double,long>(2*N+1,-N);

	asset1[-N] = S1 * ::exp(-N*h1);
	asset2[-N] = S2 * ::exp(-N*h2);

	double edx1 = ::exp(h1);
	double edx2 = ::exp(h2);

	cout << "edx1... disc " << edx1 << ", " << edx2 << ", " << disc << endl;

	for (long n = -N + 1; n <= N; n++)
	{
		asset1[n] = asset1[n-1] * edx1;
		asset2[n] = asset2[n-1] * edx2;
	}

	//print(asset1);
	//print(asset2);
	
	option = NumericMatrix<double,long>(2*N + 1, 2*N + 1, -N, -N);

	// Calculate option price at the expiry date
	for (long j = option.MinRowIndex(); j <= option.MaxRowIndex(); j += 2)
	{
		for (long k = option.MinColumnIndex(); k <= option.MaxColumnIndex(); k += 2)
		{

			option(j, k) = Payoff(asset1[j], asset2[k]);
		}
	}

	
}

 
TwoFactorBinomial::~TwoFactorBinomial()
{// Destructor

	
}

// Operator overloading
 
TwoFactorBinomial& TwoFactorBinomial::operator=(const TwoFactorBinomial& tritree)
{// Assignment

	// No body
	return *this;

}

// Payoff function (modify as needed)
inline
double TwoFactorBinomial::Payoff(double S1, double S2) const
{
	// Spread option
	return std::max(0.0, S1 - S2 - (par->K));
}


// Functions for declaration and initialisation of the trinomial tree
 

double TwoFactorBinomial::Price()
{// Calculate Call price: page 44 Clewlow 

	
	// Step back through lattice, starting from maturity as given value n = N

	// European option
	if (par->exercise == false)
	{

		for(long n = N-1; n >= 0; n--)
		{
			for(long j = -n; j <= n; j += 2)
			{
				for (long k = -n; k <= n; k += 2)
				{
					option(j, k) = puu * option(j+1, k+1) + pud * option(j+1,k-1)
									+ pdu * option(j-1, k+1) + pdd * option(j-1,k-1);
				}
			}
		}
	}
	else	// American put only
	{
		cout << "American exercise\n";
		for(long n = N-1; n >= 0; n--)
		{
			for(long j = -n; j <= n; j += 2)
			{
				for (long k = -n; k <= n; k += 2)
				{
					option(j,k) = puu * option(j+1, k+1) + pud * option(j+1,k-1)
									+ pdu * option(j-1, k+1) + pdd * option(j-1,k-1);

					option(j,k) = std::max(option(j,k), asset1[j] - asset2[k] - (par->K));
					
				}
			}
		}
	}

	return option(0,0);
}

 // Accuracy of price on number of steps
Vector<double, long> Prices(TwoFactorBinomialParameters& optionData, const Vector<long, long>& meshSizes, double S1,
												double S2) 
{
	// Caculates the price for a number of step sizes (usually increasing)

	Vector<double, long> result(meshSizes.Size());
	print (result);

	// TwoFactorBinomial(TwoFactorBinomialParameters& optinData,long NSteps,
	//									double S1, double S2); 

	TwoFactorBinomial* local;

	for (long j = result.MinIndex(); j <=  result.MaxIndex(); j++)
	{
		
			local = new TwoFactorBinomial(optionData, meshSizes[j], S1, S2);
		
			result[j] = local->Price();
			//cout << local->Price() << ";;";
			delete local;
		
	}

	return result;
}

} // End of name space Datasim

#endif // TwoFactorBinomial_CPP