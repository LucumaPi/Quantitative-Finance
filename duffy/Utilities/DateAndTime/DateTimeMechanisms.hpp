// DataTimeMechanisms.hpp
//
// Generic functions for dates, times and timestamps and
// appplications to financial engineering and computational
// finance.
//
// (C) Datasim Education BV 2004
//


#ifndef DateTimeMechanisms_hpp
#define DateTimeMechanisms_hpp

#include "datasimdate.hpp"
#include "vector.cpp"
#include "assocarray.cpp"

//#include <string>
//using namespace std;

// Define the kind of date format that we can use

enum DateType	
{			STD,		// d[d]-mon-yy[yy]
			EUROPEAN,	// d[d]-m[m]-yy[yy]
			ANSI,		// yy[yy]-m[m]-d[d]
			AMERICAN	// m[m]-d[d]-yy[yy]
};
 
enum DateOffsetUnit
{

			DAYS,
			MONTHS,
			QUARTERS,
			HALFYEARS,
			YEARS
};

static char* monthname[] = {
		"January", "February", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December"
};

// Creating dates from characters and strings
// DatasimDate createDate(char* charDate);
// DatasimDate createDate(const string& stringDate);

// Presentation of dates

// Print a Date in some format and give your delimiter
void print(const DatasimDate& date, DateType dtype, char delimiter = '/');

string DateToString(const DatasimDate& date, DateType dtype, char formatter[20] = "ZZ", char delim = '/');


/*	This function converts the DATE to a string and return it. 
	If the string 'fromatter is 0 (NULL-pointer) the format depends on 
	the enum DateType. If s is not 0 it contains the format-string for 
	the output-string. The format-string can contain the following elements:
 	%D	insert day (1..31) in 1 digit if possible, otherwise 2 digits
 	%DD	insert day (1..31) in 2 digits, first digit may be 0
 	%M	insert month (1..12) in 1 digit if possible, otherwise 2
 	%MM	insert month (1..12) in 2 digits, first digit may be 0
 	%YY	insert yearnumber in 2 digits (year in century)
 	%YYYY	insert full yearnumber in 4 digits
 	any other character will be copied to the output string.

 	An example: 
  		date d("31-1-1977");
 		char str = d.to_string("[%D]-[%MM]-[%YY]");
 	will result str to be:
 		"[31]-[01]-[77]" */


void print(const Vector<DatasimDate, int>& dateArray);

// Creating Arrays of Dates (e.g. for cashflow calculations)
DatasimDate nextDate(const DatasimDate& now, DateOffsetUnit type); // Add an offset to a date
Vector<DatasimDate, int> createDateArray(const DatasimDate& start, DateOffsetUnit offset,
										 int N);


// Given two dates (start, end) generate an array of dates between them. The array contains both end 
// points and the end day maybe changed! (round-off stuff)
Vector<DatasimDate, int> createDateArray(const DatasimDate& start, const DatasimDate& end,
										 int N);

// Create an array of dates given 1) the start date 2) number of years 3) number of periods per year
Vector<DatasimDate, int> createDateArray(const DatasimDate& start, int numYears = 20, int numPeriodsperYear = 2);

// Convert an array of dates to a numeric form that can be used in charting for example. The user can give an initial value 
Vector<int, int> convertDateArray(const Vector<DatasimDate, int>& dates, int startValue);

// Create an array of doubles that correspond to the numeric values of the date array 
Vector<double, int> convertDateArray(const DatasimDate& start, const DatasimDate& end, int nSteps);


// Classes that are of use for Cash Flows (partial specialisation)
template <class V> class CashFlowThing : public AssocArray<V, DatasimDate> 
{ // V == the Values types, could be a heterogeneous type
public:

	// Should really have canonical header file
	CashFlowThing ();

	// Create from a list of dates and an array of values
	CashFlowThing (const list<DatasimDate>& dates, const Array<V, int>& values);

	// Create from a list of dates and an array of values
	CashFlowThing (const list<DatasimDate>& dates, const V& val);

	// Create from an array of dates and an array of values
	CashFlowThing (const Array<DatasimDate, int>& dates, const Array<V, int>& values);

	CashFlowThing& operator=(const CashFlowThing& cft2);	// copy


};

#endif