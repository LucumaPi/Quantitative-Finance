// Observer.hpp
//
// (C) Datasim Education BV 2001

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Observable;

class Observer
{
private:
	Observer(const Observer& orig);	// Copy constructor
	Observer& operator=(const Observer& orig);	// Assignment operator

public:
	Observer();		// Default constructor
	~Observer();	// Destructor

	// Method is called when the obeservable object has a change in its state
	virtual void Update(Observable* obj) = 0;
};

#endif


