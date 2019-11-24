// Account.cpp
//
// Base class for Accounts.
//
// (C) Datasim Education BV 2002

#include "Account.hpp"

// Constructors and destructor
Account::Account()
{ // Default constructor
}

Account::Account(const Account& source)
{ // Copy constructor
}

Account:: ~Account()
{ // Destructor
}

// Operator overloading
Account& Account::operator = (const Account& source)
{ // Assignment operator

	return *this;
}
