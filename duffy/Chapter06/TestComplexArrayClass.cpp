// TestComplexArrayClass.cpp
//
// Testing complex numbers. Focus is on arrays
// and usage with functions with complex arguments.
//
// In this case we are using the Complex Array class.
//
// (C) Datasim Education BV 2005-2006
//

#include "ComplexArray.hpp"

Complex myFunc(const Complex& z)
{ // Single valued function of a complex variable

	return z * z;
}

Complex ComplexProduct(const ComplexArray& carr, int n)
{ // Complex function of several complex variables

	Complex product = carr[carr.MinIndex()];

	for (int j = carr.MinIndex() + 1; j <= carr.MaxIndex(); j++)
	{
		product *= carr[j];
	}

	return product;

}

Complex ComplexSum(const ComplexArray& carr, int n)
{ // Complex function of several complex variables

	Complex sum = carr[carr.MinIndex()];

	for (int j = carr.MinIndex() + 1; j <= carr.MaxIndex(); j++)
	{
		sum += carr[j];
	}

	return sum;

}


int main()
{

	Complex z1(1.0, 1.0);
	Complex z2(2.0, 3.0);

	Complex z3 = z1 * z2;
	Complex z4 = 2.0 * z3;
	Complex z5 = - z3;

	// Create a dynamic list of Complex numbers
	int Size = 5;
	ComplexArray cpArray (Size);
	cpArray[0] = z1;
	cpArray[1] = z2;
	cpArray[2] = z3;
	cpArray[3] = z4;
	cpArray[4] = z5;

	// Another complex array
	ComplexArray fixedArray(5);
	for (int i = fixedArray.MinIndex(); i <= fixedArray.MaxIndex(); i++)
	{
		fixedArray[i] = Complex ((double) i, 0.0);

	}

	// Call function and print values for each z
	for (int j = 0; j < Size; j++)
	{
		cout << myFunc(cpArray[j]) << ", ";

	}

	// Now work with functions of several complex variables
	Complex product = ComplexProduct(fixedArray, Size);
	cout << "Product: " << product << endl;

	Complex sum = ComplexSum(fixedArray, Size);
	cout << "Sum: " << sum << endl;


	return 0;
}