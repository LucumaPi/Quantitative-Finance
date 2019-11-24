// characteristics.hpp
//
// this file contains functions that can be used as function pointers
// as input for parabolicPDE and parabolicFDM. The current functions
// allow plain vanilla call and put options, power options,
// capped power options, single barrier options (with rebates) and
// double barrier options (with rebates). The barriers are
// up-and-out and down-and-out calls and puts.
//


#ifndef CHAR_HPP
#define CHAR_HPP


#include <map>
#include <iostream>
#include <math.h>
using namespace std;

const double p = 1; // power factor for Power Options, Topper section 3.2.1 page 12

const double r = 0.06;		 // interest rate
const double d = 0.00;	 // dividend
const double vol = 0.20;	 // volatility
const double f = 0;      // forcing term
const double Strike = 95.0;   // strike price
const double bcl = 0;    // constant value of left boundary condition
const double bcr = 360; // constant value of right boundary condition Call

const double Xfrom = 0;	 // minimum value of stock-price domain
const double Xto = 4.0*Strike; // maximum value of stock-price domain
const double Yfrom = 0;  // initial time
const double Yto = 0.5;  // final time
const long XINTERVALS = 120;  // number of intervals in stock-price discretization
const long YINTERVALS = 100;  // number of time-intervals

// THETA = 0 fully explicit, = 1 fully implicit
//double THETA =0.0;// denotes extent to explicit versus implicit

double sigma(const pair<double,double>& state);		// volatility
double mu(const pair<double,double>& state);      // drift
double forcing(const pair<double,double>& state); // forcing term
double b(const pair<double,double>& state);       // free term
double IC(const double& S);                       // initial condition for a call
double IC_put(const double& S);                   // initial condition for a put
double BCR(const double& t);                      // right boundary condition (returns bcr)
double BCL(const double& t);                      // left boundary condition (returns bcl)
double BCL_put(const double& t);                  // right boundary condition for a put
double BCR_Topper_p10(const double & t);          // special right boundary condition
double BCR_Topper_p11(const double & t);          // special right boundary condition
double sigma_linear(const pair<double,double>& state); // volatility = b+a*t
double IC_PO(const double& S);      // power options: initial condition
double IC_ASCPO(const double & S);  // asymmetric capped power options: initial condition
double IC_SCPO(const double & S);   // symmetric capped power options: initial condition
double BCR_PO(const double& t);     // power options: boundary condition

#endif