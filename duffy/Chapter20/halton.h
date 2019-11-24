//
//
//       Halton.h
//
//
//		Halton sequences
//
//		Author: J. Kienitz	       
//		Date:   25.03.2006


#ifndef Halton_H
#define Halton_H
#include "MCRandomNumbers.h"
#include <vector>

class Halton
{
public:
    
    Halton(long Seed = 1, long Dim = 1);

	double GetOneRandomInteger(unsigned long NthElement);
    void SetSeed(long Seed);
	void SetDim(long Dim);
	void SetBase(long Dim);
	unsigned long GetSeed();
	unsigned long GetDim();

private:

    long Seed;
	long Dim;
	mutable std::vector<int> base;
	static int primenumbers[1500];
};

#endif
