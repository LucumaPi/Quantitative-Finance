// ProtectedAccount.hpp
//
// Account proxy with access control
//
// (C) Datasim Education BV 2002

#ifndef ProtectedAccount_hpp
#define ProtectedAccount_hpp

#include "RealAccount.hpp"
#include <string>

class ProtectedAccount: public Account
{
private:		
	RealAccount* account;
	bool access;

public:
	// Constructors and destructor
	ProtectedAccount();										// Default constructor
	ProtectedAccount(double balance, const std::string& password);	// Constructor with initial balance and password
	ProtectedAccount(const ProtectedAccount& source);		// Copy constructor
	virtual ~ProtectedAccount();							// Destructor

	// Virtual functions to be define in derived classes
	virtual void Withdraw(double amount);
	virtual double GetBalance();

	// Operator overloading
	ProtectedAccount& operator = (const ProtectedAccount& source);	// Assignment operator
};


#endif // ProtectedAccount_hpp