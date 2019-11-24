//
//
//      CongRNG.h
//
//      Congruential Random Number Generators
//
//		Author: J. Kienitz	       
//		Date:   25.03.2006


#ifndef CONGRNG_H
#define CONGRNG_H
#include "MCRandomNumbers.h"

class Ran0
{
public:
    
    Ran0(long Seed = 1, long Dim = 1, long a = 16807, long m = 2147483647, long q = 127773, long r = 2836);

    double GetOneRandomInteger(unsigned long NthElement);
    void SetSeed(long Seed);

private:

    long Seed;
	long Dim;
	long a;
	long m;
	long q;
	long r;

};

class Ran1
{
public:
    
    Ran1(long Seed = 1, long Dim = 1, long a = 16807, long m = 2147483647, long q = 127773, long r = 2836, long ntab = 32);

    double GetOneRandomInteger(unsigned long NthElement);
    void SetSeed(long Seed);

private:

    long Seed;
	long Dim;
	long a;
	long m;
	long q;
	long r;
	long ntab;
    long ndiv;
};

#endif