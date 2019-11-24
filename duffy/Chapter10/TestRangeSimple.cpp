// TestRangeSimple.cpp
//
// Simple tests of Range template class.
//
// (C) Datasim Education BV 2005
//

#include "range.cpp"
#include "datasimdate.hpp" // Dates and other useful stuff

#include <iostream>
using namespace std;

template <class Numeric>
void print(const Range<Numeric>& range)
{
	cout << "[" << range.low() << "," << range.high() << "]\n";
}

int main()
{
	Range<int> range1 (0, 10);

	int valL = -1;
	int valM = 5;
	int valR = 20;

	if (range1.left(valL) == true)
		cout << valL << " to left, OK\n";

	if (range1.contains(valM) == true)
		cout << valM << " in interval, OK\n";

	if (range1.right(valR) == true)
		cout << valR << " to right, OK\n";

	// Create interval between now and 1 year's time
	DatasimDate now;
	DatasimDate nextYear = now.add_years(1);
	Range<DatasimDate> dateSchedule(now, nextYear);

	DatasimDate datL = now - 1; // yesterday
	DatasimDate datM = now.add_halfyear();
	DatasimDate datR = nextYear + 1; // One year and a day from now
	
	
	if (dateSchedule.left(datL) == true)
		cout << datL << " to left, OK\n";

	if (dateSchedule.contains(datM) == true)
		cout << datM << " in interval, OK\n";

	if (dateSchedule.right(datR) == true)
		cout << datR << " to right, OK\n";

	cout << endl << now << endl;
	cout << nextYear << endl;

	cout << "**\n";

	cout << datL << endl;
	cout << datM << endl;
	cout << datR << endl;

	// Default types and synonyms
	Range<double> d(-1.0, 1.0);
	print (d);

	typedef Range<double> DoubleRange;
	DoubleRange d1(-1.0, 1.0);
	print (d1);

	typedef Range<DatasimDate> DateRange;
	DatasimDate today;
	DatasimDate anotherDate = today + 365;
	DateRange whatsAnotherYear(today, anotherDate);
	print(whatsAnotherYear);

	return 0;
}

