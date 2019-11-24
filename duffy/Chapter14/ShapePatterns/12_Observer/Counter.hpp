// Counter.hpp
//
// (C) Datasim Education BV 2001

#ifndef COUNTER_HPP
#define COUNTER_HPP

#include "Observable.hpp"

class Counter : public Observable
{
private:
	long CounterValue;

	Counter(const Counter& orig);	// Copy constructor
	Counter& operator=(const Counter& orig);	// Assignment operator
public:
	Counter();	// Default constructor
	~Counter();	// Destructor

	// Selectors
	long GetCounter() const;	// Return the counter value
	// Increase the internal counter
	void IncreaseCounter();
	// Decrease the internal counter
	void DecreaseCounter();
};

#endif