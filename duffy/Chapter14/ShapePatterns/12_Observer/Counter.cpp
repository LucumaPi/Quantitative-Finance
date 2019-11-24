// Counter.cpp
//
// (C) Datasim Education BV 2001

#include "Counter.hpp"
Counter::Counter()
{// Default constructor
	CounterValue = 0;
}

Counter::~Counter()
{// Destructor
}

// Selectors
long Counter::GetCounter() const
{// Return the counter value
	return CounterValue;
}

// Increase the internal counter
void Counter::IncreaseCounter()
{
	CounterValue++;
	NotifyObservers();
}
// Decrease the internal counter
void Counter::DecreaseCounter()
{
	CounterValue--;
	NotifyObservers();
}
