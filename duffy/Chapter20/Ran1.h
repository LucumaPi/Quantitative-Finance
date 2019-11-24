//
//
//                      Ran1.h
//
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005


#ifndef RAN1_H
#define RAN1_H
#include <MCRandomNumbers.h>


class Ran1
{
public:
    
    Ran1(long Seed = 1, long a = 16807, long m = 2147483647, long q = 127773, long r = 2836, long ntab = 32);

    double GetOneRandomInteger();
    void SetSeed(long Seed);

private:

    long Seed;
	long a;
	long m;
	long q;
	long r;
	long ntab;
    long ndiv;
};


#endif
