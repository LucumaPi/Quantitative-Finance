// RealAccount.cpp
//
// (C) Datasim Education BV  2002

#include "RealAccount.hpp"

// Constructors and destructor
RealAccount::RealAccount(): Account()
{ // Default constructor

	bal=0.0;
}

RealAccount::RealAccount(double balance): Account()
{ // Constructor with initial balance

	bal=balance;
}

RealAccount::RealAccount(const RealAccount& source): Account(source)
{ // Copy constructor

	bal=source.bal;
}

RealAccount:: ~RealAccount()
{ // Destructor
}

// Virtual functions to be define in derived classes
void RealAccount::Withdraw(double amount)
{ // Withdraw some money

	if (amount>bal) throw NoFundsException();
	else bal-=amount;
}

double RealAccount::GetBalance()
{ // Return the balance

	return bal;
}

// Operator overloading
RealAccount& RealAccount::operator = (const RealAccount& source)
{ // Assignment operator

	// Call base class assignment
	Account::operator = (source);

	bal=source.bal;
	return *this;
}

