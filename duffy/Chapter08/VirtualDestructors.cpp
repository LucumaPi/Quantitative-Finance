// VirtualDestructors.cpp
//
// Showing use of virtual destructors.
//
// (C) Datasim Education BV 2005

#include <iostream>
using namespace std;

class B
{ // Class with non-virtual destructor
private:
		double* d;
public:
	B() { d = new double (1.0); }
	virtual ~B() { cout << "Base destructor\n"; delete d; }

};

class D : public B
{ // Derived class
private:
		int* iarr;
public:
	D(int N) : B() { iarr = new int[N]; }
	~D() { cout << "Derived destructor\n"; delete [] iarr; }
};


int main()
{
	{
		B* b = new D(10);
		delete b;
	}

	
	return 0;
}
