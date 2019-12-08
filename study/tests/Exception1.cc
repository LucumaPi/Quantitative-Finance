// Exception1.cpp
//
// Some simple examples of using the exception handling
// mechanism.
//
// (C) Datasim Education BV 2005.
//

#include <iostream>
#include <vector>

// Useful proceduare for printing vector on Console
template <class V> void print(const std::vector<V>& v)
{

	std::cout << "\nARR:[";
	for (int j = 0; j < v.size(); j++)
	{
		std::cout << v[j] << ", ";
	
	}

	std::cout << "]";
}

template <class V> 
V sumReciprocals(const std::vector<V>& array) 
{ // Sum of reciprocals 
	
		V ans = V(0.0);
		for (int j = 0; j < array.size(); j++)
		{
			ans += 1.0/array[j];
		}

		return ans;
} 

int main()
{
	int size = 10;
	double elementsValue = 3.1415;
	std::vector<double> myArray (size, elementsValue);
	myArray[5] = 0.0;
	print(myArray);

	double answer = sumReciprocals(myArray);
	std::cout << "Sum of reciprocals: " << answer << std::endl;

	std::cout << "Which index change value to new value? ";
	int index;
	std::cin >> index;
	myArray[index] = 2.0;
	print(myArray);

	return 0;

}