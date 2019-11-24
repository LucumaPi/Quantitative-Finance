// Exception2.cpp
//
// Some simple examples of using the exception handling
// mechanism. Now include the necessary keywords:
//
// (C) Datasim Education BV 2005.
//

#include <vector>
#include <string>
using namespace std;
#include <iostream>
#include <math.h>
#include "matherr.cpp"

// Useful proceduare for printing vector on Console
template <class V> void print(const vector<V>& v)
{

	cout << "\nARR:[";
	for (int j = 0; j < v.size(); j++)
	{
		cout << v[j] << ", ";
	
	}

	cout << "]" << endl;
}

template <class V> 
V sumReciprocals(const vector<V>& array) 
{ // Sum of reciprocals 
	
		V ans = V(0.0);
		for (int j = 0; j < array.size(); j++)
		{
			if (fabs(array[j] < 0.001)) // Magic number, for convenience
			{
				throw ZeroDivide("divide by zero","sumReciprocals", string());
			}

			ans += 1.0/array[j];
		}

		return ans;
} 

int main()
{
	int size = 10;
	double elementsValue = 3.1415;
	vector<double> myArray (size, elementsValue);
	myArray[5] = 0.0;
	print(myArray);

	// Now create a try/catch block
	try
	{
		double answer = sumReciprocals(myArray);
		cout << "Sum of reciprocals: " << answer << endl;
	}
	catch (ZeroDivide& exception)
	{
		exception.print();
	}

Lab1:	try
		{
			cout << "\nGive a new value for index number 5:";
			double val;
			cin >> val;
			myArray[5] = val;
			if (val == 999.0)
			{
				return 1; // Exit the program
			}

			double answer = sumReciprocals(myArray);
			cout << "Sum of reciprocals: " << answer << endl;
		}
		catch (ZeroDivide& exception)
		{
			exception.print();
			goto Lab1;
		}
	
	
		return 0;

}
