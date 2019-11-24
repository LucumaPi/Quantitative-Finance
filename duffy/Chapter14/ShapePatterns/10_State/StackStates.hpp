// StackStates.hpp
//
// These are different stack states.
// All stack states are defined in one file for convenience only.
//
// (C) Datasim Education BV 1999

#ifndef STACKSTATES_HPP
#define STACKSTATES_HPP

class Stack;
#include "Singleton.cpp"

class StackState
{
private:
	// Operators
	StackState& operator = (const StackState& source);
	StackState(const StackState& source);					// Copy constructor

protected:
	// Functions needed by the derived classes
	void private_push(Stack* st, double element);
	double private_pop(Stack* st);
	int getmaxelements(Stack* st);
	int getcurrentindex(Stack* st);

public:
	// Constructors & destructor
	StackState();											// Default constructor

	virtual ~StackState();									// Destructor

	void ChangeState(Stack* st, StackState* NewState);

	virtual void Push(Stack* st, double NewElement) =0;// Push an element on the stack
	virtual double Pop(Stack* st) =0;					// Pop the last pushed element of the stack
};

// We used multiple inheritance since the Singleton template argument
// must be the class we want to instanciate and not the base class.
class EmptyState: public StackState
{
// Singleton must be able to create instance of me
friend class Singleton<EmptyState>;

private:
	EmptyState();									// Default constructor
	EmptyState(const EmptyState& source);			// Copy constructor
	EmptyState& operator = (const EmptyState& source);

public:
	// Constructors & destructor
	virtual ~EmptyState();							// Destructor
	
	void Push(Stack* st, double NewElement) ;	// Push an element on the stack
	double Pop(Stack* st) ;					// Pop the last pushed element of the stack

	static EmptyState* Instance();				// Return a unique instance

};

// We used multiple inheritance since the Singleton template argument
// must be the class we want to instanciate and not the base class.
class NotEmptyNotFullState: public StackState
{
// Singleton must be able to create instance of me
friend class Singleton<NotEmptyNotFullState>;

private:
	// Constructors & destructor
	NotEmptyNotFullState();								// Default constructor
	NotEmptyNotFullState(const NotEmptyNotFullState& source);				// Copy constructor
	NotEmptyNotFullState& operator = (const NotEmptyNotFullState& source);

public:
	virtual ~NotEmptyNotFullState();					// Destructor

	void Push(Stack* st, double NewElement) ;		// Push an element on the stack
	double Pop(Stack* st) ;						// Pop the last pushed element of the stack

	static NotEmptyNotFullState* Instance();				// Return a unique instance
};

// We used multiple inheritance since the Singleton template argument
// must be the class we want to instanciate and not the base class.
class FullState: public StackState
{
// Singleton must be able to create instance of me
friend class Singleton<FullState>;

private:
	// Constructors & destructor
	FullState();								// Default constructor
	FullState(const FullState& source);				// Copy constructor
	FullState& operator = (const FullState& source);

public:
	virtual ~FullState();					// Destructor

	void Push(Stack* st, double NewElement) ;		// Push an element on the stack
	double Pop(Stack* st) ;						// Pop the last pushed element of the stack

	static FullState* Instance();				// Return a unique instance
};

#endif // FileStates_hpp