//
//
//                      MCRandomNumberGenerator.cpp
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include "MCRandomNumbers.h"
//#include "NormalDistribution.h" DD
#include "NormalDist.h"
#include <cstdlib>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

//Generate Standard Normals by Inverse Method
void MCRandomNumber::GenerateNormals(MCPath& variates)
{
    GenerateUniforms(variates);

    for (unsigned long i=0; i < Dimensionality; i++)
    {
        double x=variates[i];
        variates[i] = InverseCumulativeNormal(x);    
    }
}

//Generate LogNormals by Inverse Method
void MCRandomNumber::GenerateLogNormals(MCPath& variates)
{
    GenerateUniforms(variates);

    for (unsigned long i=0; i < Dimensionality; i++)
    {
        double x=variates[i];
        variates[i] = exp(InverseCumulativeNormal(x));    
    }
}

void MCRandomNumber::ResetDimensionality(unsigned long NewDimensionality)
{
    Dimensionality = NewDimensionality;
}


MCRandomNumber::RandomBase(unsigned long Dimensionality_)
: Dimensionality(Dimensionality_)
{
}

MCRandomNumber(unsigned long Dimensionality, unsigned long Seed)
:    RandomBase(Dimensionality),
     MCNumberGen(Seed),
     InitialSeed(Seed)
{
    Reciprocal = 1/(1.0+MCNumberGen.Max());
}

RandomBase* MCRandomNumber::clone() const
{
    return new MCRandomNumber(*this);   
}

void MCRandomNumber::GenerateUniforms(MCPath& variates)
{
    for (unsigned long j=0; j < GetDimensionality(); j++)
        variates[j] = MCNumberGen.GetOneRandomInteger();	
}
    
void MCRandomNumber::Skip(unsigned long numberOfPaths)
{
    MCPath tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GenerateUniforms(tmp);
}

void MCRandomNumber::SetSeed(unsigned long Seed)
{
    InitialSeed = Seed;
    MCNumberGen.SetSeed(Seed);
}

void MCRandomNumber::Reset()
{
    MCNumberGen.SetSeed(InitialSeed);
}

