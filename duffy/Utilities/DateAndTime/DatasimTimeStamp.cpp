#include "tstamp.hxx"
#include <stdio.h>

void tstamp::print()
{
	stamp_date.print();
	putchar(' ');
	stamp_time.print();
}