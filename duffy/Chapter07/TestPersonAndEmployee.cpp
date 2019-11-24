// TestPersonAndEmployee.cpp
//
// 'Hello World' Inheritance Example
//
// (C) Datasim Education BV 2005-2006
//

#include "PersonAndEmployee.hpp"

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
	
	Employee dde (myName, myBirthday, string("Cuchulainn Chief"), 0.01, 65);
	dde.print();

	cout << "Working with pointers I\n"; // Non-polymorphic function
	Person* p = &dde;
	p -> print();

	cout << "Working with pointers II\n"; // Polymorphic function
	p -> DeepPrint();

	return 0;
}
