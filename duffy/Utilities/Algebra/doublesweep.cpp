// doublesweep.cpp
//
// The Balayage method
//
// (C) Datasim Component Technology BV 2000
//
// 24.07.2000 S changed into AS - Array structure (JT)
// 2002-1-8 DD Remove namespace, improved array indexing
// 2002-4-8 DD Indexing improvements, improve usability
// 2006-1-9 DD Clean up + solve() member function

#ifndef DOUBLESWEEP_CPP
#define DOUBLESWEEP_CPP


#include "doublesweep.hpp"


template <class V, class I>
DoubleSweep<V,I>::DoubleSweep()
{
			// empty OK
}



template <class V, class I>
DoubleSweep<V,I>::DoubleSweep (const DoubleSweep<V,I>& s2)
{

			// empty OK
}



template <class V, class I>
DoubleSweep<V,I>::DoubleSweep(const Vector<V,I>& a, const Vector<V,I>& b,
								 const Vector<V,I>& c,
								 const Vector<V,I>& f, const V& bc_left,
								 const V& bc_right)
{

	aa = a;
	bb = b;
	cc = c;
	ff = f;

	left = bc_left;
	right = bc_right;
}


template <class V, class I>
DoubleSweep<V,I>::~DoubleSweep()
{
			// empty OK

}

template <class V, class I>
DoubleSweep<V,I>& DoubleSweep<V,I>::operator = (const DoubleSweep<V,I>& i2)
{
			// empty OK
}


template <class V, class I>
Vector<V,I> DoubleSweep<V,I>::result() const
{ // Code to actually create the solution to the tridiagonal system

	size_t N =  aa.Size() + 1;

	Vector<V,I> U( N + 1, 0 ); // start index = 0; this vector will 'contain' the result
	U[0] = left;
	U[N] = right;

	Vector<V,I> L(N, 0);	// [0, N-1]
	L[0] = 0.0;
	
	
	I j;
	for (j = L.MinIndex() + 1; j <=  L.MaxIndex(); j++ )
	{// L
		L[j] = ( -cc[j] ) / ( bb[j] + ( aa[j] *	L[j-I(1)] ) );
	}
	
	
	
	Vector<V,I> K(N, 0);	// [0, N-1]	
	K[0] = left;

	for (j = K.MinIndex() + 1; j <= K.MaxIndex(); j++ )
	{// K

		K[j] = ( ff[j] - ( aa[j] * K[j-I(1)] ) ) / ( bb[j] + ( aa[j] * L[j-I(1)] ) );
	}


	Vector<V,I> Solution(N-1, 1);

	for(j = N - 1; j >= 1; j-- )
	{// U

		U[j] = ( L[j] * U[j + 1] ) + K[j];

		Solution[j] = U[j];

	}
	
	return Solution;

}

template <class V, class I>
Vector<V,I> DoubleSweep<V,I>::solve() const
{

	return result();
}


#endif
