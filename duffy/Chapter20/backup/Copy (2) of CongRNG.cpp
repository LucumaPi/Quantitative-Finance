//
//
//                  Congruential Random Number Generator
//                                 Ran0.cpp
//
//		Taken from Numerical Recipes in C++
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include <CongRNG.h>
#include <vector>


Ran0::Ran0(long Seed_, long Dim_, long a_, long m_, long q_, long r_) : Seed(Seed_), a(a_), m(m_), q(q_), r(r_)
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


double Ran0::GetOneRandomInteger(unsigned long NthElement)
{
    long k;
 
    k=Seed/q;
    
    Seed=a*(Seed-k*q)-r*k; 

    if (Seed < 0) 
        Seed += m;
	return Seed * 1/(1.0+m);
}


// Ran1

const double rnmx = (1.0-3.0e-8);

std::vector<double> iv(32);

static int iy=0;




Ran1::Ran1(long Seed_, long Dim_, long a_, long m_, long q_, long r_, long ntab_ ) : Seed(Seed_), a(a_), m(m_), q(q_), r(r_), ntab(ntab_)
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


double Ran1::GetOneRandomInteger(unsigned long NthElement)
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
}

