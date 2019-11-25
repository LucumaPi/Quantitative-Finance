// TestNonlinearSolver.cpp
//
// Testing Bisection method and Newton Raphson method.
//
// (C) Datasim Education BV 2006
//

#include "NonlinearSolver.hpp"
#include <cmath>
#include <iostream>

double Func1(double x)
{
	double tmp = 0.5 * x;

	return (tmp*tmp) - std::sin(x);
}

double DerivativeFunc1(double x)
{
	// Just the derivative, need for Newton's method
	return (0.5 * x) - std::cos(x);
}


int main()
{
	// Tell where to look for solvers, in a namespace
	using namespace NS_NonlinearSolver;

	// 1. Bisection method

	// Initial interval
	double a = 1.52;
	double b = 2.0;

	// In this version all data is public; in a later version
	// make it private
	BisectionSolver bs;
	bs.myF = Func1;
	bs.a = a; bs.b = b;
	bs.tol = 0.0001;

	double result = bs.solve();
	std::cout << "Bisection: " << result << ", " << bs.accuracy() << std::endl;

	bs.printStatistics();

	// Newton Method
	double initialGuess = 1.2;
	NewtonRaphsonSolver nr(initialGuess);
	nr.myF = Func1;
	nr.derivative = DerivativeFunc1;
	nr.tol = 0.0001;

	double resultNR = nr.solve();
	std::cout << "Newton Raphson: " << resultNR << std::endl;

	nr.printStatistics();

	// Secant method
	double initialGuess0 = 1.2;
	double initialGuess1 = 1.6;

	SecantMethodSolver sm(initialGuess0, initialGuess1, Func1);
	sm.tol = 0.0001;

	double resultSM= sm.solve();
	std::cout << "Secant Method: " << resultSM << std::endl;

	sm.printStatistics();

	std::cout << "Steffensen's method\n";

	// Steffensen's method
	double guess = 1.4;

	SteffensensSolver steff(guess, Func1);
	steff.tol = 0.01;

	double resultST= steff.solve();
	std::cout << "Steffensen's Method: " << resultST << std::endl;

	steff.printStatistics();

	std::cout << "Finished\n";

	return 0;
}