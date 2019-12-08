// latticemechanisms.cpp
//
// Testing the Latice class (basis for binomial and trinomial
// trees)
//
// In this version we have one class for both binomial and trinomial
// trees.
//
// (C) Datasim Education BV 2003-2006
//

#ifndef LatticeMechanisms_CPP
#define LatticeMechanisms_CPP

#include <duffy/Lattice.hh>
#include <duffy/Matrix.hh>
#include <duffy/MatrixMechanisms.hh>

#include <iostream>

template <class V, class I, int NumberNodes> void print(const Lattice<V, I, NumberNodes>& source)
{
	for (I j = source.MinIndex(); j <= source.MaxIndex(); j++)
	{

		std::cout << "\nBranch Number " << j << ": [";
		for (I i = source[j].MinIndex(); i <= source[j].MaxIndex(); i++)
		{
			std::cout << source[j][i] << ", ";
		}
		std::cout << "]";
	}
}
#endif