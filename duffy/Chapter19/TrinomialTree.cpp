// TrinomialTree.cpp
//
// This class represents a trinomial tree model of the asset price.
// This model assumes that the asset price can reach tree values.
// When x = lnS, than the tree values can be calculated via:
// lnS = x + dx, lnS = x, lnS = x - dx. Thus S can become larger, smaller or
// stay same with a defined way.
//
// Started 30 october 2000 (JT)
// 2006-8-5 DD Update and rewrite
//
// (C) Datasim Component Technology 2000-2006

#include "TrinomialTree.hpp"
#include "Vector.cpp"
#include <math.h>
#include <iostream>
using namespace std;

#ifndef TRINOMIALTREE_CPP
#define TRINOMIALTREE_CPP

namespace Datasim
{



// Constructors and destructor
 
TrinomialTree::TrinomialTree()
{// Default constructor

	// No body
}

 
TrinomialTree::TrinomialTree(const TrinomialTree& tritree)
{// Copy-constructor

	// No body

}

 
TrinomialTree::TrinomialTree(TrinomialParameters& optionData)
{ // The most important constuctor

	par = &optionData;

	N = par->NumberOfSteps;

	/* NOT in this version
	// Build the tree

	// Exercise: optimise all this loop stuff
	TriTree = new Vector<Vector<double, long>, long>[N + 1];

	for(long n = N; n >= 0;n--)
	{
		TriTree[n] = 
			Vector<Vector<double, long>,long>(2*n+1,-n);
	}
	
	for(long nn = N; nn >= 0 ; nn--)
	{
		for(long j = -nn; j <= nn; j++)
		{
			TriTree[nn][j] = 0.0; // Magic number but OK
		}
	}	
	*/

}

 
TrinomialTree::~TrinomialTree()
{// Destructor

	delete [] option;
}

// Operator overloading
 
TrinomialTree& TrinomialTree::operator=(const TrinomialTree& tritree)
{// Assignment

	// No body
	return *this;

}


// Functions for declaration and initialisation of the trinomial tree
 

double TrinomialTree::Price(double S)
{// Calculate Call price: page 54 Clewlow figure 3.3 pseudo code
 // In this case wit dividend (div)

	double sig2 = par->sigma * par->sigma;

	double dt = par->T / double(N);
	double nu = par->r - par->div -0.5 * sig2;

	// Since trinomal is explicit FDM we have a constraint between
	// dt and dx (Clewlow inequality (3.27))
	double dx = par->sigma * ::sqrt(3.0 * dt); 
	double edx = ::exp(dx);

	// Temporary variables

	double nu2 = nu * nu;
	double dt2 = dt * dt;

	double dx2 = dx * dx;

	double tmp1 = (sig2 * dt + nu2 * dt2) / dx2;
	double tmp2 = nu * dt / dx;

	/* double pu = 0.5 * ( ( sig2 * dt + nu2 * dt2) / dx2 + nu * dt / dx); // page 53, formula 3.6
	double pm = 1.0 - (sig2 * dt + nu2 * dt2 ) / dx2;	// page 53, formula 3.7
	double pd = 0.5 * ( (sig2 * dt + nu2 * dt2) / dx2 - nu * dt / dx);	// page 53, formula 3.8*/

	double pu = 0.5 * (tmp1 + tmp2);
	double pm = 1.0 - tmp1;
	double pd = 0.5 * (tmp1 - tmp2);

	double disc = ::exp(-par->r * dt);

	// Initialise asset prices at *maturity*. Norice that the start index is a negative number
	Vector<double,long> asset(2*N+1,-N);

	asset[-N] = S * exp(-N*dx);
	for (long n = -N + 1; n <= N; n++)
	{
		asset[n] = asset[n-1] * edx;
	}

	cout << "finished asset\n";
	// Initialise option values at maturtity
	option = new Vector<double,long>[N+1];

	for (long n= N; n >= 0; n--)
	{
		for(long j = -n; j <= n;j++)
		{
			option[n] = Vector<double,long>(2*n+1,-n);
		}
	}

	long nn = N;
	if (par->type == 'C')
	{
		for(long j = -nn; j <= nn; j++)
		{
			option[nn][j] = std::max(0.0,asset[j] - par->K);
		}
	}
	else	// Put option
	{
		cout << "Put option\n";
		for(long j = -nn; j <= nn; j++)
		{
			option[nn][j] = std::max(0.0, par->K - asset[j]);
		}

	}

	// Step back through lattice, starting from maturity as given value n = N

	// European option
	if (par->exercise == false)
	{

		for(long n = N-1; n >= 0; n--)
		{
			for(long j =- n; j <= n; j++)
			{
				option[n][j] = disc*(pu*option[n+1][j+1]+pm*option[n+1][j]+pd*option[n+1][j-1]);
			}
		}
	}
	else	// American put only
	{
		cout << "American put option\n";
		double tmp;
		for(long n = N-1; n >= 0; n--)
		{
			for(long j =- n; j <= n; j++)
			{

				tmp = disc*(pu*option[n+1][j+1]+pm*option[n+1][j]+pd*option[n+1][j-1]);
				option[n][j] = std::max(tmp, par->K - asset[j]);
			}
		}
	}

	return option[0][0];
}

 	

} // End of name space Datasim

#endif // TRINOMIALTREE_CPP