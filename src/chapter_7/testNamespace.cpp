// testNamespace.cpp
//
// Using C++ namespaces. In this way we wish to simulate
// INTERFACE concept by grouping blocks of functions into
// logical units.
// 
// (C) Datasim Education BV 2004-2006
//

#include <iostream>

namespace MyFunctions
{

	double diffusion (double x) { return x; }

	double convection (double x) { return x*x; }
}

namespace YourFunctions
{

	double diffusion (double x) { return 2.0; }

	double convection (double x) { return 1.0; }
}



int main()
{
	{
		namespace CurrentFunctions = MyFunctions;

		std::cout << CurrentFunctions::diffusion(3.0) << std::endl;
	}

	{	// A redefinition of an alias must be in another block

		namespace CurrentFunctions = YourFunctions;

		std::cout << CurrentFunctions::diffusion(3.0) << std::endl;
	}

	// Choose from a hard-coded list of namespaces. Useful
	// for configuration because we often having typical
	// Prototypical functions in a logical grouping. Has
	// potential ...

	std::cout << "Choose: 1) My 2) You \n";
	int j; std::cin >> j;

	if (j == 1)
	{
		namespace CurrentFunctions = MyFunctions;
		std::cout << CurrentFunctions::convection(3.0) << std::endl;
	}
	else
	{ // This kind of code in your is 'Function-independent'
		namespace CurrentFunctions = YourFunctions;
		using namespace CurrentFunctions;
		std::cout << convection(1.0) << std::endl;
	}
	
//	using namespace MyFunctions;
	std::cout << "Me: Directive: \n";
//	cout << convection (10.0) << endl;
//	cout << diffusion (2.0) << endl;

	using namespace YourFunctions;
	std::cout << "You: Directive: \n";
	std::cout << convection (10.0) << std::endl;
	std::cout << diffusion (2.0) << std::endl;

	namespace YourAlias = YourFunctions; // Define alias NS
	std::cout << YourAlias::convection (10.0) << std::endl;
	std::cout << YourAlias::diffusion (2.0) << std::endl;
	
	std::cout << YourFunctions::convection (10.0) << std::endl;

	using YourFunctions::convection;
	std::cout << convection (10.0) << std::endl;

	return 0;
}

