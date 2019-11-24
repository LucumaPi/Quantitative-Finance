// TesExceptionSimple.cpp
//
// Testing the Excel Driver fom the viewpoint of
// exception handling.
//
// (C) Datasim Education BV 2006
//
#include "StringConversions.cpp"
#include "DatasimException.cpp"

#include <string>

double Divide(double x, double y)
{
		// Precondition: y is not zero
		if (y == 0.0)
		{
	
			throw DatasimException(std::string("\tDivide by zero"), std::string("In function Divide"),
				std::string("Try with non-zero value"));
		}

		return x/y;
}

int main()
{
/*
	try
	{
		std::cout << "Give a number to divide by: " << std::endl;
		double y; std::cin >> y;
		
		std::cout << Divide(2.0, y);
	}
	catch(DatasimException& e)
	{
		e.print();
		return 0;
	}
*/
	return 0;
}
