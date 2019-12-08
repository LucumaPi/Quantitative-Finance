// PSetCreators.hpp
//
// The Abstract Factory for Simple Property sets
// Version 1
//
// (C) Datasim Education BV 2006
//

#include "SimplePropertySet.hh"

#include <iostream>
#include <string>

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

		std::cout << "Give name of property set: ";
		std::cin >> k;

		PSet* result = new PSet(k);

L1:
		std::cout << "Key name (EXIT): "; std::cin >> k; std::cout << endl;
		if (k == string("EXIT"))
		{
			return result;
		}

		std::cout << "Value: "; std::cin >> v; std::cout << std::endl;
		

		result->add(k, v);

		goto L1;

		return result;
	}
};