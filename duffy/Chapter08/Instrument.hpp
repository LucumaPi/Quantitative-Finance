// Instrument.hpp
//
// Classes for instruments. Two Factor models.
//
// N.B.
// N.B. This class is special because it models what is 
// essentially a two-factor basket PUT option.
// 
// You can easily modify this class for your own objectives. 
// But take care of the data for the payoff functions!
//
// See chapters 24 and 32 of my FDM book for more details. 
//
// ALSO
//			Topper 2005, page 216 (Case Study, Basket Option)
//			(3D case)
//			Topper 2005, page 197(Case Study, Basket Optioon)
//			(2D case)
//			Bhansali 1998, pages 210-212 
//			
//
// 2006-1-31 DD new name TwoFactorOptionData + now work with a Specific
// BasketStrategy
// 2006-2-1 DD Prototype Factory created (save typing in information during debugging)
//
// (C) Datasim Education BV 2006
//

#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include <iostream>
using namespace std;

///////////////////// Strategy /////////////////////////////////////////////////////
class BasketStrategy			
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

			if (w*(sum-K) > 0.0)
				return (w*(sum - K));
			return 0.0;
		}
};
//////////////////////// End of Strategy //////////////////////////////////////

class TwoFactorInstrument
{
public:

};

class TwoFactorOptionData : public TwoFactorInstrument
{
//private:
public: // For convenience only
	// An option uses a polymorphic payoff object
	BasketStrategy pay;
public:
	// PUBLIC, PURE FOR PEDAGOGICAL REASONS, 13 parameters
	double r;				// Interest rate
	double D1, D2;			// Dividends
	double sig1, sig2;		// Volatility
	double rho;				// Cross correlation
	double K;				// Strike price, now place in IC
	double T;				// Expiry date
	double SMax1, SMax2;	// Far field condition
	double w1, w2;
	int type;				// Call +1 or put -1

	TwoFactorOptionData()
	{
		// Initialise all data and the payoff

		// Use Topper's data as the default, Table 7.1

		r = 0.01;
		D1 = D2 = 0.0;
		sig1 = 0.1; sig2 = 0.2;
		rho = 0.5;
		
		K = 40.0;
		T = 0.5;

		w1 = 1.0;
		w2 = 20.0;

		type = -1;

		// Now create the payoff Strategy object
		/* BasketStrategy(double strike, double cp,double weight1, double weight2)
		{ K = strike; w = cp; w1 = weight1; w2 = weight2;} */
		
		pay = BasketStrategy(K, type, w1, w2);

		// In general 1) we need a Factory object as we have done
		// in the one-dimensional case and 2) work with pointers to
		// base classes
	}

	double payoff(double x, double y) const
	{
		return pay.payoff(x, y);
	}

};

class InstrumentFactory
{
public:

	virtual TwoFactorOptionData* CreateOption() const = 0;

};

class ConsoleInstrumentFactory : public InstrumentFactory
{
public:

	TwoFactorOptionData* CreateOption() const
	{

		double dr;		// Interest rate
		double dsig1, dsig2;	// Volatility
		double div1, div2;	// Dividends
		double drho;
		double dK;		// Strike price
		double dT;		// Expiry date
		double dSMax1, dSMax2;	// Far field boundary

		double dw1, dw2;	// Weights of each asset
		int dtype;		// C +1, P -1
L1:
		cout << "Type Call +1, Put -1: ";
		cin >> dtype;
		dtype = -1;		// !!! for the moment

		cout << "Interest rate: ";
		cin >> dr;

		cout << "Strike: ";
		cin >> dK;

		cout << "Volatility 1: ";
		cin >> dsig1;

		cout << "Volatility 2: ";
		cin >> dsig2;

		cout << "Dividend 1: ";
		cin >> div1;

		cout << "Dividend 2: ";
		cin >> div2;

		cout << "Correlation: ";
		cin >> drho;

		cout << "First Far Field: ";
		cin >> dSMax1;
		cout << "Second Far Field: ";
		cin >> dSMax2;

		cout << "weight 1: ";
		cin >> dw1;

		cout << "Weight 2: ";
		cin >> dw2;

		cout << "Expiry: ";
		cin >> dT;

		cout << "Is this correct, carry on?";
		char c; cin >> c;
		if (c != 'y' && c != 'Y')
		{
			goto L1;
		}

		TwoFactorOptionData* result = new TwoFactorOptionData;

		result->r		= dr;
		result->sig1	= dsig1;
		result->sig2	= dsig2;
		result->rho		= drho;

		result->D1		= div1;
		result->D2		= div2;
	
		result->K		= dK;
		result->T		= dT;
		result->SMax1	= dSMax1;
		result->SMax2	= dSMax2;

		result->type	= dtype;
	
		result->w1		= dw1;
		result->w2		= dw2;
	
		// Now assign the payoff function
		result->pay = BasketStrategy(dK, dtype, dw1, dw2);


		return result;

	}	
};

class PrototypeInstrumentFactory : public InstrumentFactory
{ // Returns a prototype object

public:

	TwoFactorOptionData* CreateOption() const
	{

		TwoFactorOptionData* result = new TwoFactorOptionData;

		// Results take from Topper 2005
		result->r		= 0.0;	// Percentage
		result->sig1	= 0.2;
		result->sig2	= 0.2;
		result->rho		= -0.9;

		result->D1		= 0.0;
		result->D2		= 0.0;
	
		result->K		= 4.0;
		result->T		= 2.5;
		//result->SMax1	= result->K * 2.0;
		//result->SMax2	= result->K * 2.0;

		result->SMax1	= 40.0;
		result->SMax2	= 40.0;

		result->type	= -1;	// Put, temp
	
		result->w1		= 1.0; // Topper
		result->w2		= 1.0;
	
		// Now assign the payoff function
		result->pay = BasketStrategy(result->K, result->type, result->w1, result->w2);


		return result;

	}	
};

#endif