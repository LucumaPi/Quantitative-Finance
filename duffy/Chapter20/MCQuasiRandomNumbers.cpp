//
//
//                      MCQuasiRandomNumbers.cpp
//		Author: J. Kienitz	       
//		Date:   25.08.2005
/*

Could be realized as a template to which one puts in a random number generator

*/
#include "MCQuasiRandomNumbers.h"
#include "NormalDist.h"
#include <cstdlib>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

//Generate Standard Normals by Inverse Method
void QuasiRandom::GenerateNormals(MCPath& variates)
{
    GenerateUniforms(variates);

    for (unsigned long i=0; i < Dimensionality; i++)
    {
        double x=variates[i];
        variates[i] = InverseCumulativeNormal(x);    
    }
}

//Generate LogNormals by Inverse Method
void QuasiRandom::GenerateLogNormals(MCPath& variates)
{
    GenerateUniforms(variates);

    for (unsigned long i=0; i < Dimensionality; i++)
    {
        double x=variates[i];
        variates[i] = exp(InverseCumulativeNormal(x));    
    }
}

void QuasiRandom::ResetDimensionality(unsigned long NewDimensionality)
{
    Dimensionality = NewDimensionality;
}

QuasiRandom::QuasiRandom(unsigned long Dimensionality_)
: Dimensionality(Dimensionality_)
{
}

