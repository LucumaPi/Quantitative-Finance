//
//
//                      Ran0.h
//
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005


#ifndef RAN0_H
#define RAN0_H
#include <MCRandomNumbers.h>
class Ran0
{
public:
    
    Ran0(long Seed = 1, long a = 16807, long m = 2147483647, long q = 127773, long r = 2836);

    double GetOneRandomInteger();
    void SetSeed(long Seed);

private:

    long Seed;
	long a;
	long m;
	long q;
	long r;

};

#endif
