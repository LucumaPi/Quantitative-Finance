// RealAccount.hpp
//
// Account class
//
// (C) Datasim Education BV  2002

#ifndef RealAccount_hpp
#define RealAccount_hpp

#include "Account.hpp"

class RealAccount:  public Account
{
private:
	double bal;

public:
	// Constructors and destructor
	RealAccount();								// Default constructor
	RealAccount(double balance);				// Constructor with initial balance
	RealAccount(const RealAccount& source);		// Copy constructor
	virtual ~RealAccount();						// Destructor

	// Virtual functions to be define in derived classes
	virtual void Withdraw(double amount);
	virtual double GetBalance();

	// Operator overloading
	RealAccount& operator = (const RealAccount& source);	// Assignment operator
};

#endif
