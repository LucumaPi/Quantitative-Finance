// Option.hpp
//
//
// (C) Datasim Component Technology BV 2003-2005
//

#ifndef Option_hpp
#define Option_hpp

class Option
{
public:

	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
//	double U;		// Current underlying price (e.g. stock, forward)
//	double b;		// Cost of carry
	int type;		// 1 == Call, 2 == Put

	double payoff(double S)const
	{
		if (type == 1)
		{
			if (S > K)
				return (S - K);
		
			return 0.0;
		}
		else
		{
			if (S < K)
				return -(S - K);
		
			return 0.0;
		}
	}
};

#endif