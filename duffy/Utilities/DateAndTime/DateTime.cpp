// DateTime.cpp
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
//  2005-4-15 DD print() function and set_to_dtime

#include "DateTime.hpp"
#include <stdio.h>

void DatasimDateTime::secs_to_DatasimDateTime(int& hour, int& minute, int& second, long* over)
/*
 *	calculate the time of the day (hour, minute, second) from
 *	the given seconds (which is the number of seconds past midnight).
 *	If the number of seconds is more than seconds in one day, the
 *	parameter 'over' will point to that number of days (seconds div 
 *	day_seconds) if the parameter has been passed (it is a default
 *	argument, default = 0), otherwise it will remain 0 (null pointer).
 */
{
printf("seconds = %lu\n", seconds);
	if (over != 0)			// parameter has been passed
		*over = seconds / day_seconds;	// number of days in seconds
//	seconds %= day_seconds;		// rest seconds
printf("seconds after days subtr. = %lu\n", seconds);
	hour = seconds / 3600;		// calculate hours from midnight
	int h = seconds % 3600;		// rest
	minute = h / 60;		// calc. minutes after 'hour'
	second = h % 60;		// calc seconds after 'minute'
printf("hour = %d\nminute = %d\nsecond = %d\n", hour, minute, second);
}

secTy DatasimDateTime::secs(long hours, long minutes, long secos)
/*
 *	return the number of seconds after midnight (12:00 AM) from
 *	hours, minutes and seconds. If one of them is < 0 then 
 *	return 0. (=midnight). The number of hours, minutes and seconds
 *	may be any value (> 0).
 */
{
	if (hours < 0 OR minutes < 0 OR secos < 0)
		return(0);
	else {
		minutes += (secos / 60);	// #minutes in seconds
		secos %= 60;			// rest seconds
		hours += (minutes / 60);	// #hours in minutes
		minutes %= 60;			// rest minutes
		hours %= 24;			// discard day-limit
		return(hours * 60l * 60l + minutes * 60l + secos);// total
					// number of seconds after 12:00
	}
}
 
 
int DatasimDateTime::hour_test(int hour)
/*
 *	test if hours has a valid value. It must be between 0 and 23, 
 *	(so 24 is an invalid value). An invalid hour will give a returnvalue
 *	of -1, a valid value will be returned.
 */
{
	if (hour > 23 OR hour < 0)
		return(-1);
	else 
		return(hour);
}
 
 
 
int DatasimDateTime::min_test(int minutes)
/*
 *	test if minutes has a valid value. It must be between 0 and 59, 
 *	(so 60 is an invalid value). An invalid value will give a returnvalue
 *	of -1, a valid value will be returned.
 */
{
        if (minutes > 59 OR minutes < 0)
			return(-1);
		else
			return(minutes);
}
 
 
int DatasimDateTime::sec_test(int secos)
/*
 *	test if seconds has a valid value. It must be between 0 and 59, 
 *	(so 60 is an invalid value). An invalid value will give a returnvalue
 *	of -1, a valid value will be returned.
 */
{
	if (secos > 59 OR secos < 0)
		return(-1);
	else
		return(secos);
}
 
 
DatasimDateTime::DatasimDateTime(secTy secs, long* over)
/*
 *	construct a time from a number of seconds. If the number of 
 *	seconds passes a day-limit and the default argument '*over' has
 *	been passed, *over will be set to the number of days past.
 */
{
	if (secs >= day_seconds AND over != 0) 	// past day-limit
						// and par. '*over' passed
		*over = secs / day_seconds;	// #days past
	secs %= day_seconds;			// rest of seconds
	seconds = secs;
}
 
