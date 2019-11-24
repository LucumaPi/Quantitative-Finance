// TrinomialParameters.hpp
//
// Simple structure to hold option data and numeric data for 
// the two-factor binomial method.
//
// This is a quick and dirty data structure just to test the 
// 2-factor binomial. But it works.
//
// (C) Datasim Education BV 2006
//

struct TrinomialParameters
{
	// Option data
	double sigma;
	double T;
	double r;
	double K;
	double div;			// Dividend
	char type;			// 'C' or 'P'
	bool exercise;		// false if European, true if American	

	// 'Numeric' data
	long NumberOfSteps;	// Nr. of subdivisions of [0, T]
};

