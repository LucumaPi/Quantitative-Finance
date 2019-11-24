// TesExceptionSimple.cpp
//
// Testing the Excel Driver fom the viewpoint of
// exception handling.
//
// (C) Datasim Education BV 2006
//
#include "StringConversions.hpp"
#include "DatasimException.hpp"

#include <string>
using namespace std;

double Divide(double x, double y)
{
		// Precondition: y is not zero
		if (y == 0.0)
		{
	
			throw DatasimException(string("\tDivide by zero"), string("In function Divide"),
				string("Try with non-zero value"));
		}

		return x/y;
}

int main()
{


	try
	{
		cout << "Give a number to divide by: " << endl;
		double y; cin >> y;
		
		cout << Divide(2.0, y);
	}
	catch(DatasimException& e)
	{
		e.print();
		return 0;
	}




	return 0;
}
