// testBinomialMethod.cpp
//
// Testing the binomial method
//
// (C) Datasim Education BV 2003-2005
//

#include "binomialmethod.hpp"
#include "lattice.cpp"
#include "PayoffNamespace.cpp"

#include <iostream>
using namespace std;


template <class V, class I, int NumberNodes> void print(const Lattice<V, I, NumberNodes>& source)
{
	
	for (I j = source.MinIndex(); j <= source.MaxIndex(); j++)
	{

		cout << "\nBranch Number " << j << ": [";
		for (I i = source[j].MinIndex(); i <= source[j].MaxIndex(); i++)
		{
			cout << source[j][i] << ", ";
	
		}

		cout << "]";
			
	}

}

int main()
{
	using namespace PayoffNamespace;

	K = 10.0;
	type = 1; // Euro

	using namespace CallPayoff;

	BinomialMethod bn (OptPayoff);

	return 0;
}
