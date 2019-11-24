// MultiAssetPayoffStrategy.hpp
//
// Lightweight classes for payoff functions. You can 
// add your own payoff classes here.
//
// 2005-7-16 DD Multi-asset (n = 2) case.
// 2005-12-20 DD Review + corresponding Factory.
// 2006-1-20 DD to reader are formulae OK?
//
// (C) Datasim Education BV 1998 - 2006

#ifndef MultiAssetPayoffStrategy_hpp
#define MultiAssetPayoffStrategy_hpp

#include "Inequalities.hpp"


class MultiAssetPayoffStrategy
{
public:
		virtual double payoff(double S1, double S2) const = 0;
};


class ExchangeStrategy : public MultiAssetPayoffStrategy
{
private:
		// No member data
public:
		ExchangeStrategy() { }
		double payoff(double S1, double S2) const
		{
			return DMax(S1-S2, 0.0);
		}
};

class RainbowStrategy : public MultiAssetPayoffStrategy
{
private:
		double K;	// Strike
		double w;	// +1 call, -1 put
		int type;	// DMax (1) or DMin (!1) of 2 assets
public:
		RainbowStrategy(double strike, double cp, int DMinDMax)
		{ K = strike; w = cp; type = DMinDMax; }
		double payoff(double S1, double S2) const
		{
			if (type == 1)	// DMax
				return DMax ( w * DMax(S1,S2) - w*K, 0.0);

			return DMax( w * DMin(S1,S2) - w*K, 0.0);
		}
};

class BasketStrategy : public MultiAssetPayoffStrategy
{ // 2-asset basket option payoff

private:
		double K;		// Strike
		double w;		// +1 call, -1 put
		double w1, w2;	// w1 + w2 = 1
public:
		// All classes need default constructor
		BasketStrategy()
		{ K = 95.0; w = +1; w1 = 0.5; w2 = 0.5;
		}

		BasketStrategy(double strike, double cp,double weight1, double weight2)
		{ K = strike; w = cp; w1 = weight1; w2 = weight2;
		}
		double payoff(double S1, double S2) const
		{
	
			double sum = w1*S1 + w2*S2;

			return DMax(w* (sum - K), 0.0);
		}
};

class BestWorstStrategy : public MultiAssetPayoffStrategy
{
private:
		double K;		// Strike
		double w;		// +1 Best, -1 Worst
		
public:
		BestWorstStrategy(double cash, double BestWorst)
		{ K = cash; w = BestWorst;}

		double payoff(double S1, double S2) const
		{
	
			if (w == 1)	// Best
				return DMax (S1, S2, K);

			return DMin (S1, S2, K);
		}
};

class QuotientStrategy : public MultiAssetPayoffStrategy
{
private:
		double K;	// Strike
		double w;	// +1 call, -1 put
		
public:
		QuotientStrategy(double strike, double cp)
		{ K = strike; w = cp; }
		double payoff(double S1, double S2) const
		{
			return DMax ( w * (S1/S2) - w*K, 0.0);

		}
};

class QuantoStrategy : public MultiAssetPayoffStrategy
{
private:
		double Kf;	// Strike in foreign currency
		double fer;	// Fixed exchange rate
		double w;	// +1 call, -1 put
		
public:
		QuantoStrategy(double foreignStrike, double cp, double forExchangeRate)
		{ Kf = foreignStrike; w = cp; fer = forExchangeRate; }

		double payoff(double S1, double S2) const
		{
			return fer * DMax ( w * S1 - w*Kf, 0.0);

		}
};

class SpreadStrategy : public MultiAssetPayoffStrategy
{
private:
		double K;		// Strike
		double w;		// +1 call, -1 put
		double a, b;	// a > 0, b < 0
public:
		SpreadStrategy(double cp, double strike = 0.0, double A = 1.0, double B = -1.0)
		{ K = strike; w = cp; a = A; b = B;}
		double payoff(double S1, double S2) const
		{
	
			double sum = a*S1 + b*S2;

			return DMax(w* (sum - K), 0.0);
		}
};

class DualStrikeStrategy : public MultiAssetPayoffStrategy
{
private:
		double K1, K2;
		double w1, w2;
public:
		DualStrikeStrategy(double strike1, double strike2, double cp1, double cp2)
		{ K1 = strike1; K2 = strike2;
		  w1 = cp1; w2 = cp2;
		}

		double payoff(double S1, double S2) const
		{

			return DMax (w1*(S1-K1), w2*(S2-K2), 0.0);

		}
};

class OutPerformanceStrategy : public MultiAssetPayoffStrategy
{
private:
		double I1, I2;	// Values of underlyings at maturity
		double w;		// Call +1 or put -1
		double k;		// Strike rate of option

public:
		OutPerformanceStrategy(double currentRate1, double currentRate2, double cp,
								double strikeRate)
		{ I1 = currentRate1; I2 = currentRate2;
		  w = cp; k = strikeRate;
		}

		double payoff(double S1, double S2) const
		{

			return DMax (w*((I1/S1) - (I2/S2)) - w* k, 0.0);

		}
};

#endif