// TestOptionStack.cpp
//
// Defining variables and arrays of variables on
// the stack.
//
// Testing a Proof-Of-Concept(POC) class
//
// (C) Datasim Education BV 2005
//

#include <iostream>
using namespace std;

class SimpleOption
{
public:
	double T;
	double K;
	
	SimpleOption () { T = 1.0; K = 100.0; }
	SimpleOption (double expiry, double strike) { T = expiry; K = strike; }


	void print() const
	{ // Read contents of option

		cout << "Expiry: " << T << ", " << "Strike: " << K << endl;
	}

	virtual ~SimpleOption()
	{
		cout << "Bye bye object\n";
	}


};


	
int main()
{
/*
	{ // Define a scope

		SimpleOption opt1;
		opt1.print();
	}

	//opt1.print(); opt1 does not exist

	SimpleOption myPortfolio[10]; 

	// Initialise the array
	for (int j = 0; j < 10; j++)
	{
		myPortfolio[j].print();
	}

//	myPortfolio[-1].print();
//	myPortfolio[1000].print();
*/
	cout << "Heap based stuff \n";
	SimpleOption* opt;
	SimpleOption* opt2;

	// Call default constructor
	opt = new SimpleOption;
	opt -> print();
	(*opt).print();

	// Call constructor with 2 parameters
	opt2 = new SimpleOption(0.25, 90.0);
	opt2 -> print();

	delete opt;
	delete opt2;

	opt = new SimpleOption;
	(*opt).print();

	// Now create an array of options
	SimpleOption* optArray;

	int N = 10;
	optArray = new SimpleOption[N]; // Default constructor called

	for (int j = 0; j < N; j++)
	{ // Member data public for convenience only

		optArray[j].T = 1.0; // 1 year expiry
		optArray[j].K = 100.0; // Strike price

		optArray[j].print(); 
	}

	delete [] optArray;



	return 0;
}
