// PayoffNamespace.cpp
//
// Source containing all payoff types
//
// (C) Datasim Education BV 2005
//

#ifndef PayoffNamespace_CC
#define PayoffNamespace_CC

namespace PayoffNamespace
{
	double K;
	int type;

	namespace CallPayoff
	{

		double OptPayoff(double S)
		{
		
			double tmp = S - K;
			if (tmp > 0.0)
				return tmp;

			return 0.0;
		}

	}

	namespace PutPayoff
	{

		double OptPayoff(double S)
		{
		
			double tmp = K - S;
			if (tmp > 0.0)
				return tmp;

			return 0.0;
		}
	}

}

#endif