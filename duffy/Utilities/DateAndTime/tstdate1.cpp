// tstDatasimDate.cpp
//
// Simple program to test the DatasimDate class.
//
// (C) Datasim BV 1993-2004

#include "DatasimDate.hpp"
#include <iostream>
using namespace std;


int main()
{
//	d_dyn_string s1("1/1/92");
//	d_dyn_string s2("1/3/92");
//	DatasimDate d1(s1);
	DatasimDate d1(1, 1, 92);
	cout << "First DatasimDate: " << d1 << endl;
	DatasimDate d2(1, 3, 92);
	cout << "Second DatasimDate: " << d2 << endl;
	DatasimDate tod;	// today
	cout << "Today is: " << tod << endl;

	int diff = d2.difference(d1);
	cout << "Difference in days is: " << diff << endl;

/*
	cout << endl << endl;
	d_dyn_string s3("1/1/93");
	d_dyn_string s4("1/3/93");
	DatasimDate d3(s3);
	cout << "First DatasimDate: " << d3 << endl;
	DatasimDate d4(s4);
	cout << "Second DatasimDate: " << d4 << endl;
	int diff2 = d4.difference(d3);
	cout << "Difference in days is: " << diff2 << endl;
*/
	// Looping over numbers
//	DatasimDate fixed("1/1/94");
//	DatasimDate current("1/1/94");

	DatasimDate fixed(1, 1, 94);
	DatasimDate current(1, 1, 94);

	int interval = 30;

	for (int j = 0; j < 12; j++)
	{

		 current = fixed - (j*interval);
		 cout << current << endl;
	}

	// Offsets; quarters + half years
	cout << "Offset stuff\n";
	DatasimDate today;
	DatasimDate d3 = today.add_quarter();
	DatasimDate d4 = today.add_halfyear();

	cout << d3 << endl;
	cout << d4 << endl;

	d3 = d3.sub_quarter();
	d4 = d4.sub_halfyear();

	cout << d3 << endl;
	cout << d4 << endl;

	
	return 0;

}
