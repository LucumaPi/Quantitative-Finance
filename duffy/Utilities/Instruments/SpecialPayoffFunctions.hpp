// SpecialPayoffFunctions.hpp
//
// Specific payoff functions
//
// (C) Datasim Education BV 2006
//

#ifndef SpecialPayoffFunctions_HPP
#define SpecialPayoffFunctions_HPP


double MyCallPayoffFN(double K, double S) 
{
		if (S > K)
			return (S - K);
		
		return 0.0;

}

double MyPutPayoffFN(double K, double S) 
{
		// max (K-S, 0)
		if (K > S)
			return (K - S);
		
		return 0.0;
}


#endif