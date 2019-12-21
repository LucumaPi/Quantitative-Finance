// Stack.hpp
//
// Creating a stack class based on a list class.
//
// Composition and delegation
//
// (C) Datasim Education BV 2006
//

/**
 * @file Stack.hh
 * @author Daniel J. Duffy (dduffy@datasim.nl)
 * @brief Stack header
 * @version 0.1
 * @date 2019-12-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

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