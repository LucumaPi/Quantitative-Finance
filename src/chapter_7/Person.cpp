// Person.cpp
//
// 'Hello World' Inheritance Example
//
// (C) Datasim Education BV 2005
//

#include "DatesimDateTime.hpp"
#include "DatasimDate.hpp" // Dates and other useful stuff
#include <string> // Standard string class in C++

class Person
{
public: // Everything public, for convenience only

		// Data
		std::string nam;					// Name of person
		DatasimDate dob;			// Date of birth

		DatasimDate createdD;		// Internal, when object was created
		DatasimDateTime createdT;	// Internal, when object was created

public:
		Person (const std::string& name, const DatasimDate& DateofBirth)
		{
			nam = name;
			dob = DateofBirth;
			createdD = DatasimDate();	// default, today REALLY!
			createdT = DatasimDateTime();	// default, now REALLY!

		}

		void print() const
		{ // Who am I?
			
			std::cout << "\n** Person Data **\n";
		
			std::cout << "Name: " << nam << ", Date of birth: " << dob
						<< ", Age: " << age() << std::endl;

			std::cout << "Object created: " << createdD << " "; createdT.print(); std::cout << std::endl;
		}

		virtual void DeepPrint() const
		{
			print(); // Calls Person::print()
		}

		int age() const
		{
			return int( double(DatasimDate() - dob) / 365.0);
		}
};

class Employee : public Person
{
public: // For convenience only
		std::string fun;	// Function
		double sal;	// Salary
		int rAge;	// Retirement age

public:
		Employee (const std::string& name, const DatasimDate& DateofBirth,
			const std::string& function, double salary, int Retires) : Person(name, DateofBirth)
		{
			fun = function;
			sal = salary;
			rAge = Retires;

		}

		void print() const
		{ // Who am I and what do I do?

			// Print Base class data

			std::cout << "\n** Employee Data **\n";
			Person::print();

			// Now print data from current derived class
			std::cout << "\nFunction: " << fun << ", Salary: " << sal
						<< ", Retires at: " << rAge << std::endl
						<< YearsToRetirement() << " years to retirement.\n";
		}

		void DeepPrint() const
		{
			print(); // Calls Employee::print()
		}

		int YearsToRetirement() const
		{ // How many more years slogging away at C++?

			return rAge - age();
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
	
	Employee dde (myName, myBirthday, std::string("Cuchulainn Chief"), 0.01, 65);
	dde.print();

	std::cout << "Working with pointers I\n"; // Non-polymorphic function
	Person* p = &dde;
	p -> print();

	std::cout << "Working with pointers II\n"; // Polymorphic function
	p -> DeepPrint();

	return 0;
}