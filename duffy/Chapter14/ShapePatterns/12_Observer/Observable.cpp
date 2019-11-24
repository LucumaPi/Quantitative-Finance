// Observable.cpp
//
// (C) Datasim Education BV 2001

#include "Observable.hpp"
#include <functional>

// Default constructor
Observable::Observable() 
{
}

Observable::~Observable()
{// Destructor
}

void Observable::AddObserver(Observer* obj)
{
	Observers.push_back(obj);
}

void Observable::DeleteObserver(Observer* obj)
{

	Observers.remove(obj);
}

void Observable::NotifyObservers()
{
	std::list<Observer*>::iterator it;
	std::list<Observer*>::iterator end = Observers.end();

	for(it = Observers.begin(); it != end; it ++)
	{
		(*it)->Update(this);
	}
	
}
