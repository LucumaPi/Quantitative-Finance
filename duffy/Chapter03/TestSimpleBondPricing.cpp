// TestSimpleBondPricing.cpp
//
// (C) Datasim Education BV 2006
//

#include "SimpleBondPricing.hpp"
#include <iostream>
using namespace std;

int main()
{

	// Future value of a sum of money invested today
	long nPeriods = 6;				// 6 years
	double P = 10000000;	// Amount invested now
	double r = 0.092;		// 9.2% interest

	double fv = Chapter3CPPBook::FutureValue(P, nPeriods, r);

	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout << "Future Value: " << fv << endl;

	long frequency = 2;
	double fv2 = Chapter3CPPBook::FutureValue(P, nPeriods, r, frequency);
//	cout.setf(0, ios_base::floatfield);

	cout << "Future Value, 2 periods: " << fv2 << endl;

	// Future value of a sum of money invested today, m periods 
	// per year. r is annual interest rate

	// Using: means that we search in NS for the functions
	using namespace Chapter3CPPBook;

	double P0 = 10000000; // 10 million
	r = 0.092;
	long m = 2;	// Twice per year
	nPeriods = 6;
	cout << "**Future with " << m << " periods: " << FutureValue(P0, nPeriods, r, m) << endl;

	// Future value of an ordinary annuity
	double A = 2000000;
	r = 0.08;
	nPeriods = 15;	// 15 years
	cout << "**Ordinary Annuity; " << OrdinaryAnnuity(A, nPeriods, r)  << endl;

	// Present Value
	double Pn = 5000000;
	r = 0.10;
	nPeriods = 7;
	cout << "**Present value: " << PresentValue(Pn, nPeriods, r) << endl;

	// Present Value of a series of future values
	Vector futureValues(5); // For five years
	for (long j = 0; j < 4; j++)
	{ // The first 4 years
		futureValues[j] = 100.0;
	}
	futureValues[4] = 1100.0;

	nPeriods = 5; // Redundant in a sense since this is in the vector
	r = 0.0625;
	cout << "**Present value, series: " << PresentValue(futureValues, nPeriods, r) << endl;

	// Present Value of an ordinary annuity
	A = 100.0;
	r = 0.09;
	nPeriods = 8;
	cout << "**PV, ordinary annuity: " << PresentValueOrdinaryAnnuity(A, nPeriods, r) << endl;

	// Now test periodic testing with continuous compounding
	P0 = 10000000;
	r = 0.092;
	nPeriods = 6;
	for (long mm = 1; mm <= 10000000; mm *=12)
	{
		cout << "Periodic: " << mm << ", " << FutureValue(P0, nPeriods, r, mm) << endl;

	}

	cout << "Continuous Compounding: " << FutureValueContinuous(P0, nPeriods, r);

	return 0;
}
