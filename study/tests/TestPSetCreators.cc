// TestPSetCreators.cpp
//
// Test program for property set creators.
//
// V2: use auto_ptr
//
// (C) Datasim Education BV 1998-2006

#include <duffy/PSetCreators.hh>

void print(const SimplePropertySet<std::string,double>& pset)
{

	SimplePropertySet<std::string,double>::const_iterator it;
	
	std::cout << "\nPrinting Property Set\n";

	for (it= pset.Begin(); it!=pset.End(); it++)
	{ 
	
			std::cout << (*it).first << ", " << (*it).second << std::endl;
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