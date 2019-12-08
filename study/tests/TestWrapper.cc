// TestWrapper.cpp
//
// Testing heterogeneous properties
//
// (C) Datasim Education BV 2006
//


#include <duffy/DatasimDate.hh> // Dates and other useful stuff
#include <duffy/DatesimDateTime.hh>
#include <string> // Standard string class in C++
#include "../src/Wrapper.cc"
#include <duffy/SimplePropertySet.hh>

class Person
{
public: // Everything public, for convenience only

		// Data
		Wrapper<std::string> nam;					// Name of person
		Wrapper<DatasimDate> dob;				// Date of birth

		Wrapper<DatasimDate> createdD;			// Internal, when object was created

		SimplePropertySet<std::string, AnyType*> props;

public:
		Person (const std::string& name, const DatasimDate& DateofBirth)
		{
			nam = name;
			dob = DateofBirth;
			createdD = DatasimDate();	// default, today REALLY!

			// Now add this stuff into the property set
			props = SimplePropertySet<std::string, AnyType*>();
			props.add(std::string("Name"), &nam);
			props.add(std::string("DOB"), &dob);
			props.add(std::string("CreatedDate"), &createdD);

		}

		void print() const
		{ // Who am I?
			std::cout << "\n** Person Data **\n";

			SimplePropertySet<std::string, AnyType*>::const_iterator it;

			for (it = props.Begin(); it != props.End(); it++)
			{

				std::cout << "Key " << it ->first << std::endl;

				// No value printed because we lack polymorphism in 
				// general
			}
		}
};

int main()
{
	DatasimDate myBirthday(29, 8, 1952);
	std::string myName ("Daniel J. Duffy");
	Person dd(myName, myBirthday);
	dd.print();

	DatasimDate bBirthday(06, 8, 1994);
	std::string bName ("Brendan Duffy");
	Person bd(bName, bBirthday);
	bd.print();
	

	Wrapper<std::string> w1;
	Wrapper<std::string> w2;
	if (w1.sameType(w2) == true)
	{
		std::cout << "Same type\n";
	}
	else
	{
		std::cout << "Not Same type\n";
	}

	return 0;
}