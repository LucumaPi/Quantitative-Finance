//
//
//                      MCRandomNumbers.cpp
//		Author: J. Kienitz	       
//		Date:   25.05.2005
/*

Could be realized as a template to which one puts in a random number generator
*/

#include "MCRandomNumbers.h"
#include "NormalDist.h"
#include <cstdlib>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

//Generate Standard Normals by Inverse Method
void Random::GenerateNormals(MCPath& variates)
{
    GenerateUniforms(variates);

    for (unsigned long i=0; i < Dimensionality; i++)
    {
        double x=variates[i];
        variates[i] = InverseCumulativeNormal(x);    
    }
}

void Random::ResetDimensionality(unsigned long NewDimensionality)
{
    Dimensionality = NewDimensionality;
}

Random::Random(unsigned long Dimensionality_)
: Dimensionality(Dimensionality_)
{
}

