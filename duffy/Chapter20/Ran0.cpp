//
//
//                       Ran0.cpp
//
//		Taken from Numerical Recipes in C++
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include <Ran0.h>


Ran0::Ran0(long Seed_, long a_, long m_, long q_, long r_) : Seed(Seed_), a(a_), m(m_), q(q_), r(r_)
{
    if (Seed ==0)
        Seed=1;
	if (a == 0)
		a = 16807;
	if (m == 0) 
		m = 2147483647;
	if(q==0)
		q = 127773;
	if(r==0)
		r = 2836;
}

  
void Ran0::SetSeed(long Seed_)
{
  Seed=Seed_;
  //necessary to insure that RNG does not only return zeroes
  if (Seed ==0)
        Seed=1;
}


double Ran0::GetOneRandomInteger()
{
    long k;
 
    k=Seed/q;
    
    Seed=a*(Seed-k*q)-r*k; 

    if (Seed < 0) 
        Seed += m;
	return Seed * 1/(1.0+m);
}
/*
RandomRan0::RandomRan0(unsigned long Dimensionality, unsigned long Seed)
:    Random(Dimensionality),
    MCNumberGen(Seed),
    InitialSeed(Seed)
{
}

Random* RandomRan0::clone() const
{
    return new RandomRan0(*this);   
}

void RandomRan0::GenerateUniforms(MCPath& variates)
{
    for (unsigned long j=0; j < GetDimensionality(); j++)
        variates[j] = MCNumberGen.GetOneRandomInteger();

}
    
void RandomRan0::Skip(unsigned long numberOfPaths)
{
    MCPath tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GenerateUniforms(tmp);
}

void RandomRan0::SetSeed(unsigned long Seed)
{
    InitialSeed = Seed;
    MCNumberGen.SetSeed(Seed);
}

void RandomRan0::Reset()
{
    MCNumberGen.SetSeed(InitialSeed);
}


void RandomRan0::ResetDimensionality(unsigned long NewDimensionality)
{
    Random::ResetDimensionality(NewDimensionality);
    MCNumberGen.SetSeed(InitialSeed);
}
*/