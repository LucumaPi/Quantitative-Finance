// Mt.h
//
// Random number generation by Mersenne Twister.
//
#ifndef MT_H
#define MT_H

#include "MCRandomNumbers.h"


class MersenneTwister
{
public:
    //constructor
    MersenneTwister(long Seed = 4357);
	
	//elements
    double GetOneRandomInteger(unsigned long NthElement);
    void SetSeed(long Seed);


private:

    long Seed;
	int mti;
	unsigned long* mt;
	static unsigned long mag01[2];
};




/*
Random number generators: uniform.

Mersenne Twister MT19937. Minimal rewrite to C++ of a
<a href="http://www.math.keio.ac.jp/~nisimura/random/real2/mt19932-2.c">
A C-program for MT19937</a> by Makoto
<a href="http://www.math.keio.ac.jp/matumoto/emt.html">Matsumoto</a>
and  Takuji Nishimura. 
License and copyright statement at the bottom of the file  MersenneTwister.h.



/* A C-program for MT19937: Real number version((0,1)-interval) */
/* (2001/9/28)                                                  */
/*   genrand() generates one pseudorandom real number (double)  */
/* which is uniformly distributed on (0,1)-interval, for each   */
/* call. sgenrand(seed) sets initial values to the working area */
/* of 624 words. Before genrand(), sgenrand(seed) must be       */
/* called once. (seed is any 32-bit integer.)                   */
/* Integer generator is obtained by modifying two lines.        */
/*   Coded by Takuji Nishimura, considering the suggestions by  */
/* Topher Cooper and Marc Rieffel in July-Aug. 1997.            */

/* This library is free software; you can redistribute it and/or   */
/* modify it under the terms of the GNU Library General Public     */
/* License as published by the Free Software Foundation; either    */
/* version 2 of the License, or (at your option) any later         */
/* version.                                                        */
/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            */
/* See the GNU Library General Public License for more details.    */
/* You should have received a copy of the GNU Library General      */
/* Public License along with this library; if not, write to the    */
/* Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   */ 
/* 02111-1307  USA                                                 */

/* Copyright (C) 1997, 1999, 2001                                  */
/*    Makoto Matsumoto and  Takuji Nishimura.                      */
/*                                                                 */
/* Any feedback is very welcome. For any question, comments,       */
/* see http://www.math.keio.ac.jp/matumoto/emt.html or email       */
/* matumoto@math.keio.ac.jp                                        */

/* REFERENCE                                                       */
/* M. Matsumoto and T. Nishimura,                                  */
/* "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform  */
/* Pseudo-Random Number Generator",                                */
/* ACM Transactions on Modeling and Computer Simulation,           */
/* Vol. 8, No. 1, January 1998, pp 3--30.                          */

#endif