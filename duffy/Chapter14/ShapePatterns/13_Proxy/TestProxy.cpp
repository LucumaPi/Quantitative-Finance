// testProxy.cpp
//
// Program to test Proxy

#include "ProtectedAccount.hpp"
#include <iostream>

void main()
{

	// Create accounts
	Account* account1=new ProtectedAccount(100.0, "password");
	Account* account2=new ProtectedAccount(100.0, "dontknow");

	// Try to withdraw money
	try
	{
		// Withdraw some money
		std::cout<<"Withdraw 25 from account 1"<<std::endl;
		account1->Withdraw(25);
		std::cout<<"Withdraw 25 from account 2"<<std::endl;
		account2->Withdraw(25);
		std::cout<<"Withdraw 100 from account 2"<<std::endl;
		account2->Withdraw(100);
	}
	catch (NoFundsException)
	{
		std::cout<<"Not enough funds"<<std::endl;
	}
	
	// Try to access balance
	try
	{
		std::cout<<"Balance account 1: "<<account1->GetBalance()<<std::endl;
		std::cout<<"Balance account 2: "<<account2->GetBalance()<<std::endl;
	}
	catch (NoAccessException)
	{
		std::cout<<"No permission to access balance"<<std::endl;
	}


	// Clean up memory
	delete account1;
	delete account2;

}
