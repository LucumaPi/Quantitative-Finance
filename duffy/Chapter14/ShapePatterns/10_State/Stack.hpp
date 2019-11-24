// Stack.hpp
//
// (C) Datasim Education BV 1999

#ifndef STACK_HPP
#define STACK_HPP


class StackState;

class Stack
{
private:
	StackState* sst;		// State of the stack
	double * Elements;		// Elements of the stack
	long Size;				// Maximum size of the stack
	long Current;			

	Stack(const Stack& source);			// Copy constructor
	// Operators
	Stack& operator = (const Stack& source);

protected:
	// The next functions will be used by the StackState base class
	void ChangeState(StackState* NewState);
	friend class StackState;

	
	void private_push(double element);
	double private_pop();
	int getmaxelements();
	int getcurrentindex();

public:
	// Constructors & destructor
	Stack();							// Default constructor
	Stack(int NewSize);					// Initial size of the stack

	virtual ~Stack();					// Destructor

	void Push(double NewItem);			// Push an element on the stack 
	double Pop();						// Pop the last pushed element of the stack


};

#endif // STACK_HPP