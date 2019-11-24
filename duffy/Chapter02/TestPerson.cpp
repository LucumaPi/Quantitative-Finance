// TestPerson.cpp
//
// 'Hello World' Testing the first C++ class
//
// (C) Datasim Education BV 2005-2006
//


#include "datasimdate.hpp"	// Dates and other useful stuff
#include "Person.hpp"		// Interface functions for Person
#include <string>			// Standard string class in C++
using namespace std;

int main()
{

	DatasimDate myBirthday(29, 8, 1952);
	string myName ("Daniel J. Duffy");
	Person dd(myName, myBirthday);
	dd.print();

	DatasimDate bBirthday(06, 8, 1994);
	string bName ("Brendan Duffy");
	Person bd(bName, bBirthday);
	bd.print();
	
	return 0;
}