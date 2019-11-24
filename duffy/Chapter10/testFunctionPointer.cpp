// testFunctionPointer.cpp
//
// Simple test program to show how to define and use
// function pointers. The functions are templated.
//
// (C) Datasim Education BV 2003-2005
//

#include <iostream.h>
#include "complex.hpp"

template <class V> V add(V x, V y)
{

	cout << "** Adding two numbers: " << x << ", " << y << endl;

	return x + y;

}

template <class V> V multiply(V x, V y)
{

	cout << "** Multiplying two numbers: " << x << ", " << y << endl;

	return x * y;

}

template <class V> V subtract(V x, V y)
{

	cout << "** Subtracting two numbers: " << x << ", " << y << endl;

	return x - y;

}

template <class V>
void genericFunction (V myX, V myY, V (*f) (V  x, V y))
{ // A function that delivers two variables myX and MyY to the function pointer 'f'
  // This is a potentially reusable function

	// Call the function with myX and myY
	V result = (*f)(myX, myY);

	cout << "Result is: " << result << endl;
}


int main()
{
	{
		double x = 3.0;
		double y = 2.0;

		genericFunction<double>(x, y, add);
		genericFunction<double>(x, y, multiply);
		genericFunction<double>(x, y, subtract);
	}

	Complex x(3.0, 2.0);
	Complex y(2.0, -4.9);

	genericFunction<Complex>(x, y, add);
	genericFunction<Complex>(x, y, multiply);
	genericFunction<Complex>(x, y, subtract);


	return 0;
}
