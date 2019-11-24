// CounterObserver.cpp
//
// (C) Datasim Education BV 2001

#include "CounterObserver.hpp"
#include <iostream>

CounterObserver::CounterObserver(Counter& obj)
{
	obj.AddObserver(this);
}
// Method is called when the obeservable object has a change in its state
void CounterObserver::Update(Observable* obj)
{
	Counter* pCounter = dynamic_cast<Counter*>(obj);
	if(pCounter != NULL)
		std::cout << "Observer address : " << this << " Counter has changed : " << pCounter->GetCounter() << std::endl;
	else
		std::cout << "Unknown observable" << std ::endl;
}


