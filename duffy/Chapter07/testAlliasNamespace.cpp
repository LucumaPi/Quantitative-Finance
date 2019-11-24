// testAliasNamespace.cpp
//
// Program to test aliases in namespaces. This is a 
// good way to program the Template Method pattern without
// need for classes.
//
// 2005-1-4 DD kick-off code
//
// (C) Datasim Education BV 2005
//
//
// Idea is to define an algorithm whose body consists of INVARIANT and
// VARIANT parts.

#include <string>
#include <iostream>
using namespace std;

namespace DatasimFunctions
{
	double (*first)();
	double (*second)();

}

double algorithm()
{
	
	return DatasimFunctions::first() + DatasimFunctions::second();
}


namespace myFunctions
{
	double first() {return 2.0;}
	double second(){return 4.0;}

}


int main()
{

	namespace DS = DatasimFunctions;	// Shorthand, alias
	namespace MF = myFunctions;			// Shorthand, alias
	
	DS::first= MF::first;
	DS::second= MF::second;

	double d = algorithm();

	cout << d << endl;

}
