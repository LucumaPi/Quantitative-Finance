// Delegation.cpp
//
// Show use of Composition and Delegation
//
// (C) Datasim Education BV 2005-2006

#include <iostream>
using namespace std;

class B
{ // Base class for Delegation
private:
		
public:
	B() {}
	virtual double getValue() = 0;
	virtual ~B() { }

};

class D : public B
{ // Derived class
private:
		int* iarr;
		int size;
public:
	D(int N) : B() 
	{ 
		size = N;
		iarr = new int[size];
		for (int j = 0; j < N; j++)
		{
			iarr[j] = double(N-j);
		}
	}

	double getValue() {return iarr[0]/double(size);}
	~D() { delete [] iarr; }
};

class Client
{
private:
		B* b;
public:
	Client(B& delegate) { b = &delegate; }

	// The function that delegates
	double clientValue() const
	{
		double tmp = b -> getValue();

		// Modify for current situation
		return tmp * 100.0;
	}
};

int main()
{
	int arraySize = 10;
	D myDerived(arraySize);
	
	Client myClient(myDerived);

	cout << "Client value: " << myClient.clientValue() << endl;

	return 0;
}
