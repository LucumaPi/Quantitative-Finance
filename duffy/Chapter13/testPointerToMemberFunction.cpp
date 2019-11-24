// testPointerToMemberFunction.cpp
//
// Testing pointers to member functions. This is 
// documented in Stroustrup 3rd edition page 418
//
// (C) Datasim Education BV 2005

#include "payoff.cpp"

#include <iostream>
using namespace std;

typedef double (Payoff::* PMember)(double value);

class Option
{

public:
	Payoff pay;
//	typedef double (Payoff::* PMember)(double value);
	PMember pm;

	double K;
	double T;
	// etc.

	Option ()
	{
		K = 100;
		T = 1.0;

		// Must define these later
		pay = Payoff(K);
		
	}

	Option (PMember func)
	{
		K = 100;
		T = 1.0;

		pay = Payoff(K);
		pm = func;
	}

	double payoff(double S)
	{
		return (pay.*pm)(S);
	}
};

int main()
{
	Option myOption;
	Payoff myPayoff(myOption.K);
	PMember myFunc = Payoff::Call;
	myOption.pay = myPayoff;
	myOption.pm = myFunc;

	double d = myOption.payoff(23);
	
	cout << "Call " << d << endl;

	myFunc = Payoff::Put;
	myOption.pm = myFunc;
	d = myOption.payoff(23);

	cout << "Put " << d << endl;


	return 0;
}
