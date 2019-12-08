// TestInequalities.cpp
//
// Main program (Console-based) to test Max and 
// Min functions.
//
// (C) Datasim Education BV 2006
//

#include <iostream>		// Console input and output

#include <duffy/Inequalities.hh>

int main()
{
	// Prompt the user for input. Console output (cout)
	// and input (cin)
	double d1, d2;
	std::cout << "Give the first number: ";
	std::cin >> d1;
	std::cout << "Give the second number: ";
	std::cin >> d2;

	char c;	// Character type
	std::cout << "Which function a) Max() or b) Min()? ";
	std::cin >> c;
	if (c == 'a')
	{
		std::cout << "Max value is: " << Max(d1, d2) << std::endl;
	}
	else
	{
		std::cout << "Min value is: " << Min(d1, d2) << std::endl;
	}

	double dA = 1.0; double dB = 2.0; double dC = 3.0;
	std::cout << "\n\nMax and min of three numbers: " << std::endl;
	std::cout << "Max value is: " << Max(dA, dB, dC) << std::endl;
	std::cout << "Min value is: " << Min(dA, dB, dC) << std::endl;

	return 0;
}