// OneFactorPayoff.hpp
//
// Special one factor payoff with a function pointer.
// This is specific but flexible. For example, we can handle
// both calls and puts very easily.
//
// (C) Datasim Education BV 1998 - 2005

#ifndef OneFactorPayoff_HH
#define OneFactorPayoff_HH

// Hard-coded, handy functions
double MyCallPayoffFN(double K, double S);
double MyPutPayoffFN(double K, double S) ;

class OneFactorPayoff
{
private:
	double K;
	double (*payoffFN)(double K, double S);
public:
	// Constructors and destructor
	OneFactorPayoff();
	OneFactorPayoff(double strike, double (*pay)(double K, double S));							// Default constructor
	OneFactorPayoff(const OneFactorPayoff& source);		// Copy constructor
	virtual ~OneFactorPayoff();					// Destructor
	
	// Operator overloading
	OneFactorPayoff& operator = (const OneFactorPayoff& source);	// Assignment operator

	double payoff(double S) const; // For a given spot price
};

#endif // OneFactorPayoff_HH