// TestComplexArray.cpp
//
// Testing complex numbers. Focus is on arrays
// and usage with functions with complex arguments.
//
// (C) Datasim Education BV 2005
//

#include <duffy/Complex.hh>

Complex myFunc(const Complex& z)
{ // Single valued function of a complex variable

	return z * z;
}

Complex ComplexProduct(Complex* carr, int n)
{ // Complex function of several complex variables

	Complex product = carr[0];

	for (int j = 1; j < n; j++)
	{
		product *= carr[j];
	}

	return product;

}

Complex ComplexSum(Complex* carr, int n)
{ // Complex function of several complex variables

	Complex sum = carr[0];

	for (int j = 1; j < n; j++)
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
//	Complex z4 = 2.0 * z4; ?? compiles
	Complex z4 = 2.0 * z3;
	Complex z5 = - z3;

	// Create a dynamic list of Complex numbers
	int Size = 5;
	Complex* cpArray = new Complex[Size];
	cpArray[0] = z1;
	cpArray[1] = z2;
	cpArray[2] = z3;
	cpArray[3] = z4;
	cpArray[4] = z5;

	// Now define an array on the stack
	Complex fixedArray[5]; // The constant '5' is mandatory
	for (int i = 0; i < Size; i++)
	{
		fixedArray[i] = Complex ((double) i, 0.0);

	}

	// Call function and print values for each z
	for (int j = 0; j < Size; j++)
	{
		std::cout << myFunc(cpArray[j]) << ", ";

	}

	// Now work with functions of several complex variables
	Complex product = ComplexProduct(fixedArray, Size);
	std::cout << "Product: " << product << std::endl;

	Complex sum = ComplexSum(fixedArray, Size);
	std::cout << "Sum: " << sum << std::endl;

	delete [] cpArray;

	return 0;
}