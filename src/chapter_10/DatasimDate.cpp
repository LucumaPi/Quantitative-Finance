// datasimDatasimDate.cpp
//
       /*****************************************************************
        * Prog. Name : DDatasimDate.CXX                                        *
        * Copyright  : Datasim b.v. 1990                                *
        * Author     : Eric Manshande & Henri Schenau  14-3-1990        *
        * Descr.     : This file contains the class DatasimDate.               *
	*****************************************************************/

// Last modification DatasimDates:
//
//	D Duffy 2003-12-28 New version (after 13 years!) kick off
//	Many thanks to Eric and Henry; we won't see your kind again
//	DD 2004-1-9 const functions qualified as needed
// DD 2006-8-8  local_time = time((long*) 0);        // get time (and DatasimDate) from system
// Now:	local_time = time(0); New strict compiler
// DD 2006-8-8 Only possible now is Date + int
 
#include "DatasimDate.hpp"
 
//	the following initialization of the static class members is not
//	possible before version 2.0 of C++. Instead, they are implicitly
//	defined 0. For DatasimDate::dtype this is ok but for DatasimDate::delim it is
//	not, so be sure to set this to an appropriate value in the main
//	program using the function DatasimDate::set_delim(char).
 
 
void DatasimDate::init(julTy days, julTy months, julTy years)
/*
 *	general init procedure to initialize this DatasimDate. It calculates
 *	the number of Julian days and sets the pivate member Julian_days
 *	to that value.
 */
{
	Julian_days = j_days(days, months, years);
}

int DatasimDate::year_test(int year) const
/*
 *	test the value of year. If the value is between 0 and 99,
 *	return the value + this century (defined in header file).
 *	if the value is between 1000 and 9999, just return the value.
 *	else return 0.
 */
{
		// Bug?
        if (year < 0 OR year > 9999)
			return 0;

		// First line changed for the 21st Century; time returned from system
		// is 100 + year in 21st century
		if (year > 100)
                return(century + year - 100);

        if (year >= 1000)
                return(year);
        
		return(0);
}
 
 
int DatasimDate::mm_test(int month) const
/*
 *	Test the value of month. If the value is between 1 and 12
 *	return the value, else return 0.
 */
{
        return( (month < 1 OR month > 12) ? 0 : month);
}
 
 

