// Main.cpp
//
// Test program for the array class.
//
// (C) Datasim Education BV  1995-2003

#include <iostream>

#include "Array.cpp"

using namespace std;


template<class Type, int def_size>
void PrintArray(const Array<Type, def_size>& a)
{
	for (int i=0; i<a.Size(); i++)
	{
		cout<<a[i]<<", ";
	}
	cout<<endl;
}


void main()
{
	Array<int, 10> a;
	Array<double, 10> b;

	// Fill Arrays
	for (int i=0; i<10; i++) 
	{
		a[i]=i;
		b[i]=1.1*i;
	}

	// Print array2
	PrintArray(a);
	PrintArray(b);

}