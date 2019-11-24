// testvalarray.cpp
//
// Show some of the functionality of the STL
// 'valarray'. This is a dynamic maths vector class.
//

#include <valarray> // Reusable vector class
#include <iostream> // I/O stuff
using namespace std; // STL namespace, STANDARD C++

template <class T> valarray<T> multiply(const valarray<T>& vec1, const T& factor)
{ // Multiply a vector by a scalar factor

	valarray<T> result (vec1.size()); // Same size

	for (int j = 0; j < result.size(); j++)
	{
		result[j] = vec1[j] * factor;
	}

	return result;
}

// Usually work with doubles, define handy alias
typedef valarray<double> DoubleArray;

int main()
{
	int N;
	cout << "Give size: ";
	cin >> N;
	
	double factor = 0.5;

	DoubleArray inputArray(N);

	// Initialisation of input array
	for (int j = 0; j < inputArray.size(); j++)
	{
		inputArray[j] = double (j+1);		// Simple values
	}
	DoubleArray outputArray = multiply(inputArray, factor);

	for (int i = 0; i < outputArray.size(); i++)
	{
		cout << outputArray[i] << ", ";
	}

	return 0;
}