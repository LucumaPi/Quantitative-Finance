// Stack.hpp
//
// Creating a stack class based on a list class.
//
// Composition and delegation
//
// (C) Datasim Education BV 2006
//
#include <list>

class Stack
{
private:
		std::list<double> elements;
public:
		
		// Default constructor, initialise parts
		Stack() : elements(std::list<double> ()) {}

		// Manipulating elements
		double pop();
		void push(double value);
};