DatasimDateTime::DatasimDateTime(const DatasimDateTime& DatasimDateTime_2)
/*
 *	this constructor is for the copy in initialization. It is not
 *	really necessary to declare this one because a bitwise copy (before
 *	2.00) has the same effect.
 */
{
	seconds = DatasimDateTime_2.seconds;
}
 
 
DatasimDateTime::DatasimDateTime()
/*
 *	default constructor. Gives the time at the moment of creation.
 *	because this function uses ANSI structures and function, it 
 *	should be machine independant.
 */
{
        time_t local_time;              // type to hold time
        struct tm *t_ptr;               // struct to contain time, date etc
 
        local_time = time(NULL);        // get time (and date) from system
        t_ptr = localtime(&local_time); // convert to struct 
        int hour_t = hour_test(t_ptr->tm_hour);	// test hour.
        int min_t = min_test(t_ptr->tm_min);	// test minute
        int sec_t = sec_test(t_ptr->tm_sec);	// test second
        seconds = secs(hour_t, min_t, sec_t);	// cal. seconds from midnight
}
 
 
 

 
int DatasimDateTime::ret_hour()
/*
 *	return the hour of the day from this DatasimDateTime.
 */
{
	int h, m, s;		// hour, minute and seconds
	secs_to_DatasimDateTime(h, m, s); // get hour,minute and seconds of day
	return(h);		// return hour of day
}
 
 
int DatasimDateTime::ret_minute()
/*
 *	return the minute (0..59) past last hour from this DatasimDateTime.
 */
{
	int h, m, s;		// hour, minute and seconds
	secs_to_DatasimDateTime(h, m, s); // get hour,minute and seconds of day
	return(m);		// return minute
}
 
 
int DatasimDateTime::ret_second()
/*
 *	return the second (0..59) past last minute from this DatasimDateTime.
 */
{
	int h, m, s;		// hour, minute and seconds
	secs_to_DatasimDateTime(h, m, s); // get hour,minute and seconds of day
	return(s);		// return second
}
 
 

 
bool DatasimDateTime::operator==(DatasimDateTime DatasimDateTime_2)
/*
 *	compare two DatasimDateTimes. Return true if they are on the same time, 
 *	else return false. They need not be the same objects.
 */
{
	if (seconds == DatasimDateTime_2.seconds)
		return(true);
	else
		return(false);
};
		
 
bool DatasimDateTime::operator!=(DatasimDateTime DatasimDateTime_2)
/*
 *	compare two DatasimDateTimes. Return true if they are not on the same time, 
 *	else return false. They need not be the same objects.
 */
{
	if (seconds != DatasimDateTime_2.seconds)
		return(true);
	else
		return(false);
}
 
 
bool DatasimDateTime::operator>(DatasimDateTime DatasimDateTime_2)
/*
 *	if this DatasimDateTime is later than DatasimDateTime_2, return true, else return false.
 */
{
	if (seconds > DatasimDateTime_2.seconds)
		return(true);
	else
		return(false);
}
 
