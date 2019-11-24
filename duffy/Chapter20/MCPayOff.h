//
//
//      MCPayOff.h
//
// Standard C++ class hierarchy for 1-factor optioms. It is
// similar to one of the approaches in chapter 8. At the moment
// we have support for call options.
//
// This class is in fact a Strategy for the underlyings in this chapter,
// in particular Asian options and Up/Out options.
//
//
// Each class has a polymorphic clone function (Prototype fucntion)
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#ifndef MCPAYOFF_H
#define MCPAYOFF_H

class PayOff
{
public:

    PayOff(){};

    virtual double operator()(double Spot) const=0;
    virtual ~PayOff(){}
    virtual PayOff* clone() const=0;

private:
    
};

//// Call option payoff
class PayOffCall : public PayOff
{
public:

    PayOffCall(double Strike_);

    virtual double operator()(double Spot) const;
    virtual ~PayOffCall(){}
    virtual PayOff* clone() const;

private:

    double Strike;

};

//// Put option payoff
class PayOffPut : public PayOff
{
public:

    PayOffPut(double Strike_);

    virtual double operator()(double Spot) const;
    virtual ~PayOffPut(){}
    virtual PayOff* clone() const;

private:

    double Strike;

};


/// Version 2
//Example of OptionPayOff class based on Datasim Option Template
/*
template <class ValueType, class OptionType> class OptionPayOff
{
private:
	ValueType r;   //Interest Rate
	ValueType K;   //Strike
	ValueType T;   //Maturity
	ValueType S0;  //Spot Price of Underlying
	ValueType sig; //Volatility

public:
	OptionType opttype; //Type: Call or Put

	//Constructors
	OptionPayOff();  //DefaultConstructor
	OptionPayOff(const ValueType& r_,
				 const ValueType& K_,
				 const ValueType& T_,
				 const ValueType& S0_,
				 const ValueType& sig_,
				 const OptionType& opttype_);
	
	//Destructors
	virtual ~OptionPayOff();

	//Copy
    OptionPayOff(const OptionPayOff<ValueType, OptionType>& OptionPayOff2);   //CopyConstructor
	
	//Accessing Functions
	ValueType Price() const;			//Gives OptionPrice 
	ValueType GetInterestRate() const;	//Gives InterestRate
	ValueType GetStrike() const;		//Gives Strike
	ValueType GetMaturity() const;		//Gives Maturity
	ValueType GetSpotPrice() const;		//Gives SpotPrice
	ValueType GetVolatility() const;	//Gives used Volatility

	//OperatorOverloading
	virtual ValueType operator()(ValueType K_) const;
};*/

#endif