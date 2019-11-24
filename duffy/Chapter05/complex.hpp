// complex.hpp
//
// Class of complex number in two-dimensional space.
//
// (C) Copyright Datasim Education BV 1992-2005
//
// The information contained in this file is property of Datasim BV Amsterdam Nederland.
// The information contained herein is subject to change without notice. No part
// of this information may be reproduced or transmitted in any form or by any means,
// electronic or mechanical, for any purpose, without the express written permission
// of Datasim BV.

#ifndef COMPLEX_HXX
#define COMPLEX_HXX

#include <iostream>
using namespace std;

class Complex
{
private:

	double x, y;

	friend Complex mpi(const Complex& z);	   // Multiply z by i == sqrt(-1)
public:
       // Constructors
       Complex();							// Default constructor
	   Complex(double real);				// Special case is real numbers
       Complex(double real, double imag);	// Cartesian form
       Complex(const Complex& p);
	   virtual ~Complex();

       // Accessing functions
       double xVal() const;
       double yVal() const;
       friend double real(const Complex& c);		   // Real part of number
       friend double imag(const Complex& c);		   // Imaginary part of number
       friend double rad(const Complex& c);     	   // Distance from origin
       friend double modulus(const Complex& c); 	   // Distance from the origin
       friend double abs(const Complex& c);			   // Absolute value of complex number

       // Member operator overloading
       Complex  operator - () const;
       Complex& operator =  (const Complex& c);
       Complex& operator += (const Complex& c);
       Complex& operator *= (const Complex& c);
       Complex& operator -= (const Complex& c);
       Complex& operator /= (const Complex& c);
       Complex  add	(const Complex& c2) const;
	   Complex  operator +  (const Complex& c2) const;
       Complex  operator -  (const Complex& c2) const;
       Complex  operator *  (const Complex& c2) const;
       Complex  operator /  (const Complex& c2) const;
       Complex  operator /  (double d)          const;

	   // Functionality
	   double distance (const Complex& c2);	// Euclidean distance

       // Global operator overloading
	   friend Complex operator * (const Complex& c, double d);
       friend Complex operator * (double d, const Complex& c);
//	   friend Complex operator + (const Complex& c, double d);
//      friend Complex operator + (double d, const Complex& c);
       friend Complex operator - (const Complex& c, double d);
       friend Complex operator - (double d, const Complex& c);

       // Other functions
       friend Complex conjugate(const Complex& c);	   // X + iY --> X - iY
       friend Complex inverse(const Complex& c);	   // X + iY --> 1.0 /(X + iY)
    
       // Complex trigonometric functions
       friend Complex exp(const Complex& c);           // Exponential function
       friend Complex cos(const Complex& c);           // Cosine function
       friend Complex sin(const Complex& c);           // Sine function
       friend Complex cosh(const Complex& c); 	   // Hyperbolic cosine function
       friend Complex sinh(const Complex& c); 	   // Hyperbolic sine function
       friend Complex tanh(const Complex& c);          // Hyperbolic tangent
	   friend Complex sech(const Complex& c);        // Hyperbolic secant
       friend Complex csch(const Complex& c);      
       friend Complex coth(const Complex& c);        // Hyperbolic cotangent
	   friend Complex tan(const Complex& c);	   // The tangent function
       friend Complex cgt(const Complex& c);	   // The cotangent function

       friend ostream& operator << (ostream& os, const Complex& cmp);

};

#endif   // Complex_HXX
