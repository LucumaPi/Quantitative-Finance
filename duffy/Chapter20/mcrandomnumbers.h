//
//
//      MCRandomNumbers.h
//
//		Generating arrays of random numbers
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#ifndef MC_RANDOM_NUMBERS_H
#define MC_RANDOM_NUMBERS_H

#include "MCPath.h"
#include "NormalDist.h"

class Random
{
public:

    Random(unsigned long Dimensionality);

    inline unsigned long GetDimensionality() const;
	inline unsigned long GetSeed() const;

    virtual Random* clone() const=0;
    virtual void GenerateUniforms(MCPath& variates)=0;
    virtual void Skip(unsigned long numberOfPaths)=0;
    virtual void SetSeed(unsigned long Seed) =0;
    virtual void Reset()=0;

    virtual void GenerateNormals(MCPath& variates);
	//virtual void GenerateLogNormals(MCPath& variates);
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
    unsigned long Dimensionality;
	unsigned long Seed;
};

unsigned long Random::GetDimensionality() const
{
    return Dimensionality;
}

unsigned long Random::GetSeed() const
{
	return Seed;
}


#endif