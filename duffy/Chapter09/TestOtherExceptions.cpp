// TestOtherExceptions.cpp
//
// Simple program to test tensors.
//
// 2005-12-3 DD kick-off
// 2006-4-14 DD exceptions
//
// (C) Datasim Education BV 2004-2006

#include <math.h>
#include <string>
#include <iostream>
using namespace std;

class BoundsError
{ // Empty exception class
public:
};

void getValue(int j) throw (int, string)
{
		if (j == 0) throw int(123);
		if (j > 100) throw string("out of bounds");
		throw BoundsError();	// Throws unexpected if no catch(...)
}

void getValueVersionTwo(int j) throw (int, string)
{
		if (j == 0) throw int(123);
		if (j > 100) throw string("out of bounds");
		
		// Re-throw
		throw;
}

int main()
{


	try
	{
		cout << "Value: ";
		int val; cin >> val;
//		getValue(val);
		getValueVersionTwo(val);
	}	

	catch (int& e)
	{
		cout << "integer " << e << endl;
		
	}

	catch (string& e)
	{
		cout << e << endl;
		
	}
	catch (...)
	{
		cout << "No idea, really\n:";
		
	}

	return 0;
}
