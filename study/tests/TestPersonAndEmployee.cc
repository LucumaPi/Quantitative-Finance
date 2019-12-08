// TestPersonAndEmployee.cpp
//
// 'Hello World' Inheritance Example
//
// (C) Datasim Education BV 2005-2006
//

#include <duffy/PersonAndEmployee.hh>

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
