//
//
//                        MCQuasiRandomNumbers.h
//
//
//		Author: J. Kienitz	       
//		Date:   25.08.2005

#ifndef MC_QUASI_RANDOM_NUMBERS_H
#define MC_QUASI_RANDOM_NUMBERS_H

#include "MCPath.h"

class QuasiRandom
{
public:

    QuasiRandom(unsigned long Dimensionality);

    inline unsigned long GetDimensionality() const;
	inline unsigned long GetSeed() const;

    virtual QuasiRandom* clone() const=0;
    virtual void GenerateUniforms(MCPath& variates)=0;
    virtual void Skip(unsigned long numberOfPaths)=0;
    virtual void SetSeed(unsigned long Seed) =0;
    virtual void Reset()=0;

    virtual void GenerateNormals(MCPath& variates);
	virtual void GenerateLogNormals(MCPath& variates);
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
    unsigned long Dimensionality;
	unsigned long Seed;
};

unsigned long QuasiRandom::GetDimensionality() const
{
    return Dimensionality;
}

unsigned long QuasiRandom::GetSeed() const
{
	return Seed;
}

#endif