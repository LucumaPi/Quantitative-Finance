// TestAlias.cpp
//
// Using namespace in combnation with function
// pointers.
//
// (C) Datasim Education BV 2005
//

#include <iostream>
using namespace std;

namespace StandardInterface 
{ // Namespace consistig of function pointers

	double (*func1) (double x);
	double (*func2) (double x, double y);
}

namespace Implementation1
{

	double F1 (double x) { return x; }

	double F2 (double x, double y) { return x*y; }
}

namespace Implementation2
{

	double G1 (double x) { return -x; }

	double G2 (double x, double y) { return -x*y; }
}

class MyClass
{
public:
	double result;
//	using namespace StandardInterface;

	MyClass()
	{
//		result = func1(2.0) * func2(1.0, 3.0);
	}
};

int main ()
{

	// Assign the function pointers from NS
	StandardInterface::func1 = Implementation1::F1;
	StandardInterface::func2 = Implementation1::F2;

	using namespace StandardInterface;
	cout << func1(2.0) << ", " << func2(3.0, -4.0) << endl;

	func1 = Implementation2::G1;
	func2 = Implementation2::G2;
	cout << func1(2.0) << ", " << func2(3.0, -4.0) << endl;

	return 0;
}
