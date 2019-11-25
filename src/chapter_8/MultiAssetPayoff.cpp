// MultiAssetPayoff.cpp
//
// Base class for MultiAssetPayoffs.
//
// 5 june 1998	MB	Started
// 2005-5-16 DD Modified from Shape hierarchy
// 2005-7-16 DD Modified for 2-asset Correlation assets
//
// (C) Datasim Education BV 1998 - 2005

#include "MultiAssetPayoff.hpp"

// Constructors and destructor
MultiAssetPayoff::MultiAssetPayoff(MultiAssetPayoffStrategy& pstrat)
{ // Default constructor

	ps = &pstrat;
}

MultiAssetPayoff::MultiAssetPayoff(const MultiAssetPayoff& source)
{ // Copy constructor

	ps = source.ps;
}

MultiAssetPayoff:: ~MultiAssetPayoff()
{ // Destructor
}

// Operator overloading
MultiAssetPayoff& MultiAssetPayoff::operator = (const MultiAssetPayoff& source)
{ // Assignment operator

	if (this == &source)
		return *this;

	ps = source.ps;

	return *this;
}

// Not a pure virtual MultiAssetPayoff function anymore
double MultiAssetPayoff::Payoff(double S1, double S2) const
{ // For a given spot price
	
	return ps->payoff(S1, S2);	// DELEGATE to strategy
}
