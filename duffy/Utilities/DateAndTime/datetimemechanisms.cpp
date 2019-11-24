// DataTimeMechanisms.cpp
//
// Generic functions for dates, times and timestamps and
// appplications to financial engineering and computational
// finance.
//
// Last modification dates:
//
//	2004-1-9 DD kick-off code
//	2004-1-12 CashFlowThing class		
//
// (C) Datasim Education BV 2006

#ifndef DateTimeMechanisms_cpp
#define DateTimeMechanisms_cpp

#include "datetimemechanisms.hpp"


// Creating dates from characters and strings
// DatasimDate createDate(char* charDate);
// DatasimDate createDate(const string& stringDate);

// Presentation of dates
string DateToString(const DatasimDate& date, DateType dtype, char formatter[20], char delim)

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

{
	julTy day=0, month =0, year=0;
	date.jul_to_greg(day, month, year);
	if (formatter == "ZZ") {
		char *str = new char[20];
		switch (dtype) {
		case EUROPEAN: 		// dd-mm-yy or dd-mm-yyyy if not in this century
			if (year/100 == century/100)
				sprintf(str, "%02lu%c%02lu%c%02lu", day, delim, month, delim, year%100);
			else 	sprintf(str, "%02lu%c%02lu%c%02lu", day, delim, month, delim, year);
			break;
		case ANSI:		// yy-mm-dd or yyyy-mm-dd if not in this century
			if (year/100 == century/100)
				sprintf(str, "%02lu%c%02lu%c%02lu", year%100, delim, month, delim, day);
			else	sprintf(str, "%02lu%c%02lu%c%02lu", year, delim, month, delim, day);
			break;
		case AMERICAN:		// mm-dd-yy or mm-dd-yyyy if not in this century
			if (year/100 == century/100)
				sprintf(str, "%02lu%c%02lu%c%02lu", month, delim, day, delim, year%100);
			else	sprintf(str, "%02lu%c%02lu%c%02lu", month, delim, day, delim, year);
			break;
		case STD:	;
		default:		// dd-mon-yy or dd-mon-yyyy (not in this cent.)
			if (year/100 == century/100)
				sprintf(str, "%02lu%c%s%c%02lu", day, delim, monthname[month - 1],
					delim, year%100);
			else	sprintf(str, "%02lu%c%s%c%02lu", day, delim, monthname[month - 1],
					delim, year);
			break;
		}

		string result(str);

		delete str;
		return result;
		//return(str);
	}

	else {					// a format has been given
		char* str = new char[80];	// space for outstring
		int count = 0;			// counter for format string
		int outcnt = 0;			// counter for output string
		while (formatter[count] != '\0' && outcnt < 70) { // end of input or output
			if (formatter[count] == '%') {		// check char
				count++;		// move one char
				switch (formatter[count++]) {	// scan date expression
				case 'D': 		// D or DD
				   if (formatter[count] == 'D') { // 2 digits for day
					count++;
					sprintf(str + outcnt, "%02lu", day);
					outcnt = strlen(str);
				   }
				   else {		// 1 digit if possible
					sprintf(str + outcnt, "%lu", day);
					outcnt = strlen(str);
				   }
				   break;
				case 'M':		// M or MM
				   if (formatter[count] == 'M') { // 2 digits for month
					count++;
					sprintf(str + outcnt, "%02lu", month);
					outcnt = strlen(str);
				   }
				   else	{		// 1 digit if possible
					sprintf(str + outcnt, "%lu", month);
					outcnt = strlen(str);
				   }
				   break;
				case 'Y':		// YY or YYYY
				   if (formatter[count] != 'Y') // at least 2*Y
					break;
				   else {		// 2nd Y
					count++;	// move one char
					if (formatter[count] == 'Y' &&	// 3rd Y
					formatter[count + 1] == 'Y') {	// 4th Y
						count += 2;	// move past Ys
						sprintf(str + outcnt, "%04lu", year);
						outcnt = strlen(str);
					}
					else {		// 2 or 3 Ys
						sprintf(str + outcnt, "%02lu", year%100);
						outcnt = strlen(str);
					}
				   }
				   break;
				default: 		// % with another char
				   count++;		// just skip %
				   break;
				}			// end switch
			}				// end if 
			else {				// no %, copy char to output
				str[outcnt] = formatter[count];	// and move pointers
				count++;		// move inp. pointer
				outcnt++;		// move output pointer
			}
		}
		str[outcnt] = '\0';			// string terminator

		string result (str);

		// DD Jan 2004
		delete str;

		return result;
		//return(str);				// retun outpustring
	}
}

void print(const DatasimDate& date, DateType dtype, char delimiter)
{

	julTy day=0, month=0, year=0;
	date.jul_to_greg(day, month, year);
	switch (dtype) {
	case EUROPEAN: 		// d[d]-mm-yyyy
		printf("%lu%c%lu%c%lu", day, delimiter, month, delimiter, year);
		break;
	case ANSI:		// yyyy-mm-d[d]
		printf("%lu%c%lu%c%lu", year, delimiter, month, delimiter, day);
		break;
	case AMERICAN:		// mm-d[d]-yyyy
		printf("%lu%c%lu%c%lu", month, delimiter, day, delimiter, year);
		break;
	case STD:	;
	default:
		printf("%lu%c%s%c%lu", day, delimiter, monthname[month - 1],
				delimiter, year);
		break;
	}
}




