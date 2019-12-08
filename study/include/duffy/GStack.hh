// Stack.hpp
//
// Creating a stack class based on a list class.
//
// Composition and delegation
//
// (C) Datasim Education BV 2006
//

#include <list>

template <class T>
	class Stack
{ // Generic bounded stack

private:
		std::list<T> elements;	// Elements of the stack
		int N;				// Size of stack
		// Other data ...

public:
		
		// Default constructor, initialise parts
		Stack() : elements(std::list<T> ()) { N = 10;}
		Stack(int size) { // TODO }
	
		// Manipulating elements
		T pop() { // TODO }
		void push(double value){ // TODO }
};