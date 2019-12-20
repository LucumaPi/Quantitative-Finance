// TestRangeSimple.cpp
//
// Simple tests of Range template class.
//
// (C) Datasim Education BV 2005
//

#include <duffy/Range.hh>
#include <duffy/DatasimDate.hh> // Dates and other useful stuff

template <class Numeric>
void print(const Range<Numeric>& range)
{
	std::cout << "[" << range.low() << "," << range.high() << "]\n";
}

int main()
{
	Range<int> range1 (0, 10);

	int valL = -1;
	int valM = 5;
	int valR = 20;

	if (range1.left(valL) == true)
		std::cout << valL << " to left, OK\n";

	if (range1.contains(valM) == true)
		std::cout << valM << " in interval, OK\n";

	if (range1.right(valR) == true)
		std::cout << valR << " to right, OK\n";

	// Create interval between now and 1 year's time
	DatasimDate now;
	DatasimDate nextYear = now.add_years(1);
	Range<DatasimDate> dateSchedule(now, nextYear);

	DatasimDate datL = now - 1; // yesterday
	DatasimDate datM = now.add_halfyear();
	DatasimDate datR = nextYear + 1; // One year and a day from now
	
	
	if (dateSchedule.left(datL) == true)
		std::cout << datL << " to left, OK\n";

	if (dateSchedule.contains(datM) == true)
		std::cout << datM << " in interval, OK\n";

	if (dateSchedule.right(datR) == true)
		std::cout << datR << " to right, OK\n";

	std::cout << std::endl << now << std::endl;
	std::cout << nextYear << std::endl;

	std::cout << "**\n";

	std::cout << datL << std::endl;
	std::cout << datM << std::endl;
	std::cout << datR << std::endl;

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