// ProtectedAccount.cpp
//
// Account proxy with access control
//
// (C) Datasim Education BV 2002

#include "ProtectedAccount.hpp"

// Constructors and destructor
ProtectedAccount::ProtectedAccount(): Account()
{ // Default constructor

	account=new RealAccount();
	access=false;
}

ProtectedAccount::ProtectedAccount(double balance, const std::string& password)
{ // Constructor with initial balance and password

	// Create account
	account=new RealAccount(balance);

	// Check password
	if (password=="password") access=true;
	else access=false;
}

ProtectedAccount::ProtectedAccount(const ProtectedAccount& source): Account(source)
{ // Copy constructor

	account=new RealAccount(*source.account);
	access=source.access;
}

ProtectedAccount:: ~ProtectedAccount()
{ // Destructor

	delete account;
}

void ProtectedAccount::Withdraw(double amount)
{ // Withdraw sme money

	account->Withdraw(amount);
}

double ProtectedAccount::GetBalance()
{ // Return the balance

	// Check access permissions
	if (access==false) throw NoAccessException();
	
	// Return balance
	return account->GetBalance();
}

// Operator overloading
ProtectedAccount& ProtectedAccount::operator = (const ProtectedAccount& source)
{ // Assignment operator

	// Check if same object
	if (this==&source) return *this;

	// Call base class assignment
	Account::operator = (source);

	// Delete own data
	delete account;

	// Copy data
	account=new RealAccount(*source.account);
	access=source.access;

	return *this;
}
