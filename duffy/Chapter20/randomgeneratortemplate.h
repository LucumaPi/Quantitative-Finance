#ifndef RANDOMGENERATORTEMPLATE_H
#define RANDOMGENERATORTEMPLATE_H

#include "MCRandomNumbers.h"


template <class R>
	class RandGen : public Random
{
public:

    RandGen(unsigned long Dimensionality, unsigned long Seed=1);

    virtual Random* clone() const;    
    virtual void GenerateUniforms(MCPath& variates);    
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:

    R MCNumberGen;
    unsigned long InitialSeed;
};

template <class R> RandGen<R>::RandGen(unsigned long Dimensionality, unsigned long Seed)
:    Random(Dimensionality),
     MCNumberGen(Seed, Dimensionality),
     InitialSeed(Seed)
{
}

template <class R> Random* RandGen<R>::clone() const
{
    return new RandGen<R>(*this);   
}

template <class R> void RandGen<R>::GenerateUniforms(MCPath& variates)
{
    for (unsigned long j=0; j < GetDimensionality(); j++)
        variates[j] = MCNumberGen.GetOneRandomInteger(j);	
}
    
template <class R> void RandGen<R>::Skip(unsigned long numberOfPaths)
{
    MCPath tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GenerateUniforms(tmp);
}

template <class R> void RandGen<R>::SetSeed(unsigned long Seed)
{
    InitialSeed = Seed;
    MCNumberGen.SetSeed(Seed);
}

template <class R> void RandGen<R>::Reset()
{
    MCNumberGen.SetSeed(InitialSeed);
}


template <class R> void RandGen<R>::ResetDimensionality(unsigned long NewDimensionality)
{
    Random::ResetDimensionality(NewDimensionality);
    MCNumberGen.SetSeed(InitialSeed);
}

#endif