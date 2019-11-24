// Exception1.cpp
//
// Some simple examples of using the exception handling
// mechanism.
//
// (C) Datasim Education BV 2005.
//

#include <vector>
using namespace std;
#include <iostream>

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

template <class V> 
V sumReciprocals(const vector<V>& array) 
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
	vector<double> myArray (size, elementsValue);
	myArray[5] = 0.0;
	print(myArray);

	double answer = sumReciprocals(myArray);
	cout << "Sum of reciprocals: " << answer << endl;

	cout << "Which index change value to new value? ";
	int index;
	cin >> index;
	myArray[index] = 2.0;
	print(myArray);

	return 0;

}
