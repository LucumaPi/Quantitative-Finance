
#include "date.hxx"
#include "dtime.hxx"

#ifndef TSTAMP.HXX
#define TSTAMP.HXX

class tstamp {
 private:
	date stamp_date;		// timestamp date
	dtime stamp_time;		// timestamp time

 public:
	tstamp(void):stamp_date(), stamp_time(){}; // construct a timestamp with 
					// date and time from system (now)
	void print();			// print timestamp
};

#endif
