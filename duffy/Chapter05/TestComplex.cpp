// TestComplex.cpp
//
// Testing complex numbers
//

#include "complex.hpp"

int main()
{

	Complex z1(-23.0, 5.3);
	Complex z2(2.0, 3.0);

	Complex z3 = z1 * z2;
	Complex z4 = 2.0 * z4;
	Complex z5 = - z3;

	cout << z1;
	cout << z3;
	cout << z5; cout << "****\n";

	Complex z6 = z2 * 2.0;
	Complex z7 = 2.0 * z2;
	Complex z8 = z2 * 2.0;
	Complex z9= z6* z7;

	cout << z6;
	cout << z7;
	cout << z8;cout << "****\n";

	Complex z10 = z1.add(z2);
	cout << z10;

	Complex z0(1.0, 2.0);
	z4 = z3 = z1 = z0;
	cout << "Chain: " << z0 << z1 << z3 << z4;

	z4 += z1;	// Multiply z4 by z1 and modify it
	cout << z4;

	double real;
	double imaginary;
	cout << "Creating a complex number" << endl;
	cout << "Give real part: ";
	cin >> real;
	cout << "Give imaginary part: ";
	cin >> imaginary;

	// User-defined class and output for its objects
	Complex c(real, imaginary);
	cout << c;

	cout << "First: " << z1 << "Second: " << z2 << endl;
	
	Complex za = exp(Complex(0.0, 0.0));
	cout << za;

	Complex zs = sinh(za);
	Complex zc = cosh(za);

	cout << zs << zc;

	Complex c2(0.0, 0.0);
	cout << sinh(c2) << cosh(c2);

	return 0;
}