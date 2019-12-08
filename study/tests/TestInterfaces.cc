// TestInterfaces.cpp
//
// Simulating interfaces in C++
//
// (C) Datasim Education BV 2005-2006

#include <duffy/MathsInterfaces.hh>
#include <iostream>

class SimpleArray : IOneDimensionalAccess<double> // Index == int
{
private:
		double first;
		double second;

public:
	SimpleArray() { first = 1.0; second = 2.71;}

	double& operator [] (int index)
	{
		if (1 == index) return first;
		if (2 == index) return second;
	}

};

int main()
{

	SimpleArray myArr;

	std::cout << myArr[1] << ", " << myArr[2] << std::endl;

	return 0;
}