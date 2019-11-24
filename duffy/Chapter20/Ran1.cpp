//
//
//                       Ran0.cpp
//
//		Taken from Numerical Recipes in C++
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include <Ran1.h>
#include <vector>



const double rnmx = (1.0-3.0e-8);

std::vector<double> iv(32);

static int iy=0;




Ran1::Ran1(long Seed_, long a_, long m_, long q_, long r_, long ntab_ ) : Seed(Seed_), a(a_), m(m_), q(q_), r(r_), ntab(ntab_)
{
    if (Seed >0)
        Seed=-1;
	if (a == 0)
        a = 16807;
	if (m == 0)
        m = 2147483647;
	if (q == 0)
        q = 127773;
	if (r == 0)
        r = 2836;
	if (ntab == 0)
        ntab = 32;
	ndiv = 1+(m-1)/ntab;

}

  
void Ran1::SetSeed(long Seed_)
{
  Seed=Seed_;
  //due to NRR C++
  if (Seed >0)
        Seed=-1;
}


double Ran1::GetOneRandomInteger()
{
	
    long j,k;
	double output;
	const double am=1.0/m;

	if(Seed <= 0 || !iy){
		if (-Seed < 1) Seed = 1;
		else Seed = -Seed;
		for(j=ntab+7;j>=0;j--){
			k=Seed/q;
			Seed=a*(Seed-k*q)-r*k;
			if(Seed < 0) Seed += m;
			if(j < ntab) iv[j]=Seed;
		}
		iy = iv[0];
	}

    k=Seed/q;
    
    Seed=a*(Seed-k*q)-r*k; 

    if (Seed < 0) 
        Seed += m;
	j=iy/ndiv;
	iy = iv[j];
	iv[j]=Seed;
	if((output=am*iy) > rnmx) return rnmx;
	else return output;

    //return Seed;
}

/*
RandomRan1::RandomRan1(unsigned long Dimensionality, unsigned long Seed)
:    Random(Dimensionality),
    MCNumberGen(Seed),
    InitialSeed(Seed)
{
}

Random* RandomRan1::clone() const
{
    return new RandomRan1(*this);   
}

void RandomRan1::GenerateUniforms(MCPath& variates)
{
    for (unsigned long j=0; j < GetDimensionality(); j++)
        variates[j] = MCNumberGen.GetOneRandomInteger();	
}
    
void RandomRan1::Skip(unsigned long numberOfPaths)
{
    MCPath tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GenerateUniforms(tmp);
}

void RandomRan1::SetSeed(unsigned long Seed)
{
    InitialSeed = Seed;
    MCNumberGen.SetSeed(Seed);
}

void RandomRan1::Reset()
{
    MCNumberGen.SetSeed(InitialSeed);
}


void RandomRan1::ResetDimensionality(unsigned long NewDimensionality)
{
    Random::ResetDimensionality(NewDimensionality);
    MCNumberGen.SetSeed(InitialSeed);
}

*/