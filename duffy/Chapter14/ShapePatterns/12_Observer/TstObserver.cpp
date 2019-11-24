// TstObserver.cpp
//
// (C) Datasim Education BV 2001

#include "Counter.hpp"
#include "CounterObserver.hpp"

void main()
{
	// Create a counter object
	Counter cnt;
	
	// Just increase the counter without observing it
    cnt.IncreaseCounter();
	cnt.IncreaseCounter();
	cnt.IncreaseCounter();

	// Create an observer
	CounterObserver observer1(cnt);

	// Increase the counter
    cnt.IncreaseCounter();
	cnt.IncreaseCounter();
	cnt.IncreaseCounter();

	// Create another observer
	CounterObserver observer2(cnt);

	// Increase the counter
    cnt.IncreaseCounter();
	cnt.IncreaseCounter();
	cnt.IncreaseCounter();

	// remove the first observer
	cnt.DeleteObserver(&observer1);

	// Increase the counter
    cnt.IncreaseCounter();
	cnt.IncreaseCounter();
	cnt.IncreaseCounter();

}