void print(const Vector<DatasimDate, int>& dateArray)
{

		for (int i = dateArray.MinIndex(); i <= dateArray.MaxIndex(); i++)
		{
			cout << i << ", " << dateArray[i] << endl;
		}
}


// Creating Arrays of Dates (e.g. for cashflow calculations)

// Function to create an array of dates based on a start date, constant offset in some
// unit and number of intervals (Array include start date and has length (N+1)
Vector<DatasimDate, int> createDateArray(const DatasimDate& start, DateOffsetUnit offset,
										 int N)
{

		// Initialise the array
		Vector<DatasimDate, int> result (N+1, 1);	// Start index = 1

		result[result.MinIndex()] = start;

		for (int i = result.MinIndex() + 1; i <= result.MaxIndex(); i++)
		{

				result[i] = nextDate(result[i-1], offset);

		}

		return result;
}

DatasimDate nextDate(const DatasimDate& now, DateOffsetUnit type)
{ // Calculate a new date as an offset (of a certain unit) from a given start date

		// Switch statement
		/* enum DateOffsetUnit
			{

				DAYS,
				MONTHS,
				QUARTERS,
				HALFYEARS,
				YEARS
			}; */


		DatasimDate result;

		if (type == DAYS)
			result = now + 1;

		if (type == MONTHS)
			result = now.add_months(1);


		if (type == QUARTERS)
			result = now.add_quarter();

		if (type == HALFYEARS)
			result = now.add_halfyear();


		if (type == HALFYEARS)
			result = now.add_years(1);

		return result;
}

Vector<DatasimDate, int> createDateArray(const DatasimDate& start, const DatasimDate& end,
										 int N)
{


		int offset = double(end - start)/double(N);

		// Initialise the array
		Vector<DatasimDate, int> result (N+1, 1);	// Start index = 1

		result[result.MinIndex()] = start;

		for (int i = result.MinIndex() + 1; i <= result.MaxIndex(); i++)
		{

				result[i] = result[i-1] + offset;

		}

		return result;

}

Vector<DatasimDate, int> createDateArray(const DatasimDate& start, int numYears, int npy)
{

		// Algorithm: For each year find the dates in it and add to result
		// In fact, a Strategy pattern

		// Initialise the array
		Vector<DatasimDate, int> result (numYears*npy + 1, 1);	// Start index = 1

		// Calculate number of months per period
		int nMonths = 12/npy;

		result[result.MinIndex()] = start;

		for (int i = result.MinIndex() + 1; i <= result.MaxIndex(); i++)
		{

				result[i] = result[i-1].add_months(nMonths);

		}

		return result;

}

Vector<int, int> convertDateArray(const Vector<DatasimDate, int>& dates, int startValue)
{

		// Initialise the array
		Vector<int, int> result (dates.Size(), 1);	// Start index = 1

		result[result.MinIndex()] = startValue;

		for (int i = result.MinIndex() + 1; i <= result.MaxIndex(); i++)
		{

				result[i] = result[i-1] + 1;

		}

		return result;		
}


// Create an array of doubles that correspond to the numeric values of the date array 
Vector<double, int> convertDateArray(const DatasimDate& start, const DatasimDate& end, int nSteps)
{

		// Initialise the array
		Vector<double, int> result (nSteps + 1, 1);	// Start index = 1

		int delta = (end - start) / (nSteps);


		result[result.MinIndex()] = 0.0;

		for (int i = result.MinIndex() + 1; i <= result.MaxIndex(); i++)
		{

				result[i] = result[i-1] + delta;

		}

		return result;		

}




// Classes that are of use for Cash Flows (partial specialisation)
template <class V> CashFlowThing<V>::
	CashFlowThing () : AssocArray<V,DatasimDate>()
{

}

template <class V> CashFlowThing<V>::CashFlowThing (const list<DatasimDate>& dates, const Array<V, int>& values) 
			: AssocArray<V,DatasimDate>(dates, values)
{

}

template <class V> CashFlowThing<V>::
CashFlowThing (const list<DatasimDate>& dates, const V& val) 
			: AssocArray<V,DatasimDate>(dates, val)
{

}

template <class V> CashFlowThing<V>::
CashFlowThing (const Array<DatasimDate, int>& dates, const Array<V, int>& values) 
			: AssocArray<V,DatasimDate>(dates, values)

{

		
}

template <class V> CashFlowThing<V>& CashFlowThing<V>::operator = (const CashFlowThing& cft2)
{ // Copy constructor

	
	(if cft2 == this)
		return *this;


	AssocArray<V, DatasimDate>::operator = (cft2);
	
	return *this;

}
			
#endif