bool DatasimDateTime::operator<(DatasimDateTime DatasimDateTime_2)
/*
 *	if this DatasimDateTime is earlier than DatasimDateTime_2, return true, else return false.
 */
{
	if (seconds < DatasimDateTime_2.seconds)
		return(true);
	else
		return(false);
}
 
 
bool DatasimDateTime::operator>=(DatasimDateTime DatasimDateTime_2)
/*
 *	if DatasimDateTime_2 is earlier than this DatasimDateTime return true, else return false.
 */
{
	if (seconds >= DatasimDateTime_2.seconds)
		return(true);
	else
		return(false);
}
 
 
bool DatasimDateTime::operator<=(DatasimDateTime DatasimDateTime_2)
/*
 *	if DatasimDateTime_2 is later than this DatasimDateTime return true, else return false.
 */
{
	if (seconds <= DatasimDateTime_2.seconds)
		return(true);
	else
		return(false);
}
 
 
DatasimDateTime DatasimDateTime::operator++()
/*
 *	add 1 second to this DatasimDateTime and return it. Discard the overflow
 *	fi there is one.
 */
{
	seconds++;				// one second later
	seconds %= day_seconds;			// discard overflow
	return(*this);				// return second later
}
 
 
DatasimDateTime DatasimDateTime::operator--()
/*
 *	subtract 1 second from this DatasimDateTime and return it. Discard an 
 *	underflow if there is one.
 */
{
	seconds = seconds + day_seconds - 1;	// one second earlier
	seconds %= day_seconds;			// discard underflow
	return(*this);				// return second earlier
}
 
 
DatasimDateTime DatasimDateTime::operator+(DatasimDateTime t2)
/*
 *	add two DatasimDateTimes. If the resulting time passes a day-limit, discard
 *	the overflow. return the added time.
 */
{
	secTy tot_sec = seconds + t2.seconds;	// total # seconds
	tot_sec %= day_seconds;			// discard overflow
	DatasimDateTime t(tot_sec);			// construct DatasimDateTime from rest
	return(t);				// return added time
}
 
 
DatasimDateTime DatasimDateTime::operator+(long secos)
/*
 *	return this DatasimDateTime + #seconds. If the resulting time passes a day-limit
 *	discard the overflow. #seconds May be negative.
 */
{
	DatasimDateTime tmp;
	if (secos >= 0)
		tmp = *this + DatasimDateTime(secos);	// construct DatasimDateTime, discard ovf
	else 
		tmp = *this + DatasimDateTime(secos * -1); // construct DatasimDateTime
	return(tmp);				// return DatasimDateTime
}
 
 
DatasimDateTime DatasimDateTime::operator-(DatasimDateTime t2)
/*
 *	subtract DatasimDateTime_2 from this DatasimDateTime. If the resulting time passes 
 *	a day-limit, discard the underflow. return the new time.
 */
{
	DatasimDateTime tmp;				// temporary DatasimDateTime
	if (*this >= t2)			// result will be pos
		tmp = DatasimDateTime(seconds - t2.seconds); // subtract seconds and constr.
	else 					// result will be negative
		tmp = DatasimDateTime(day_seconds - t2.seconds + seconds);
						// make positive and construct
	return(tmp);				// return added time
}
 
 
DatasimDateTime DatasimDateTime::operator-(long nr_secs)
/*
 *	return this DatasimDateTime - #seconds. If the resulting time passes a day-limit
 *	discard the underflow. #seconds May be negative.
 */
{
	DatasimDateTime tmp;
	if (nr_secs >= 0)			// #seconds is positive
		tmp = *this - DatasimDateTime(nr_secs);	// construct DatasimDateTime, discard ovf
	else 					// #seconds is negative
		tmp = *this - DatasimDateTime(nr_secs * -1); // construct DatasimDateTime
	return(tmp);				// return DatasimDateTime
}
 
 
DatasimDateTime DatasimDateTime::operator+=(long secos)
/*
 *	add a number of seconds to this DatasimDateTime and return it. If the
 *	DatasimDateTime passes a time limit, discard the overflow. The number
 *	of seconds may be positive or negative.
 */
{
	*this = *this + secos;	// call operator+, add seconds
	return(*this);			// return new this DatasimDateTime
}
 
 
DatasimDateTime DatasimDateTime::operator+=(DatasimDateTime DatasimDateTime_2)
/*
 *	add DatasimDateTime_2 to this DatasimDateTime and return it. If the 
 *	DatasimDateTime passes a day-limit, the overflow is discarded.
 */
{
	*this = *this + DatasimDateTime_2;	// add DatasimDateTime_2 to this DatasimDateTime
	return(*this);			// return it
}
 
 
DatasimDateTime DatasimDateTime::operator-=(DatasimDateTime DatasimDateTime_2)
/*
 *	subtract DatasimDateTime_2 from this DatasimDateTime (so this DatasimDateTime will be changed)
 *	and return it. If the DatasimDateTime passes day-limit, the overflow will
 *	be discarded.
 */
{
	*this = *this - DatasimDateTime_2;	// call operator-, subtract time
	return(*this);
}
 
 
DatasimDateTime DatasimDateTime::operator-=(long secos)
/*
 *	subtract a number of seconds from this DatasimDateTime (so this DatasimDateTime will
 *	be changed) and return it. when the time passes a day-limit, the
 *	underflow will be discarded. The number of secons may be positive
 *	or negative.
 */
 {
	*this = *this - secos;	// call operator-, add seconds
	return(*this);			// return new this DatasimDateTime
}
 
 
DatasimDateTime& DatasimDateTime::operator=(DatasimDateTime& DatasimDateTime_2)
/*
 *	assign DatasimDateTime_2 to this DatasimDateTime. Check ik they are the same objects
 *	(this is not really necessary) and return the new DatasimDateTime (a reference).
 */
{
	if (this != &DatasimDateTime_2)			// beware of t = t;
		seconds = DatasimDateTime_2.seconds;
	return(*this);				// for multiple assignment
}
 
 

 
DatasimDateTime DatasimDateTime::add_period(secTy secos, secTy mins, secTy hours)
/*
 *	add a period of time to this DatasimDateTime. The number of seconds can be
 *	any value (may be > 59), the number of minutes can be any value
 *	(may be > 59) and also the number of hours can be any value (may
 *	be > 23). If a day-limit is passed, the overflow will be discarded.
 */
{
	
	DatasimDateTime tmp = DatasimDateTime( secs(secos, mins, hours) ); // construct DatasimDateTime
	tmp = *this + tmp;			// add DatasimDateTimes
	return(tmp);				// return new time
}
 
 
DatasimDateTime DatasimDateTime::sub_period(secTy secos, secTy mins, secTy hours)
/*
 *	subtract a period of time from this DatasimDateTime. The number of seconds can be
 *	any value (may be > 59), the number of minutes can be any value
 *	(may be > 59) and also the number of hours can be any value (may
 *	be > 23). If a day-limit is passed, the underrflow will be discarded.
 */
{
	DatasimDateTime tmp = DatasimDateTime( secs(secos, mins, hours) ); // construct DatasimDateTime
	tmp = *this - tmp;			// subtract DatasimDateTime
	return(tmp);				// return new time
}
	
	
DatasimDateTime DatasimDateTime::add_hours(long hours)
/*
 *	return a number of hours added to this DatasimDateTime. If the DatasimDateTime passes
 *	a day-limit, the overflow will be discarded. The number of hours
 *	may be positive or negative.
 */
{ 
	DatasimDateTime tmp;			// for temporary result
	if (hours >= 0)			// add positive #hours
		tmp = add_period(0, 0, hours);	// add hours
	else				// add negative #hours
		tmp = sub_period(0, 0, hours * -1); // subtract hours
	return(tmp);			// return result
}
 
 
DatasimDateTime DatasimDateTime::sub_hours(long hours)
/*
 *	return a number of hours subtracted from this DatasimDateTime. If the DatasimDateTime 
 *	passes a day-limit, the overflow will be discarded. The number of hours
 *	may be positive or negative.
 */
{ 
	DatasimDateTime tmp;			// for temporary result
	if (hours >= 0)			// subtract positive #hours
		tmp = sub_period(0, 0, hours);	// subtract #hours
	else				// subtract negative #hours
		tmp = add_period(0, 0, hours * -1); // add #hours
	return(tmp);			// return result
}
 
 
DatasimDateTime DatasimDateTime::add_minutes(long minutes)
/*
 *	return a number of minutes added to this DatasimDateTime. If the DatasimDateTime passes
 *	a day-limit, the overflow will be discarded. The number of minutes
 *	may be positive or negative.
 */
{ 
	DatasimDateTime tmp;			// for temporary result
	if (minutes >= 0)			// add positive #minutes
		tmp = add_period(0, minutes);	// add #minutes
	else				// add negative #minutes
		tmp = sub_period(0, minutes * -1); // subtract minutes
	return(tmp);			// return result
}
 
 
DatasimDateTime DatasimDateTime::sub_minutes(long minutes)
/*
 *	return a number of minutes subtracted from this DatasimDateTime. If the DatasimDateTime 
 *	passes a day-limit, the overflow will be discarded. The number of
 *	minutes may be positive or negative.
 */
{ 
	DatasimDateTime tmp;				// for temporary result
	if (minutes >= 0)			// subtract positive #minutes
		tmp = sub_period(0, minutes); // subtract #minutes
	else					// subtract negative #minutes
		tmp = add_period(0, minutes * -1); // subtract #minutes
	return(tmp);				// return result
}

