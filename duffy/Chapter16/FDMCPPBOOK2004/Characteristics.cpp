// Characteristics.cpp
//
// (C) Datasim Education BV 2006
//

#include "Characteristics.hpp"


double sigma(const pair<double,double>& state)
{ return 0.5*vol*vol*state.first*state.first; }


// Topper section 3.1.4 page 11: Non-constant volatility
double sigma_linear(const pair<double,double>& state)
{
	const double a=0.129;
	const double b=0.177;
	
	const double t = state.second;
	const double S = state.first;

	const double s = b+a*t;
	return 0.5*vol*vol*S*S;
}

double mu(const pair<double,double>& state)
{ return (r-d)*state.first; }

double forcing(const pair<double,double>& state)
{ return f; }

double b(const pair<double,double>& state)
{ return -r; }

// initial condition for call
double IC(const double& S)
{ 
	if (S > Strike)
		return (S - Strike); 
	else
		return 0.0; 
}

// initial condition for put
double IC_put(const double& S)
{ 

//	cout << "put" << K << ", " << s;
	if (Strike > S)
		return (Strike - S); 
	else
		return 0.0;
}	

// Topper section 3.2.1 page 12: Power options
double IC_PO(const double& S)
{ return (pow(S,p) > Strike) ? pow(S,p) - Strike : 0; }

//Topper section 3.2.2 page 13: Capped Power options
double IC_ASCPO(const double & S)
{
	const double result = (pow(S,p)> Strike) ? pow(S,p)-Strike : 0;
	
	return (result<bcr) ? result : bcr;
	
}

//Topper section 3.2.2 page 14: Symmetric Capped Power options
double IC_SCPO(const double & S)
{
	const double result = (S-Strike>0) ? pow(S-Strike,p) : 0;
	
	return (result<bcr) ? result : bcr;
	
}

double BCR(const double& t)
{ return bcr; }

// Topper section 3.2.1 page 12: Power Options
double BCR_PO(const double& t)
{
	return pow(Xto,p)-Strike*exp(-(r-d)*(t - Yfrom));
}

double BCL(const double& t)
{ return bcl; }

double BCL_put(const double& t)
{
//	return Strike*::exp(-(r-d)*(Yto - t)); // DD 
	return Strike*(::exp(-(r-d)*(t)));
//	return Strike;
}

// Topper page 11: non-constant volatility boundary condition
double BCR_Topper_p11(const double & t)
{
	return Xto - Strike*exp(-(r-d)*(t - Yfrom));

}

double BCR_Topper_p10(const double & t)
{	// Topper page 10: discontinuous jumps in rebate

	double result = 1;
	int i = 1;
	while( t*12 > i ){
	 result *= 2;
	 i++;
	}
	
	return result;
}