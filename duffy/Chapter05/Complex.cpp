// complex.cpp
//
// Code file for the class of complex numbers in two dimensional
// geometry.
//
// Last modification dates:
//
// 1993-6-27: DD new functions added, mainly member functions changed to
//	      global functions and many new special functions (e.g. arc*. sqrt
//	      sinh, ...). Also operators + and - for doubles.
// 1993-7-2: DD Substantial coding and additions
// 1993-11-11: EB initial code, name is now Complex
// 1993-11-11: EB function operator = (double d) added
// 1993-11-23: EB function /(Complex) , / (double), operator  ==, degenerate modified.
// 1993-11-26: EB functions operator >, operator < added.
// 2005-2-5 DD new lease of life
// 2005-11-30 DD added sech(z) to be tested by muniangel :)
// 2006-7-7 DD constructor com(double) added
//
// (C) Copyright Datasim Education BV 1992-2006
//
// The information contained in this file is property of Datasim Education BV Amsterdam Nederland.
// The information contained herein is subject to change without notice. No part
// of this information may be reproduced or transmitted in any form or by any means,
// electronic or mechanical, for any purpose, without the express written permission
// of Datasim BV.

#include "complex.hpp"
#include <math.h>

Complex mpi(const Complex& z)
{ // Multiply z by i == sqrt(-1)

	return Complex(-z.y, z.x);
}

Complex::Complex()
{ // Default constructor

	x = 1.0;
	y = 0.0;
}

Complex::Complex(const Complex &p)
{ // Copy initialisor

	x = p.x;
	y = p.y;
}

Complex::Complex(double real)
{
	x = real;
	y = 0.0;
}

Complex::Complex(double dx, double dy)
{
	x = dx;
	y = dy;
}

Complex::~Complex()
{

}

Complex& Complex::operator = (const Complex& c)
{
	// Avoid doing assign to myself
	if (this == &c)
		return *this;

	x = c.x;
	y = c.y;

	return *this;
}

Complex& Complex::operator += (const Complex& c)
{
		x += c.x;
		y += c.y;

		return *this;
}

Complex& Complex::operator -= (const Complex& c)
{
		x -= c.x;
		y -= c.y;

		return *this;
}

Complex& Complex::operator /= (const Complex& c)
{

		Complex tmp = (*this) / c;
		*this = tmp;

		return *this;
}

Complex& Complex::operator *= (const Complex& c)
{

	Complex tmp = (*this) * c;
	*this = tmp;

	return *this;

}


double Complex::xVal() const
{

	return x;
}

double Complex::yVal() const
{

	return y;
}

double real(const Complex& c)
{
	return c.x;
}

double imag(const Complex& c)
{
	return c.y;
}


double rad(const Complex& c)
{ // Distance from origin

	double res = ::sqrt((c.x*c.x) + (c.y*c.y));
	return res;
}

double modulus(const Complex& c)
{ // Distance from the origin (Same as the rad() function)

	return rad(c);
}

double abs(const Complex& c)
{ // Absolute value of the complex number

	return rad(c);
}

// Functionality
double Complex::distance (const Complex& c2)
{ // Euclidean distance

	return ::sqrt((x-c2.x)*(x-c2.x) + (y-c2.y)*(y-c2.y));
}


// Member operator overloading
Complex Complex::operator - () const
{ // The additive inverse of the current complex number

	return Complex(- x, - y);
}

Complex Complex::add(const Complex& c2) const
{ // Add two complex numbers

	Complex result;
	result.x = x + c2.x;
	result.y = y + c2.y;

	return result;
}

Complex Complex::operator + (const Complex& c2) const
{ // Add two complex numbers

	return Complex(x + c2.x, y + c2.y);
}
Complex Complex::operator - (const Complex& c2) const
{ // Subtract two complex numbers

	return Complex(x - c2.x, y - c2.y);
}

Complex Complex::operator * (const Complex& c2) const
{ // Multiply two complex numbers

	return Complex((x * c2.x) - (y * c2.y),
		       (x * c2.y) + (y * c2.x));
}

Complex Complex::operator / (const Complex& c2) const
{ // Division of complex numbers

	Complex res;
	double r = modulus(c2);
	double d = r * r;
	Complex tmp1 = conjugate(c2);
	Complex tmp2 = tmp1 * (*this);
	res =tmp2/d;
	
	return res;
}

Complex Complex::operator / (double d) const
{ // Division of the complex number by a double

	return Complex(x / d, y / d);
}

// Global operator overloading
Complex operator * (const Complex& c, double d)
{ // Scaling by a double

	return Complex(c.x * d, c.y * d);
}

Complex operator * (double d, const Complex& c)
{ // Scaling by a double

	// Reuse already made operator
	return c * d;
}
/*
Complex operator + (const Complex& c, double d)
{
	return Complex(c.x + d, c.y);
}

Complex operator + (double d, const Complex& c)
{
	return c + d;
}
*/
Complex operator - (const Complex& c, double d)
{
	return Complex(c.x - d, c.y);
}

Complex operator - (double d, const Complex& c)
{
	return Complex(d - c.x, -c.y);
}


// Other functions
Complex conjugate(const Complex& z)
{ // The complex conjugate of a complex number

	return Complex(z.x, -z.y);
}

Complex inverse(const Complex& z)
{ // The multiplicative inverse of the complex number
	// X + iY --> 1.0 /(X + iY)

	return Complex(1.0,0.0) / z;
}


// Complex trigonometric functions
Complex exp(const Complex& c)
{ // Exponential function

	double ex = exp(c.x);
	return Complex(ex * cos(c.y), ex * sin(c.y));
}


Complex cos(const Complex& z)
{ // Cosine function

	Complex term1 = exp(mpi(z));
	Complex term2 = exp(- mpi(z));

	Complex result = 0.5 * (term1 + term2);

	return result;
}

Complex sin(const Complex& z)
{ // Sine function

	Complex term1 = exp(mpi(z));
	Complex term2 = exp(- mpi(z));

	Complex result = - 0.5 * mpi(term1 - term2);

	return result;
}

Complex cosh(const Complex& z)
{ // Hyperbolic cosine function

	return (exp(z)  + exp(- (z))) * 0.5;

}

Complex sinh(const Complex& z)
{ // Hyperbolic sine function

	return (exp(z) - exp(- (z))) * 0.5;

}

Complex tanh(const Complex& z)
{ // Hyperbolc tangent

	return sinh(z) / cosh(z);
}

Complex sech(const Complex& z)
{ // Hyperbolc cotangent

	return Complex (2.0, 0.0)/(exp(z) + exp(-z));

}

Complex csch(const Complex& z)
{ // Hyperbolc cosech

	return Complex (2.0, 0.0)/(exp(z) - exp(-z));

}

Complex coth(const Complex& z)
{ // Hyperbolc cotangent

	return cosh(z) / sinh(z);

}


Complex tan(const Complex& c)
{ // The tangent function

	return sin(c) / cos(c);
}

Complex cgt(const Complex& c)
{ // The cotangent function

	return cos(c) / sin(c);
}


ostream& operator << (ostream& os, const Complex& cmp)
{ // Print the complex number

	os << "[" << cmp.x << ", " << cmp.y << "]\n";
	return os;
}
