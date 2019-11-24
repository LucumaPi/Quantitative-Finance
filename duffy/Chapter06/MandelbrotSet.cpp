// MandelbrotSet.cpp
//
// C++ program fo the Mandelbrot set. We use 
// the class Complex in combination with the STL
// vector container.
//
// We define a recursive process of the form
//
//		z -> z*z + c
//
// where z is a complex number and c is a given complex 
// number. We need an initial value for in order to start
// the iterative process. 
//
// Fatou studied this process in the field of complex analytic 
// dynamics. He showed that once a point moved to a distance 
// greater than 2 from the origin the orbit escapes to infinity.
//
// The sequence is:
//
//		z[0] = 0 // both coordinates
//		z[n+1] = z[n]^2 + c
//
// STATUS: ALPHA, you might need to do some experoimentation
//
// (C) Datasim Education BV 2005
//

#include "Complex.hpp" // My DJD complex class

#include <vector>
using namespace std;

// Useful proceduare for printing vector on Console
template <class V> void print(const vector<V>& v)
{

	cout << "\nARR:[";
	for (int j = 0; j < v.size(); j++)
	{
		cout << v[j] << ", ";
	
	}

	cout << "]";
}


// The Mandelbrot set in C++
vector<Complex> MandelbrotSet(const Complex& c, int N)
{
	vector<Complex> result(N+1);

	result[0] = Complex (0.0, 0.0);
	Complex tmp;

	for (int n = 1; n < result.size(); n++)
	{
		tmp = result[n-1];
		result[n] = (tmp*tmp) + c;
	}

	return result;
}


int main()
{
	Complex c(0.01, 0.01);
	int n = 200;

	vector<Complex> answer = MandelbrotSet(c, n);
	print(answer);

	return 0;
}
