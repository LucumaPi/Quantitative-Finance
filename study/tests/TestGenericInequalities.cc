// TestGenericInequalities.cpp
//
// Main program (Console-based) to test Max and 
// Min functions.
//
// (C) Datasim Education BV 2006
//

#include <iostream>		// Console input and output

#include <duffy/GenericInequalities.hh> // Needed because it is templated
int main()
{
	// Prompt the user for input. Console output (cout)
	// and input (cin)
	int d1, d2;
	std::cout << "Give the first number: ";
	std::cin >> d1;
	std::cout << "Give the second number: ";
	std::cin >> d2;

	char c;	// Character type
	std::cout << "Which function a) Max() or b) Min()? ";
	std::cin >> c;
	if (c == 'a')
	{
		std::cout << "Max value is: " << Max<int>(d1, d2) << std::endl;
	}
	else
	{
		std::cout << "Min value is: " << Min<int>(d1, d2) << std::endl;
	}

	long dA = 12334; long dB = 2; long dC = -3;
	std::cout << "\n\nMax and min of three numbers: " << std::endl;
	std::cout << "Max value is: " << Max<long>(dA, dB, dC) << std::endl;
	std::cout << "Min value is: " << Min<long>(dA, dB, dC) << std::endl;

	return 0;
}
