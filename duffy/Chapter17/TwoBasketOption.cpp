// TwoBasketOption.cpp
//
// Modelling PDE as C++ classes. This is a model in 2 space
// dimensions where we assume that Dirichlet boundary conditions are in 
// force.
// 
// This is the two-factor Black Scholes implementaton (basket).
//
// In a component environment (e.g. C#) we could define intefaces and 
// abstract base classes.
//
// Last Modification:
//
//	2005-12-12 DD Initial code
//	2006-1-17 DD Now for a Two Basket Option
//	2006-2-1 DD modified cost of carry for dividends
//	2006-2-2 DD bug fixes
//	2006-2-10 DD inline functions now
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef TwoBasketOption_CPP
#define TwoBasketOption_CPP

#include "TwoBasketOption.hpp"	// Template class

void TwoBasketOption::init()
{
	/* Recall: Data members of opt
	double r;				// Interest rate
	double D1, D2;			// Dividends
	double sig1, sig2;		// Volatility
	double rho;				// Cross correlation
	double K;				// Strike price, now place in IC
	double T;				// Expiry date
	double SMax1, SMax2;	// Far field condition
	double w1, w2;
	int type;				// Call +1 or put -1 */

	// N.B. Zero dividend!!!!

	leftOption = downOption = BasicOption();

	// Create the 1-factor option object when S1 = 0
	leftOption.r = opt.r;		// Interest rate
	leftOption.sig = opt.sig2;		// Volatility
	leftOption.K = (opt.K) / (opt.w1);		// Strike price
	leftOption.T = opt.T;		// Expiry date
	leftOption.b = opt.r - opt.D2;		// Cost of carry, stock BS model Merton 1973
	leftOption.otyp = string("P");	// Option name (call, put)

	leftOption.dumpPrint();

	// Create the 1-factor option object when S2 = 0
	downOption.r = opt.r;		// Interest rate
	downOption.sig = opt.sig1;		// Volatility
	downOption.K = (opt.K) / (opt.w2);		// Strike price
	downOption.T = opt.T;		// Expiry date
	downOption.b = opt.r - opt.D1;		// Cost of carry, stock BS model Merton 1973
	downOption.otyp = string("P");	// Option name (call, put)

	downOption.dumpPrint();
}

TwoBasketOption::TwoBasketOption()
{
	opt = TwoFactorOptionData();

	leftOption = downOption = BasicOption();

	init();
}


TwoBasketOption::TwoBasketOption (const Range<double>& S1range, const Range<double>& S2range, 
		const Range<double>& trange, const TwoFactorOptionData& data) : IBVP(S1range, S2range, trange)
{
	opt = data;
	init();
}

// Selector functions// Coefficients of parabolic second order operator
inline double TwoBasketOption::diffusion1(double S1, double S2, double t) const
{

	double s = opt.sig1;
	return 0.5 * s * s * S1 * S1;

} // Coefficient of second derivative

inline double TwoBasketOption::diffusion2(double S1, double S2, double t) const 
{   
	
	double s = opt.sig2;
	return 0.5 * s * s * S1 * S2;

} // Coefficient of second derivative


 inline double TwoBasketOption::convection1(double S1, double S2, double t) const 
 {    
		return ((opt.r) - (opt.D1)) * S1;

 }	// Coefficient of first derivative


 inline double TwoBasketOption::convection2(double S1, double S2, double t) const 
 {    
	 return ((opt.r) - (opt.D2)) * S2;
 
 }	// Coefficient of first derivative

 inline double TwoBasketOption::crossTerm(double S1, double S2, double t) const 
 {    
		return (opt.rho) * (opt.sig1) * (opt.sig2) * S1 * S2;

 }	// Mixed derivative term

 inline double TwoBasketOption::zeroTerm(double S1, double S2, double t) const 
 {    
		return - (opt.r);

 }	// Coefficient of zero derivative

 inline double TwoBasketOption::RHS(double S1, double S2, double t) const 
 {    
		return 0.0;
 }			// Inhomogeneous forcing term

// Boundary and initial conditions
 inline double TwoBasketOption::BCLeft(double S2, double t) 
 {   // Left hand boundary condition


		// Solution of put Euro g(S2, K/w1, t). This code is on the CD

	// leftOption.T = t;
	leftOption.T = opt.T - t;
	
	return leftOption.Price(S2);

 }
 
 inline double TwoBasketOption::BCRight(double S2, double t) 
 {	// Right hand boundary condition

	 return 0.0; // Put

	 // For a call it will be different
 }

 inline double TwoBasketOption::BCUnder(double S1, double t) 
 { // Lower S2 = 0 boundary condition

		// Solution of put Euro g(S1, K/w2, t)

	//	downOption.T = t;
		downOption.T = opt.T - t;
		return downOption.Price(S1);

 }


 inline double TwoBasketOption::BCUpper(double S2, double t) 
 { // Upper hand boundary condition

	 return 0.0; // Put
		
	 // For a call it will be different

 }


 inline double TwoBasketOption::IC(double S1, double S2) const 
 {    // Initial condition
 
	 // Severe information hiding and that's good

	 return opt.payoff(S1, S2);
 }				

#endif