// TestOtherExceptions.cpp
//
// Simple program to test tensors.
//
// 2005-12-3 DD kick-off
// 2006-4-14 DD exceptions
//
// (C) Datasim Education BV 2004-2006

#include <iostream>
#include <cmath>
#include <string>

class BoundsError
{ // Empty exception class
public:
};

void getValue(int j) throw (int, std::string)
{
		if (j == 0) throw int(123);
		if (j > 100) throw std::string("out of bounds");
		throw BoundsError();	// Throws unexpected if no catch(...)
}

void getValueVersionTwo(int j) throw (int, std::string)
{
		if (j == 0) throw int(123);
		if (j > 100) throw std::string("out of bounds");
		
		// Re-throw
		throw;
}

int main()
{


	try
	{
		std::cout << "Value: ";
		int val; std::cin >> val;
//		getValue(val);
		getValueVersionTwo(val);
	}	

	catch (int& e)
	{
		std::cout << "integer " << e << std::endl;
		
	}

	catch (std::string& e)
	{
		std::cout << e << std::endl;
		
	}
	catch (...)
	{
		std::cout << "No idea, really\n:";
		
	}

	return 0;
}