void DatasimDateTime::print() const
{
	// dtime::delim = ':';
	char delim = ':';
	int hour = 0, min = 0, sec = 0;
	secs_to_dtime(hour, min, sec);
	printf("%02d%c%02d%c%02d", hour, delim, min, delim, sec);
}

void DatasimDateTime::secs_to_dtime(int& hour, int& minute, int& second, long* over) const
/*
 *	calculate the time of the day (hour, minute, second) from
 *	the given seconds (which is the number of seconds past midnight).
 *	If the number of seconds is more than seconds in one day, the
 *	parameter 'over' will point to that number of days (seconds div 
 *	day_seconds) if the parameter has been passed (it is a default
 *	argument, default = 0), otherwise it will remain 0 (null pointer).
 */
{
//printf("seconds = %lu\n", seconds);
	if (over != 0)			// parameter has been passed
		*over = seconds / day_seconds;	// number of days in seconds
//	seconds %= day_seconds;		// rest seconds
//printf("seconds after days subtr. = %lu\n", seconds);
	hour = seconds / 3600;		// calculate hours from midnight
	int h = seconds % 3600;		// rest
	minute = h / 60;		// calc. minutes after 'hour'
	second = h % 60;		// calc seconds after 'minute'
//printf("hour = %d\nminute = %d\nsecond = %d\n", hour, minute, second);
}