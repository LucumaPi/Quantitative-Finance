// PersonAndEmployee.cpp
//
// 'Hello World' Inheritance Example
//
// (C) Datasim Education BV 2005-2006
//


#include "datasimdate.hpp" // Dates and other useful stuff
#include "datetime.hpp"
#include <string> // Standard string class in C++
using namespace std;

class Person
{
public: // Everything public, for convenience only

		// Data
		string nam;					// Name of person
		DatasimDate dob;			// Date of birth

		DatasimDate createdD;		// Internal, when object was created
		DatasimDateTime createdT;	// Internal, when object was created

public:
		Person (const string& name, const DatasimDate& DateofBirth)
		{
			nam = name;
			dob = DateofBirth;
			createdD = DatasimDate();	// default, today REALLY!
			createdT = DatasimDateTime();	// default, now REALLY!

		}

		void print() const
		{ // Who am I?
			
			cout << "\n** Person Data **\n";
		
			cout << "Name: " << nam << ", Date of birth: " << dob 
						<< ", Age: " << age() << endl;

			cout << "Object created: " << createdD << " "; createdT.print(); cout << endl;
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
		string fun;	// Function
		double sal;	// Salary
		int rAge;	// Retirement age

public:
		Employee (const string& name, const DatasimDate& DateofBirth,
			const string& function, double salary, int Retires) : Person(name, DateofBirth)
		{
			fun = function;
			sal = salary;
			rAge = Retires;

		}

		void print() const
		{ // Who am I and what do I do?

			// Print Base class data

			cout << "\n** Employee Data **\n";
			Person::print();

			// Now print data from current derived class
			cout << "\nFunction: " << fun << ", Salary: " << sal 
						<< ", Retires at: " << rAge << endl 
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

