// Account.hpp
//
// Base class for Accounts.
//
// (C) Datasim Education BV 2002

#ifndef Account_hpp
#define Account_hpp

#include "Exceptions.hpp"

class Account
{
public:
	// Constructors and destructor
	Account();							// Default constructor
	Account(const Account& source);		// Copy constructor
	virtual ~Account();					// Destructor

	// Virtual functions to be define in derived classes
	virtual void Withdraw(double amount) = 0;
	virtual double GetBalance() = 0;

	// Operator overloading
	Account& operator = (const Account& source);	// Assignment operator
};

#endif // Account_hpp