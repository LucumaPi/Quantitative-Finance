// PSetCreators.hpp
//
// The Abstract Factory for Simple Property sets
// Version 1
//
// (C) Datasim Education BV 2006
//

#include "SimplePropertySet.cpp"

#include <string>
#include <iostream>
using namespace std;

typedef SimplePropertySet<string, double> PSet;

class PSetFactory
{
public:
	virtual PSet* CreatePSet() const = 0;
};


class ConsolePSetFactory: public PSetFactory
{ // Create properties using cout/cin

public:
	PSet* CreatePSet() const
	{
		// Add key value pairs until finished

		string k; double v;

		cout << "Give name of property set: ";
		cin >> k;

		PSet* result = new PSet(k);

L1:
		cout << "Key name (EXIT): "; cin >> k; cout << endl;
		if (k == string("EXIT"))
		{
			return result;
		}

		cout << "Value: "; cin >> v; cout << endl;
		

		result->add(k, v);

		goto L1;

		return result;
	}
};