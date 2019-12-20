// EuropeanOptionFactory.hpp
//
// Classes for creating Eurpean Options. This is
// a Factory Method pattern.
//
// (C) Datasim Education BV 2005

#ifndef EuropeanOptionFactory_HH
#define EuropeanOptionFactory_HH

#include "Option.hh"
#include <iostream>

class EuropeanOptionFactory
{
public:
	virtual Option* create() const = 0;
};

class ConsoleEuropeanOptionFactory: public EuropeanOptionFactory
{
public:

	Option* create() const
	{
		std::cout << "\n*** Parameters for option object ***\n";

		Option* opt = new Option;

		std::cout << "Strike: ";
		std::cin >> opt->K;

		std::cout << "Volatility: ";
		std::cin >> opt->sig;

		std::cout << "Interest rate: ";
		std::cin >> opt->r;

		std::cout << "Expiry date: ";
		std::cin >> opt->T;

		std::cout << "1. Call, 2. Put: ";
		std::cin >> opt->type;

		return opt;
	}
};
#endif