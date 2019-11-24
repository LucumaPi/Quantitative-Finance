// Observable.hpp
//
// (C) Datasim Education BV 2001

#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <list>

#include "Observer.hpp"


class Observable
{
private:
	std::list<Observer*> Observers;

	Observable(const Observable& org);
	Observable& operator=(const Observable& org);

public:
	Observable();	// Default constructor
	virtual ~Observable();	// Destructor

	void AddObserver(Observer* obj);		// Add an observer to the list
	void DeleteObserver(Observer* obj);		// Remove an observer from the list
	void NotifyObservers();// Notify the observers
};

#endif

