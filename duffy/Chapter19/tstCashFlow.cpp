// tstCashFlow.cpp
//
// Simple program to test the DatasimDate class. In this 
// case we test arrays of dates an so on.
//
// Specific case: Cashflows
//
// (C) Datasim BV 1993-2006

#include "DatasimDate.hpp"
#include "array.cpp"
#include "datetimemechanisms.hpp"
#include "arraymechanisms.cpp"

void print (const CashFlowThing<double>& cf)
{

	// Iterating in the map
	CashFlowThing<double>::const_iterator i = cf.Begin();

	while (i != cf.End())
	{
		cout << (*i).first << ", " << cf[(*i).first] << ", " << endl;
		i++;
	}

	cout << endl;
}



int main()
{

	// Offsets; quarters + half years
	cout << "Offset stuff\n";
	DatasimDate today;
	print(today, STD, '-');


	cout << "\nBond-type dates\n";
	int nYears = 2;
	int nPeriodsperYear = 4;
	Vector<DatasimDate, int> result2 = createDateArray(today, nYears, nPeriodsperYear);
	print(result2);


	// Cashflows
	// CashFlowThing (const Array<DatasimDate, int>& dates, const Array<V, int>& values);

	cout << "Cash flows\n";
	Array<double> values (result2.Size(), result2.MinIndex(), 100.0);		// Par
	CashFlowThing<double> myFlow(result2, values);
	print(myFlow);

	return 0;

}