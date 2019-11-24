// TestPSetCreators.cpp
//
// Test program for property set creators.
//
// V2: use auto_ptr
//
// (C) Datasim Education BV 1998-2006

#include "PSetCreators.hpp"
using namespace std;

void print(const SimplePropertySet<string,double>& pset)
{

	SimplePropertySet<string,double>::const_iterator it;
	
	cout << "\nPrinting Property Set\n";

	for (it= pset.Begin(); it!=pset.End(); it++)
	{ 
	
			cout << (*it).first << ", " << (*it).second << endl;
	}
}

PSetFactory* GetPSetFactory()
{

	// Only 1 factory in this version, like model T
	return new ConsolePSetFactory;
}

int main()
{

	PSetFactory* fac = GetPSetFactory();

	PSet* mySet = fac->CreatePSet();

	print (*mySet);

	delete fac;
	delete mySet;

	return 0;
}
