// testNamespace.cpp
//
// Using C++ namespaces. In this way we wish to simulate
// INTERFACE concept by grouping blocks of functions into
// logical units.
// 
// (C) Datasim Education BV 2004-2006
//

#include <iostream>
using namespace std;

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

		cout << CurrentFunctions::diffusion(3.0) << endl;
	}

	{	// A redefinition of an alias must be in another block

		namespace CurrentFunctions = YourFunctions;

		cout << CurrentFunctions::diffusion(3.0) << endl;
	}

	// Choose from a hard-coded list of namespaces. Useful
	// for configuration because we often having typical
	// Prototypical functions in a logical grouping. Has
	// potential ...

	cout << "Choose: 1) My 2) You \n";
	int j; cin >> j;

	if (j == 1)
	{
		namespace CurrentFunctions = MyFunctions;
		cout << CurrentFunctions::convection(3.0) << endl;
	}
	else
	{ // This kind of code in your is 'Function-independent'
		namespace CurrentFunctions = YourFunctions;
		using namespace CurrentFunctions;
		cout << convection(1.0) << endl;
	}
	
//	using namespace MyFunctions;
	cout << "Me: Directive: \n";
//	cout << convection (10.0) << endl;
//	cout << diffusion (2.0) << endl;

	using namespace YourFunctions;
	cout << "You: Directive: \n";
	cout << convection (10.0) << endl;
	cout << diffusion (2.0) << endl;

	namespace YourAlias = YourFunctions; // Define alias NS
	cout << YourAlias::convection (10.0) << endl;
	cout << YourAlias::diffusion (2.0) << endl;
	
	cout << YourFunctions::convection (10.0) << endl;

	using YourFunctions::convection;
	cout << convection (10.0) << endl;

	return 0;
}

