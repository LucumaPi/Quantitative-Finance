// integratorimp.hpp
//
// Classes that actually do integartion of one-dimensional functions.
//
// (C) Datasim Education BV 2003
//

#ifndef IntegratorImp_hpp
#define IntegratorImp_hpp



#include "Numintegrator.hpp"

class IntegratorImp
{
public:


	virtual double value(const NumIntegrator& f) const = 0;

};

class TanhRule: public IntegratorImp
{ // Rule for integrating nasty functions; based on Duffy 1980

private:

		// Possibility for caching

public:


	virtual double value(const NumIntegrator& f) const;


};

class MidpointRule: public IntegratorImp
{ // The Midpoint integration rule

private:

		// Possibility for caching

public:


	virtual double value(const NumIntegrator& f) const;



};

#endif