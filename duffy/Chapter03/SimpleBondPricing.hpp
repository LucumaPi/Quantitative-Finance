// SimpleBondPricing.hpp
//
// Simple functions for interest rate calcuations.
//
// (C) Datasim Education BV 2006
//

#ifndef SimpleBondPricing_HPP
#define SimpleBondPricing_HPP

#include <vector>
using namespace std;

namespace Chapter3CPPBook // Logical grouping of functions and others
{

	// Handy shorthand synonyms
	typedef vector<double> Vector;

	// Recursive function to calculate power of a number. This 
	// function calls itself, either directly or indirectly
	double power(double d, long n);

	// Future value of a sum of money invested today
	double FutureValue(double P0, long nPeriods, double r);

	// Future value of a sum of money invested today, m periods 
	// per year. r is annual interest rate
	double FutureValue(double P0, long nPeriods, double r, long m);

	// Continuous compounding, i.e. limit as m -> INFINITY
	double FutureValueContinuous(double P0, long nPeriods, double r);

	// Future value of an ordinary annuity
	double OrdinaryAnnuity(double A, long nPeriods, double r);

	// Present Value
	double PresentValue(double Pn, long nPeriods, double r);

	// Present Value of a series of future values
	double PresentValue(const Vector& prices, long nPeriods, double r);

	// Present Value of an ordinary annuity
	double PresentValueOrdinaryAnnuity(double A, long nPeriods, double r);


}

#endif