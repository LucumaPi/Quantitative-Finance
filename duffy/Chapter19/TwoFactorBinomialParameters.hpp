// TwoFactorBinomialParameters.hpp
//
// Simple structure to hold option data and numeric data for 
// the two-factor binomial method.
//
// This is a quick and dirty data structure just to test the 
// 2-factor binomial. But it works.
//
// (C) Datasim Education BV 2006
//

struct TwoFactorBinomialParameters
{
	// Option data
	double sigma1, sigma2;
	double T;
	double r;
	double K;
	double div1, div2;			// Dividends
	double rho;					// Correlation
	bool exercise;				// false if European, true if American	

	// Default constuctor, prototype object
	TwoFactorBinomialParameters()
	{
		sigma1 = 0.2;
		sigma2 = 0.3;
		T = 1.0;						// One year
		r = 0.06;
		K = 1;
		div1 = 0.03;
		div2 = 0.04;
		rho = 0.5;
		exercise = true;
	}


};

