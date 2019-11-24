// TestConversions.cpp
//
// Simple stuff for converting built-in
// types to strings.
//
// (C) Datasim Education BV 2006
//

#include <sstream>
#include <string>
#include <iostream>

template <typename T>
	std::string getString(const T& value)
{
		std::stringstream s;
		s << value;
		
		return s.str();
}

int main()
{

	// Hard-coded example for starters
	double myDouble = 1.0;
	std::stringstream s;
	s << myDouble;
	std::string result = s.str();
	std::cout << "String value is: " << result << std::endl;

	int i = 10;
	long j = 1234567890;
	float f = 3.14f;
	double d = 2.712222222223;

	std::string myString = getString<int>(i);
	std::cout << myString << std::endl;

	myString = getString<long>(j);
	std::cout << myString << std::endl;

	myString = getString<float>(f);
	std::cout << myString << std::endl;

	myString = getString<double>(d);
	std::cout << myString << std::endl;

	return 0;
}