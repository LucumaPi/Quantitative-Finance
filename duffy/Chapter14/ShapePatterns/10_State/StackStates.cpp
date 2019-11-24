// StackStates.cpp
//
// Stack states
// This are different stack states.
// All traverse states are defined in one file for convenience only.
//
//
// (C) Datasim Education BV 1999

#include "StackStates.hpp"
#include "Stack.hpp"

StackState::StackState()
{ // Default constructor
}

StackState::~StackState()
{ // Destructor
}

void StackState::ChangeState(Stack* st, StackState* NewState)
{
	st->ChangeState(NewState);
}

// Functions needed by the derived classes
void StackState::private_push(Stack* st, double element)
{
	st->private_push(element);
}

double StackState::private_pop(Stack* st)
{
	return st->private_pop();
}

int StackState::getmaxelements(Stack* st)
{
	return st->getmaxelements();
}

int StackState::getcurrentindex(Stack* st)
{
	return st->getcurrentindex();
}


/*****************/
/* EmptyState State */
/*****************/

EmptyState::EmptyState(): StackState()
{ // Default constructor
}



EmptyState::~EmptyState()
{ // Destructor
}

void EmptyState::Push(Stack* st, double NewElement) 
{// Push an element on the stack
	private_push(st,NewElement);
	if(getcurrentindex(st) < getmaxelements(st))
		ChangeState(st,NotEmptyNotFullState::Instance());
	else
		ChangeState(st,FullState::Instance());

}

double EmptyState::Pop(Stack* fp) 
{// Pop the last pushed element of the stack
	return 0.0;
}

EmptyState* EmptyState::Instance()
{// Return a unique instance
	return Singleton<EmptyState>::instance();
}

/******************/
/* NotEmptyNotFullState State */
/******************/

NotEmptyNotFullState::NotEmptyNotFullState(): StackState()
{ // Default constructor
}

NotEmptyNotFullState::~NotEmptyNotFullState()
{ // Destructor
}


void NotEmptyNotFullState::Push(Stack* st, double NewElement) 
{// Push an element on the stack

	private_push(st,NewElement);
	if(getcurrentindex(st) == getmaxelements(st))
	{
		ChangeState(st, FullState::Instance());
	}
}

double NotEmptyNotFullState::Pop(Stack* st)
{// Pop the last pushed element of the stack
	if(getcurrentindex(st) == 1)
		ChangeState(st,EmptyState::Instance());
	return private_pop(st);
}

NotEmptyNotFullState* NotEmptyNotFullState::Instance()
{// Return a unique instance
	return Singleton<NotEmptyNotFullState>::instance();
}

	/******************/
/* FullState State */
/******************/

FullState::FullState(): StackState()
{ // Default constructor
}

FullState::~FullState()
{ // Destructor
}


void FullState::Push(Stack* st, double NewElement)
{// Push an element on the stack
}

double FullState::Pop(Stack* st)
{// Pop the last pushed element of the stack
	if( (getcurrentindex(st)-1) == 0)
		ChangeState(st,EmptyState::Instance());
	else
		ChangeState(st,NotEmptyNotFullState::Instance());
	return private_pop(st);
}

FullState* FullState::Instance()
{// Return a unique instance
	return Singleton<FullState>::instance();
}
