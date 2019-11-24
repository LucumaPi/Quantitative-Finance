// Stack.cpp
//
// (C) Datasim Education BV 1999

#include "Stack.hpp"
#include "StackStates.hpp"


	// The next functions will be used by the StackState base class

void Stack::ChangeState(StackState* NewState)
{
	sst = NewState;
}

// The next functions will be used by the StackState base class
void Stack::private_push(double element)
{
	Elements[Current++] = element;
}

double Stack::private_pop()
{
	return Elements[--Current];
}

int Stack::getmaxelements()
{
	return Size;
}

int Stack::getcurrentindex()
{
	return Current;
}


// Constructors & destructor
Stack::Stack()
{// Default constructor
	ChangeState(EmptyState::Instance());
	Current = 0;
	Size = 1;
	Elements = new double[Size];
}

Stack::Stack(int NewSize)
{// Initial size of the stack
	ChangeState(EmptyState::Instance());
	Current = 0;
	Size = NewSize;
	Elements = new double[Size];
}

Stack::~Stack()
{// Destructor
}

void Stack::Push(double NewElement) 
{// Open File 
	sst->Push(this, NewElement);
}

double Stack::Pop() 
{// Close File
	return sst->Pop(this);
}

