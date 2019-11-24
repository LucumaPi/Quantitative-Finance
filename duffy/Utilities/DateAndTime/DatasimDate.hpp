// DatasimDatasimDate.hpp
//
// DatasimDate class that contains numeric and calculation functionality for 
// DatasimDates
//
// (C) Datasim Education BV 2004
//                    



#ifndef DatasimDate_HPP
#define DatasimDate_HPP


#include <iostream>
using namespace std;

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "temporaltype.hpp"

#define OR	||
#define AND	&&
 
typedef	unsigned long	julTy;
static const julTy century = 2000;
 

class DatasimDate : public TemporalType
{
private:

	// The real member data
	julTy Julian_days;		// number of Julian days

	// Private member functions
	void init(julTy days, julTy months, julTy years); // general init function
	julTy j_days(julTy days, julTy months, julTy years) const; // calc #Julian days
		// test functions
	int year_test(int year) const;	// return year (999<year<=9999), or 0
	int mm_test(int month) const;		// return month (1<=month<=12), or 0
	int day_test(int day, int month, int year) const;// test if day in month and year
 
public:
	// Constructors
	DatasimDate();								// default constructor = DatasimDate today
	DatasimDate(const DatasimDate& d2);			// Copy constructor
	DatasimDate(const julTy& days);					// construct DatasimDate from Julian days
	DatasimDate(int days);						// construct DatasimDate from Julian days
	DatasimDate(int day, int month, int year);	// Day, month, year

 	// Selector functions
	int ret_year() const;					// return year of this DatasimDate
	int ret_month() const;					// return monthnumber (1..12) of this DatasimDate
	int ret_day() const;					// return daynumber (1..31) of this DatasimDate
	void jul_to_greg(julTy& d, julTy& m, julTy& y) const;	// give Gregorian DatasimDate 


	// Comparison functions
	bool operator==(const DatasimDate& DatasimDate_2) const;	// compare DatasimDates, TRUE if same days
	bool operator!=(const DatasimDate& DatasimDate_2) const;	// compare DatasimDates, TRUE if not the same day
	bool operator>(const DatasimDate& DatasimDate_2) const;	// DatasimDate is later than DatasimDate_2
	bool operator<(const DatasimDate& DatasimDate_2) const;	// DatasimDate is earlier than DatasimDate_2
	bool operator>=(const DatasimDate& DatasimDate_2) const;	// DatasimDate is later than DatasimDate_2
	bool operator<=(const DatasimDate& DatasimDate_2) const;	// DatasimDate is earlier than DatasimDate_2
	
	// Arithmetic functions
	DatasimDate& operator=(const DatasimDate& DatasimDate_2);	// copy
	//DatasimDate operator+(const DatasimDate& d2);// add two values

	DatasimDate operator+(int days) const;	// Add days to DatasimDate
	//DatasimDate operator+(const julTy& days) const;	//        ''
	DatasimDate operator-(int days) const;	// subtract days from DatasimDate
	//DatasimDate operator-(const julTy& days) const;	//        ''

	DatasimDate operator++();		// add 1 day to DatasimDate
	DatasimDate operator--();		// subtract one day from DatasimDate
	//DatasimDate operator+=(const julTy& days);	// add days to this DatasimDate
	DatasimDate operator+=(int days);	// add days to this DatasimDate
	//DatasimDate operator-=(const julTy& days);	// subtract days from this DatasimDate
	DatasimDate operator-=(int days);	// subtract days from this DatasimDate
	DatasimDate add_months(long months) const;	// return this DatasimDate + #months
	DatasimDate add_quarter() const;		// return this DatasimDate + 3 months ahead
	DatasimDate add_halfyear() const;		// return this DatasimDate + 6 months ahead
	DatasimDate add_years(long years) const;	// return this DatasimDate + #years
	DatasimDate sub_months(long months) const;	// return this DatasimDate - #months
	DatasimDate sub_quarter() const;				// return this DatasimDate - 3 months ahead
	DatasimDate sub_halfyear() const;				// return this DatasimDate - 6 months ahead
	DatasimDate sub_years(long years) const;	// return this DatasimDate - #years
	DatasimDate add_period(const julTy& days, const julTy& months = 0, const julTy &years = 0) const;			// return this DatasimDate plus a period of time
	DatasimDate sub_period(julTy days, julTy months = 0, julTy years = 0) const;			// return this DatasimDate minus a period of time
	long difference (const DatasimDate& DatasimDate_2) const;	// give difference in days between DatasimDate's
	long operator - (const DatasimDate& d2) const;

	
	friend ostream& operator << (ostream& os, const DatasimDate& dat);

};

#endif
