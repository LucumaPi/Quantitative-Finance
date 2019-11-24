// DateTime.hpp
//
// Class representing dates and times in one entity.
//
// (C) Datasim Education BV 2004
//                    

 
#ifndef DatasimDateTime_HXX
#define DatasimDateTime_HXX
 
#include <time.h>
#include "temporaltype.hpp"

#define OR ||
#define AND &&
 
enum DatasimDateTime_type {HR12, HR24};
 
typedef unsigned long	secTy;
static const unsigned long day_seconds = (24l * 60l * 60l);
 
class DatasimDateTime : public TemporalType
{
 private:
	secTy seconds;			// number of seconds from midnight

	secTy secs(long hours, long minutes, long seconds); // calc #seconds from midnight
	int hour_test(int hour);	// test validity of hour
	int min_test(int minute);	// test             minute
	int sec_test(int seconds);	// test		    seconds

 	void secs_to_DatasimDateTime(int& h, int& m, int& s, long* over = 0);
					// give time from seconds 
 
 public:
	// Constructors
	DatasimDateTime();			// default constructor=time today
	DatasimDateTime(const DatasimDateTime&);			// copy in initialization
	DatasimDateTime(secTy secs, long* over = 0); // constr time from number of secs after midnight

	int ret_hour();		// return hour of this DatasimDateTime
	int ret_minute();		// return minute (0..59) of DatasimDateTime
	int ret_second();		// return second (0..59) of DatasimDateTime
 

	bool operator==(DatasimDateTime DatasimDateTime_2);	// return TRUE if on the same time
	bool operator!=(DatasimDateTime DatasimDateTime_2);	// return TRUE if not on the same time
	bool operator>(DatasimDateTime DatasimDateTime_2);	// time is later than time_2
	bool operator<(DatasimDateTime DatasimDateTime_2);	// DatasimDateTime is earlier than DatasimDateTime_2
	bool operator>=(DatasimDateTime DatasimDateTime_2);	// DatasimDateTime is later than DatasimDateTime_2
	bool operator<=(DatasimDateTime DatasimDateTime_2);	// DatasimDateTime is earlier than DatasimDateTime_2
	DatasimDateTime& operator=(DatasimDateTime& DatasimDateTime_2); // copy
	DatasimDateTime operator+(DatasimDateTime DatasimDateTime_2); // add two DatasimDateTimes
	DatasimDateTime operator+(long seconds);
	DatasimDateTime operator-(DatasimDateTime DatasimDateTime_2);	// subtract DatasimDateTime_2 from this DatasimDateTime
	DatasimDateTime operator-(long seconds);	// subtract #seconds from this DatasimDateTime
	DatasimDateTime operator++();		// add 1 second to DatasimDateTime
	DatasimDateTime operator--();		// subtract one second from DatasimDateTime
	DatasimDateTime operator+=(DatasimDateTime DatasimDateTime_2);// add secs seconds to this DatasimDateTime
	DatasimDateTime operator+=(long secs);	// add secs seconds to this DatasimDateTime
	DatasimDateTime operator-=(DatasimDateTime DatasimDateTime_2);// subtract seconds from this DatasimDateTime
	DatasimDateTime operator-=(long secs);	// subtract seconds from this DatasimDateTime
	DatasimDateTime add_hours(long hours);	// return this DatasimDateTime + #hours
	DatasimDateTime add_minutes(long minutes);// return this DatasimDateTime + #minutes
	DatasimDateTime sub_hours(long hours);	// return this DatasimDateTime - #hours
	DatasimDateTime sub_minutes(long minutes);// return this DatasimDateTime - #minutes
	DatasimDateTime add_period(secTy secs, secTy mins = 0, secTy hours = 0);
	DatasimDateTime sub_period(secTy secs, secTy mins = 0, secTy hours = 0);
	void print() const;			// print the time
	void secs_to_dtime(int& h, int& m, int& s, long* over = 0) const;
					// give time from seconds 

};
 
#endif /* DatasimDateTime_HXX */
