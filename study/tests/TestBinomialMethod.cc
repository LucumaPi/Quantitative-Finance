// testBinomialMethod.cpp
//
// Testing the binomial method
//
// (C) Datasim Education BV 2003-2005
//

#include <duffy/BinomialMethod.hh>
#include <duffy/Lattice.hh>
#include "../src/PayoffNamespace.cc"

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

int main()
{
	using namespace PayoffNamespace;

	K = 10.0;
	type = 1; // Euro

	using namespace CallPayoff;

	BinomialMethod bn (OptPayoff);

	return 0;
}