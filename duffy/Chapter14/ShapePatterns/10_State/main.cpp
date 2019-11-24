// main.cpp
//
// Test program for the stack.
//
// (C) Datasim Education 2001

#include "Stack.hpp"
#include <iostream>

void main()
{
	Stack stk;
	Stack stk2(10);
	int counter = 0;

	stk.Push(10.0);
	stk.Push(20.0);

	std::cout << "Element of stk" << stk.Pop() << std::endl;

	for(counter = 0; counter < 10; counter++)
	{
		stk2.Push(counter);
	}

	for(counter = 0; counter < 10; counter++)
	{
		std::cout << "Element : " << stk2.Pop() << std::endl;
	}
}