// Example1.cpp
//
// Showing usage of RTTI. In order for
// it to work, RTTI must encounter at least one
// virtual function in class hierarchy.
//
// AND AND DO NOT FORGET TO ENABLE RTTI IN THE PROJECT SETTINGS 
// /GR, FOR EXAMPLE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
// You can use this as a prototype example for your own classes.
//
// (C) Datasim Education BV 2005-2006
//

#include <iostream>
using namespace std;

#include <typeinfo>		// RTTI stuff here

class Base
{

public:
	Base() {} 
	virtual ~Base() {}

	virtual void print() const { cout << "I'm base\n"; }
	virtual double calculate(double d) const = 0;
	
	void doIt() { cout << "in base\n"; }

};

class D1: public Base
{

public:
	D1() {} 
	virtual ~D1() {}

	virtual void print() const { cout << "I'm a D1\n"; }
	virtual double calculate(double d) const { return 1.0 * d; }

};

class D2: public Base
{

public:
	D2() {} 
	virtual ~D2() {}

	virtual void print() const { cout << "I'm a D2\n"; }
	virtual double calculate(double d) const { return 2.0 * d; }

};


int main()
{

	// Part I: typeinfo

	D1 d1, d11;
	D2 d2;

	// Define a reference to type
	const type_info& myRef = typeid(d1);
	
	cout << "Human-readable name: " << myRef.name() << endl;

	// Test if two objects have same type or not
	if (typeid(d1) == typeid(d11))
	{
		cout << "Types are the same\n";
	}

	if (typeid(d1) != typeid(d2))
	{
		cout << "Types are NOT the same\n";
	}


	Base* b = &d1;
	const type_info& myRef2 = typeid(*b);

	cout << "Human-readable name: " << myRef2.name() << endl;


	// Create an array of Base class pointers
	int size = 10;
	Base* myArr[10];	// An array of pointers!

	for (int j = 0; j < 6; j++)
	{
		myArr[j] = &d1;
	}

	for (int k = 6; k < size; k++)
	{
		myArr[k] = &d2;
	}

	// Now 'filter' the real types. We have D1 and D2 types!
	int counterD1 = 0;
	int counterD2 = 0;

	for (int i = 0; i < size; i++)
	{
		if (typeid(*myArr[i]) == typeid(D1))
		{
			cout << "We have a D1\n"; counterD1++;
		}

		if (typeid(*myArr[i]) == typeid(D2))
		{
			cout << "We have a D2\n"; counterD2++;
		}

	}

	// Print final counts
	cout << "Number of D1s: " << counterD1 << endl;
	cout << "Number of D2s: " << counterD2 << endl;

	// Part II: dynamic casting

	D1 d1A;
	Base* base2 = &d1A;

	D1* d1Cast = dynamic_cast<D1*> (base2);

	if (d1Cast == 0)
	{
		cout << "Cast not possible:\n";
	}
	else
	{ // This function gets called

		cout << "Cast is possible: ";
		d1Cast -> print();
	}

	// Now cast a D1 to a D2 (not possible)
	D2* d2Cast = dynamic_cast<D2*> (base2);

	if (d2Cast == 0)
	{ // This function gets called

		cout << "Cast not possible:\n";
	}
	else
	{
		cout << "Cast is possible:\n";
		d2Cast -> print();
	}

	// Upcasting
	D1* dd = new D1;
	Base* b3 = dynamic_cast<Base*> (dd);

	if (b3 == 0)
	{ // This function gets called

		cout << "Cast not possible:\n";
	}
	else
	{
		cout << "Cast is possible:\n";
		b3 -> print();
		b3 -> doIt();
	}
	delete dd;

	// Static casting
	Base* bA = &d1;
	Base* bB = &d2;

	D1* dA = static_cast<D1*> (bA);

	// Unsafe static cast
	cout << "Unsafe cast ...\n";
	D1* dB = static_cast<D1*> (bB);
	dB -> print();

	// Const Cast
	cout << "\n const cast stuff\n";
	D1 dAny;
	const Base* bConst = &dAny;
	bConst -> print();
	// Base* bNonConst = bConst; DOES NOT WORK
	Base* bNonConst = const_cast<Base*> (bConst);
	bNonConst -> print();

	// The following conversions do not work
//	Base* bNonConst1 = static_cast<Base*> (bConst);
//	Base* bNonConst2 = dynamic_cast<Base*> (bConst);
//	Base* bNonConst3 = reinterpret_cast<Base*> (bConst);

	// Reinterpret Cast
	cout << "\nReinterpret cast stuff\n";

	D2 d2Any;
	Base* bb = reinterpret_cast<Base*>(&d2Any);
	bb -> print();

	return 0;
}
