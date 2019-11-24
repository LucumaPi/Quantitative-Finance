// Person.hpp
//
// 'Hello World' class. Function declarations.
//
// (C) Datasim Education BV 2005-2006
//

#ifndef Person_HPP
#define Person_HPP

#include "datasimdate.hpp"	// My dates and other useful stuff
#include <string>			// Standard string class in C++
using namespace std;

class Person
{
public: // Everything public, for convenience only

		// Data
		string nam;					// Name of person
		DatasimDate dob;			// Date of birth

		DatasimDate createdD;		// Internal, when object was created

public:
		Person (const string& name, const DatasimDate& DateofBirth);


		void print() const;
		
		int age() const;
		
};

#endif