// testvalarray.cpp
//
// Show some of the functionality of the STL
// 'valarray'. This is a dynamic maths vector class.
//

#include <iostream> // I/O stuff
#include <valarray> // Reusable vector class

template <class T> std::valarray<T> multiply(const std::valarray<T>& vec1, const T& factor)
{ // Multiply a vector by a scalar factor

	std::valarray<T> result (vec1.size()); // Same size

	for (int j = 0; j < result.size(); j++)
	{
		result[j] = vec1[j] * factor;
	}

	return result;
}

// Usually work with doubles, define handy alias
typedef std::valarray<double> DoubleArray;

int main()
{
	int N;
	std::cout << "Give size: ";
	std::cin >> N;
	
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
		std::cout << outputArray[i] << ", ";
	}

	return 0;
}