int DatasimDate::day_test(int day, int month, int year)  const
/*
 *	Test if the given day (which is a month-day-number) is a valid
 *	day in the given month and year. It checks for leapyears, etc.
 *	If it is valid, return the given day, else return 0.
 */
{
        static int numdays[] =			// number of days in month
                { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if (day < 1 OR month < 1 OR month > 12 OR year == 0)
			return(0);
		else if (month == 2)
                        if ((year % 4 != 0) OR (year % 100 == 0 AND year % 400 != 0))
                                return(day <= 28 ? day : 0);
                        else
                                return(day <= 29 ? day : 0);
		else
			return(day <= numdays[month - 1] ? day : 0);
}
 
 
DatasimDate::DatasimDate(const DatasimDate& DatasimDate_2)
/*
 *	copy initializer.
 */
{
	Julian_days = DatasimDate_2.Julian_days;	// same DatasimDate
}
 
DatasimDate& DatasimDate::operator=(const DatasimDate& DatasimDate_2)
/*
 *	this function takes care of assigning DatasimDate_2 to this DatasimDate and
 *	returns this DatasimDate for multiple assignement. If this DatasimDate and
 *	DatasimDate_2 are the same objects, just return this DatasimDate.
 */
{
	if (this != &DatasimDate_2)			// beware of d = d;
		Julian_days = DatasimDate_2.Julian_days;

	return *this;				// for multiple assignment
}


DatasimDate::DatasimDate()
/*
 *	This is the default constructor. The DatasimDate is initialized
 *	with the system DatasimDate at the moment of creation. This function
 *	uses ansi-C structures and functions and should be machine 
 *	independent.
 */
{
	
        time_t local_time;              // type to hold time
        struct tm *t_ptr;               // struct to contain time, DatasimDate etc
 
      //DD 2006-8-8  local_time = time((long*) 0);        // get time (and DatasimDate) from system
		local_time = time(0);
        t_ptr = localtime(&local_time); // convert to struct
        julTy yy_t = year_test(t_ptr->tm_year);	// test year, month and day
        julTy mm_t = mm_test(t_ptr->tm_mon + 1);
        julTy dd_t = day_test(t_ptr->tm_mday, mm_t, yy_t);
        init(dd_t, mm_t, yy_t);	// calculate Julian days


}

 
DatasimDate::DatasimDate(const julTy& days)
/*
 *	construct a DatasimDate from a number of Julian days.
 */
{
	Julian_days = days;
}
 
 
DatasimDate::DatasimDate(int days)
/*
 *	construct a DatasimDate from a number of Julian days.
 */
{
	Julian_days = days;
}
 

 
DatasimDate::DatasimDate(int day, int month, int year)
{ // Day, month, year


	Julian_days = j_days(day, month, year);
}

julTy DatasimDate::j_days(julTy day, julTy month, julTy year)  const
/*
 *	return the number of Julian days from the given Gregorian DatasimDate
 *	( in the variables day, month and year). If a wrong DatasimDate is given, 
 *	it will return 0.	 Algorithm 199 from Communications
 *	af the ACM Volume6, No.8, (Aug. 1963) p.144. Gregorian calender
 *	started September 14, 1752. The algorithm is only valid for
 *	DatasimDates from this calender, other DatasimDates may result in invalid Julian 
 *	days.
 */
{
	julTy c, ya;
 
        if (day == 0 OR month == 0 OR year == 0)	// wrong DatasimDate.
                return(0);
        else {		// valid DatasimDate, algorithm to convert to Julian days. 
		if (month > 2)
			month -= 3;
		else {
			month += 9;
			year--;
		}
		c = year / 100;
		ya = year - 100 * c;
		return(((146097 * c) >> 2) + ((1461 * ya) >> 2) +
			(153 * month + 2) / 5 + day + 1721119);
	}
}
	
 
void DatasimDate::jul_to_greg(julTy& day, julTy& month, julTy& year) const
/*
 *	get the Gregorian DatasimDate (returned in the referenced variables
 *	day, month and year) from the number of Julian days (member
 *	Julian_days) from this DatasimDate. Algorithm 199 from Communications
 *	af the ACM Volume6, No.8, (Aug. 1963) p.144. If the number of
 *	Julian days = 0, return January 1, 1900. Gregorian calender started
 *	September 14, 1752. 
 */
{
	if (Julian_days == 0) {			// return January 1, 1900
		day = 1; month = 1; year = 1900;
		return;
	}
	else {					// This is the algorithm.
		julTy j = Julian_days - 1721119l;
		year = (julTy)(((j << 2) - 1) / 146097l);
		j = (j << 2) - 1 - 146097l * year;
		day = (julTy)(j >> 2);
		j = ((day << 2) + 3) / 1461;
		day = (julTy)((day << 2) + 3 - 1461 * j);
		day = (day + 4) >> 2;
		month = (5 * day - 3) / 153;
		day = 5 * day - 3 - 153 * month;
		day = (day + 5) / 5;
		year = (julTy)(100 * year + j);
		if (month < 10)
			month += 3;
		else {
			month -=9;
			year++;
		}
	}
}
 
 




int DatasimDate::ret_year() const
/*
 *	return the year of this DatasimDate.
 */
{
	julTy d=0, m=0, y=0;
	jul_to_greg(d, m, y);
	return(y);
}


int DatasimDate::ret_month() const
/*
 *	return the monthnumber of this DatasimDate. It will be between 1 and 12.
 */
{
	julTy d=0, m=0, y=0;
	jul_to_greg(d, m, y);
	return(m);
}


int DatasimDate::ret_day() const
/*
 *	return the daynumber of this DatasimDate. It will be between 1 and 31.
 */
{
	julTy d=0, m=0, y=0;
	jul_to_greg(d, m, y);
	return(d);
}
 
 
bool DatasimDate::operator==(const DatasimDate& DatasimDate_2)  const
/*
 *	compare two DatasimDates. Return true if they are on the same day,
 *	else return false (so the objects need not be the same).
 */
{
	return(Julian_days == DatasimDate_2.Julian_days ? true : false);
};
		
 
bool DatasimDate::operator!=(const DatasimDate& DatasimDate_2)  const
/*
 *	compare two DatasimDates. Return true if they are not on the same day,
 *	else return false.
 */
{
	return(Julian_days != DatasimDate_2.Julian_days ? true : false);
}
 
bool DatasimDate::operator>(const DatasimDate& DatasimDate_2)  const
/*
 *	if this DatasimDate is later than DatasimDate_2, return true else return false.
 */
{
	return(Julian_days > DatasimDate_2.Julian_days ? true : false);
}
 
bool DatasimDate::operator<(const DatasimDate& DatasimDate_2)  const
/*
 *	if this DatasimDate is earlier than DatasimDate_2, return true else return false.
 */
{
	return(Julian_days < DatasimDate_2.Julian_days ? true : false);
}
 
 
bool DatasimDate::operator>=(const DatasimDate& DatasimDate_2)  const
/*
 *	if DatasimDate_2 is earlier than this DatasimDate, return true else return false.
 */
{
	return(Julian_days >= DatasimDate_2.Julian_days ? true : false);
}
 
bool DatasimDate::operator<=(const DatasimDate& DatasimDate_2)  const
/*
 *	if DatasimDate_2 is later than this DatasimDate, return true, else return false
 */
{
	return(Julian_days <= DatasimDate_2.Julian_days ? true : false);
}
 

//DatasimDate DatasimDate::operator+=(const julTy& nr_days)  
/*
 *	add number of days to this DatasimDate and return it. This is changed!
 */
/*{
	Julian_days += nr_days;
	return(*this);
}*/
 
DatasimDate DatasimDate::operator+=(int nr_days)
/*
 *	add number of days to this DatasimDate and return it. This is changed!
 */
{
	Julian_days += nr_days;
	return(*this);
}
 
//DatasimDate DatasimDate::operator-=(const julTy& nr_days)
/*
 *	subtract number of days from this DatasimDate and return it. This is changed!
 */
/*{
	Julian_days -= nr_days;
	return(*this);
}*/
 
DatasimDate DatasimDate::operator-=(int nr_days)
/*
 *	subtract number of days from this DatasimDate and return it. This is changed!
 */
{
	Julian_days -= nr_days;
	return(*this);
}
 
 
DatasimDate DatasimDate::operator++()
/*
 *	add 1 day to this DatasimDate and return it. This is changed!
 */
{
	Julian_days++;				// one day later
	return(*this);				// return day later
}
 
 
DatasimDate DatasimDate::operator--()
/*
 *	subtract one day from this DatasimDate and return it. This is changed!
 */
{
	Julian_days--;
	return(*this);
}
 
 
//DatasimDate DatasimDate::operator+(const DatasimDate& d2)
/*
 *	add two values. The values can be DatasimDates or one of them can
 *	be a number. If one of them is a number, the number will be
 *	converted to a DatasimDate (implicit type onversion via a constructor).
 *	This is a friend function so d1 can be a number or d2 can be a
 *	number. In this way it possible to state:
 *	DatasimDate d = DatasimDate("1-1-1977") + 5;	// implicit conversion of 5 to DatasimDate
 *		as well as:
 *	DatasimDate d = 5 + DatasimDate("1-1-1977");	// implicit conversion of 5 to DatasimDate
 */
/*{
	julTy tot_days = Julian_days + d2.Julian_days;
	DatasimDate d(tot_days);
	return(d);
}*/
 
DatasimDate DatasimDate::operator-(int nr_days)  const
/*
 *	return this DatasimDate minus the number of days. This is not changed!
 */
{
	DatasimDate d(Julian_days);
	d.Julian_days -= nr_days;
	return(d);
}
 
 
//DatasimDate DatasimDate::operator+(const julTy& nr_days)  const		// Add. nr_days to DatasimDate
/*
 *	return this DatasimDate PLUS the number of days. This is not changed!
 */
/*{
	DatasimDate d(Julian_days);
	d.Julian_days += nr_days;
	return(d);
}*/
 
 DatasimDate DatasimDate::operator+(int nr_days)  const
/*
 *	return this DatasimDate PLUS the number of days. This is not changed!
 */
{
	DatasimDate d(Julian_days);
	d.Julian_days += nr_days;
	return(d);
}
 
 
//DatasimDate DatasimDate::operator-(const julTy& nr_days)  const		// subtr. nr_days from DatasimDate
/*
 *	return this DatasimDate minus the number of days. This is not changed!
 */
/*{
	DatasimDate d(Julian_days);
	d.Julian_days -= nr_days;
	return(d);
}*/
 
DatasimDate DatasimDate::add_period(const julTy& days, const julTy& months, const julTy& years)  const
/*
 *	add a period of time to this (which itself will not be changed) DatasimDate
 *	and return that DatasimDate. The period of time can be any number of days,
 *	months and years. First the number of years is added (if specified)
 *	then the number of months (if specified) and finaly the number of 
 *	days. So:
 *	DatasimDate d = DatasimDate("28-2-1980").add_period(3, 13, 1);
 *	results in March 31, 1982.
 */
{
	julTy nday, nmonth, nyear;
		
	jul_to_greg(nday, nmonth, nyear); // calc Greg. cal. from This DatasimDate
	nmonth += months;		// add months
	nyear += ((nmonth - 1) / 12);	// how many years from months ?
	nmonth = (nmonth - 1) % 12 + 1;	// remaining months (1..12)
	nyear += years;			// add years
	while (day_test(nday, nmonth, nyear) == 0) // day still valid in month?
		nday--;			// no, subtract one monthday	
 
	julTy total_days = days + j_days(nday, nmonth, nyear); // total Julian days
	DatasimDate d(total_days);		// construct new DatasimDate
	return(d);			// return new DatasimDate
}
 
 
DatasimDate DatasimDate::sub_period(julTy days, julTy months, julTy years)  const
/*
 *	subtract a period of time from this (which will not be changed) DatasimDate
 *	and return that DatasimDate. The period of time can be any number of days,
 *	months and years. First the number of years is subtracted (if speci-
 *	fied) then the number of months (if specified) and finaly the number of
 *	days. So:
 *	DatasimDate d = DatasimDate("1-3-1980").sub_period(3, 13, 1);
 *	results in January 29, 1978.
 */
{
	julTy nday, nmonth, nyear;
 
	jul_to_greg(nday, nmonth, nyear); // calc Greg cal. from this DatasimDate
	nyear -= (months / 12);		// how many years in months ?
	months %= 12;			// remaining months;
	if (months >= nmonth) {		// more than months in this DatasimDate
		nyear--;		// one year earlier
		nmonth = 12 + nmonth - months;	// remaining months
	}
	else nmonth -= months;
	nyear -= years;
	while (day_test(nday, nmonth, nyear) == 0) // day still valid in month?
		nday--;			// no, subtract one monthday	
 
	julTy total_days = j_days(nday, nmonth, nyear) - days;
	DatasimDate d(total_days);
	return(d);
}
	
 
DatasimDate DatasimDate::add_months(long months)  const
/*
 *	this function will return a DatasimDate which is a number of months later
 *	than this DatasimDate. If 'months' is negative, the returned DatasimDate will be
 *	earlier than this DatasimDate. This DatasimDate itself wil not be changed.
 */
{
	if (months > 0)			// positive number of months ?
		return( this->add_period(0, months, 0) ); // add months
	else				// negative number of months
		return( this->sub_period(0, months * -1, 0) ); // subtract
}
 
DatasimDate DatasimDate::add_quarter()  const
{ // Return this DatasimDate + 3 months ahead

	long monthsInQuarter = 3;
	return add_months(monthsInQuarter);
}


DatasimDate DatasimDate::add_halfyear()  const
{ // Return this DatasimDate + 6 months ahead

	long monthsInhalfYear = 6;
	return add_months(monthsInhalfYear);

}

 
DatasimDate DatasimDate::sub_quarter()  const
{ // Return this DatasimDate - 3 months ahead

	long monthsInQuarter = 3;
	return sub_months(monthsInQuarter);
}


DatasimDate DatasimDate::sub_halfyear()  const
{ // Return this DatasimDate - 6 months ahead

	long monthsInhalfYear = 6;
	return sub_months(monthsInhalfYear);

}


DatasimDate DatasimDate::add_years(long years)  const
/*
 *	this function will return a DatasimDate which is a number of years later
 *	than this DatasimDate. If 'years' is negative, the returned DatasimDate will be
 *	earlier than this DatasimDate. This DatasimDate itself wil not be changed.
 */
{
	if (years > 0)			// positive number of years ?
		return( this->add_period(0, 0, years) ); // add years
	else				// negative number of years
		return( this->sub_period(0, 0, years * -1) ); // subtract
}
 
 
DatasimDate DatasimDate::sub_months(long months)  const
/*
 *	this function will return a DatasimDate which is a number of months earlier
 *	than this DatasimDate. If 'months' is negative, the returned DatasimDate will be
 *	later than this DatasimDate. This DatasimDate itself wil not be changed.
 */
{
	if (months > 0)			// positive number of months ?
		return( this->sub_period(0, months, 0) ); // subtract months
	else				// negative number of months
		return( this->add_period(0, months * -1, 0) ); // add
}
 
 
DatasimDate DatasimDate::sub_years(long years)  const
/*
 *	this function will return a DatasimDate which is a number of years earlier
 *	than this DatasimDate. If 'years' is negative, the returned DatasimDate will be
 *	later than this DatasimDate. This DatasimDate itself wil not be changed.
 */
{
	if (years > 0)			// positive number of years ?
		return( this->sub_period(0, 0, years) ); // subtract years
	else				// negative number of years
		return( this->add_period(0, 0, years * -1) ); // add
}
 


long DatasimDate::difference(const DatasimDate& DatasimDate_2)  const
/*
 *	returns the difference in days (can be negative) between
 *	this DatasimDate and DatasimDate_2.
 */
{
	long dif;

	if (Julian_days >= DatasimDate_2.Julian_days)		// dif is positive
		dif = Julian_days - DatasimDate_2.Julian_days;	// calculate it
	else						// dif is negative
			// first calc positive difference (type = julTy).
			// then convert to long and make it negative.
		dif = (DatasimDate_2.Julian_days - Julian_days) * -1;
	return(dif);				// return signed difference
}

long DatasimDate::operator - (const DatasimDate& d)  const
{


	return difference(d);
}


ostream& operator << (ostream& os, const DatasimDate& dat)
{

	os << dat.ret_day() << "/" << dat.ret_month() << "/" << dat.ret_year();
	return os;
}
