// Person.cpp
//
// 'Hello World' class 
//
// Last Modification Dates
//
// 2006-2-17 DD Kick-off
//
// (C) Datasim Education BV 2005-2006
//


#include "Person.hpp"

Person::Person (const std::string& name, const DatasimDate& DateofBirth)
{
			nam = name;
			dob = DateofBirth;
			createdD = DatasimDate();	// default, today REALLY!

}

void Person::print() const
{ // Who am I?
			
			std::cout << "\n** Person Data **\n";
		
			std::cout << "Name: " << nam << ", Date of birth: " << dob 
						<< ", Age: " << age() << std::endl;

}

int Person::age() const
{
		return int( double(DatasimDate() - dob) / 365.0);
}

