// CounterObserver.hpp
//
// (C) Datasim Education BV 2001

#ifndef COUNTEROBSERVER_HPP
#define COUNTEROBSERVER_HPP

#include "Observer.hpp"
#include "Counter.hpp"

class CounterObserver : public Observer
{
private:
	CounterObserver(const CounterObserver&);			// Copy constructor
	CounterObserver& operator=(const CounterObserver&);	// Assignment operator

public:
    CounterObserver(Counter& obj);
	// Method is called when the obeservable object has a change in its state
	void Update(Observable* obj);
};

#endif

