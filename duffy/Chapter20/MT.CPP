//
//
//                       MT.cpp
//
//		Taken from Matsumoto, see reference in MT.h
//
//		Author: J. Kienitz	       
//		Date:   17.08.2005

#include <MT.h>
#include <vector>
#include <cmath>

/* Tempering parameters */   
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

/*Initilization*/
#define MT_N 624
#define MT_M 397
#define MT_D 227               // Difference MT_N-MT_M
#define MATRIX_A 0x9908b0df    // constant vector a 
#define UPPER_MASK 0x80000000  // most significant w-r bits 
#define LOWER_MASK 0x7fffffff  // least significant r bits 

unsigned long MersenneTwister::mag01[2]={0x0, MATRIX_A};

MersenneTwister MT199937;

MersenneTwister::MersenneTwister(long Seed_ ) : Seed(Seed_), mt(new unsigned long[MT_N]), mti(MT_N)
{
    if (Seed <0)
        Seed=abs(Seed);
	for (int i=0; i < MT_N;i++){
		mt[i]=Seed & 0xffff0000;
		Seed = 69069 * Seed +1;
		mt[i] |= (Seed & 0xffff0000) >> 16;
		Seed = 69069 * Seed +1;
	}
}

  
void MersenneTwister::SetSeed(long Seed_)
{
  Seed=Seed_;
  if (Seed < 0)
	  Seed=abs(Seed);
}


double MersenneTwister::GetOneRandomInteger(unsigned long NthElement)
{
	
        unsigned long y;

    if (mti >= MT_N) { /* generate N words at one time */
        int kk;

        for (kk=0;kk<MT_D;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+MT_M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (;kk<MT_N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk-MT_D] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[MT_N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[MT_N-1] = mt[MT_M-1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }
  
    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);

	return ( ((double)y + 1.0) * 2.3283064359965952e-10 ); 
    // easily adapted to integer gen, just return y
}






