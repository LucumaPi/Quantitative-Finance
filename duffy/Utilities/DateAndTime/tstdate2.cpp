// tstdat2.cpp
//
// Simple program to test the DatasimDate class. In this 
// case we test arrays of dates an so on.
//
// (C) Datasim BV 1993-2004

#include "DatasimDate.hpp"
#include "array.cpp"
#include "datetimemechanisms.cpp"
#include "arraymechanisms.cpp"



int main()
{

	// Offsets; quarters + half years
	cout << "Offset stuff\n";
	DatasimDate today;
	print(today, STD, '-');
	DatasimDate d3 = today.add_quarter();
	DatasimDate d4 = today.add_halfyear();

	cout << d3 << endl;
	cout << d4 << endl;

	d3 = d3.sub_quarter();
	d4 = d4.sub_halfyear();

	cout << d3 << endl;
	cout << d4 << endl;


	DateOffsetUnit unit = HALFYEARS;
	int N = 4; // The next 12 months
	
	Array<DatasimDate, int> result = createDateArray(today, unit, N);
	print(result);

	cout << "Array of dates with increment\n";
	result = createDateArray(today, today + 365, 13);
	print(result);

	cout << "\nBond-type dates\n";
	int nYears = 2;
	int nPeriodsperYear = 4;
	Vector<DatasimDate, int> result2 = createDateArray(today, nYears, nPeriodsperYear);
	print(result2);

	// Now create arrays of doubles that map from arrays of dates. Be careful of integer
	// division
	DatasimDate now;
	DatasimDate then = now + 60;

	Vector<double, int> result3 = convertDateArray(now, then, 60);
	print(result3);

	return 0;

}