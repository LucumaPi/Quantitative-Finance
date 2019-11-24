// TestSTLExceptions.cpp
//
// Simple program to test STL exceptions.
//
//
// (C) Datasim Education BV 2004-2006


#include <exception>
#include <iostream>
#include <string>
using namespace std;

int main()
{


	try
	{
		throw overflow_error(string("first"));
	}	

	catch (const std::runtime_error& e)
	{ // This gets caught

		cout << e.what() << endl;
		
	}
	catch (const std::exception& e)
	{

		cout << e.what() << endl;
		
	}




	return 0;
}
