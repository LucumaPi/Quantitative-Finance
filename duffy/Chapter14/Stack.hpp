// Stack.hpp
//
// Creating a stack class based on a list class.
//
// Composition and delegation
//
// (C) Datasim Education BV 2006
//

class Stack
{
private:
		list<double> elements;
public:
		
		// Default constructor, initialise parts
		Stack() : elements(list<double> ()) {}
	
		// Manipulating elements
		double pop();
		void push(double value);
};

