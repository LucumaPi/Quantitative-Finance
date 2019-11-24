// FunctionWrapper.cpp
//
// Class to test the of function wrappers, these
// are actually commands.
//
// 2005-1-5 DD Kick-off code, POC, later support for void
//
// (C) Datasim Education BV 2004
//
// 

#include <iostream>
using namespace std;

template <class ReturnType, class Arguments> class Command
{
public:
		ReturnType (*f) (Arguments args);
		ReturnType  exec(Arguments args) { return f(args); }
};


template <class T> struct TwoD
{
	T x;
	T y;
};

template <class T> struct ThreeD
{
	T x;
	T y;
	T z;
};


double fun1(double x)
{
	return x*x;
}

double fun2(TwoD<double> p)
{
	return p.x + p.y;
}

int main()
{

	// Single input variable
	Command<double, double> cmd1;
	cmd1.f = fun1;
	double ans = cmd1.exec(2.9);	
	cout << ans << endl;
	
	// Pair of arguments
	TwoD<double> myP; myP.x = 3; myP.y = 4;

	Command<double, TwoD<double> > cmd2;
	cmd2.f = fun2;
	double ans2 = cmd2.exec(myP);	
	cout << ans2 << endl;
	


	return 0;
}
		