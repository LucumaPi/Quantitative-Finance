// TestSTLExceptions.cpp
//
// Simple program to test STL exceptions.
//
//
// (C) Datasim Education BV 2004-2006


#include <iostream>
#include <exception>
#include <string>

int main()
{


	try
	{
		throw std::overflow_error(std::string("first"));
	}	

	catch (const std::runtime_error& e)
	{ // This gets caught

		std::cout << e.what() << std::endl;

	}
	catch (const std::exception& e)
	{

		std::cout << e.what() << std::endl;
		
	}

	return 0;
}