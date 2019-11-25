// TestComplex.cpp
//
// Testing complex numbers
//

#include "Complex.hpp"

int main()
{

	Complex z1(-23.0, 5.3);
	Complex z2(2.0, 3.0);

	Complex z3 = z1 * z2;
	Complex z4 = 2.0 * z4;
	Complex z5 = - z3;

	std::cout << z1;
	std::cout << z3;
	std::cout << z5; std::cout << "****\n";

	Complex z6 = z2 * 2.0;
	Complex z7 = 2.0 * z2;
	Complex z8 = z2 * 2.0;
	Complex z9= z6* z7;

	std::cout << z6;
	std::cout << z7;
	std::cout << z8; std::cout << "****\n";

	Complex z10 = z1.add(z2);
	std::cout << z10;

	Complex z0(1.0, 2.0);
	z4 = z3 = z1 = z0;
	std::cout << "Chain: " << z0 << z1 << z3 << z4;

	z4 += z1;	// Multiply z4 by z1 and modify it
	std::cout << z4;

	double real;
	double imaginary;
	std::cout << "Creating a complex number" << std::endl;
	std::cout << "Give real part: ";
	std::cin >> real;
	std::cout << "Give imaginary part: ";
	std::cin >> imaginary;

	// User-defined class and output for its objects
	Complex c(real, imaginary);
	std::cout << c;

	std::cout << "First: " << z1 << "Second: " << z2 << std::endl;
	
	Complex za = exp(Complex(0.0, 0.0));
	std::cout << za;

	Complex zs = sinh(za);
	Complex zc = cosh(za);

	std::cout << zs << zc;

	Complex c2(0.0, 0.0);
	std::cout << sinh(c2) << cosh(c2);

	return 0;
}