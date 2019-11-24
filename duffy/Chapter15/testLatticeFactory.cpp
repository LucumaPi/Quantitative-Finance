// testLatticeFactory.cpp
//

#include "LatticeFactory.hpp"
#include "binomialmethod.hpp"

#include "Option.hpp"

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
		using namespace Option;

		U = 105.0;		// Later use Property Sets in NS
		K = 100.0;
		T = 0.5;
		r = 0.10;
		sig = 0.36;
		b = 0.0;
		
		int N = 100;
		double k = T / double(N);

		//LatticeFactory* lf = new CRRFactory(sig,r,k,T);
		LatticeFactory* lf = new JRFactory(sig,r,k,T);

		// Forward Induction
		double S = 10.0;
		Lattice<double, int, 2> lattice = lf -> createLattice(S);
		print(lattice);

		// Backward Induction
		BinomialMethod bn (payoffCall);
		bn.buildLattice();
		bn.modifyLattice();

		bn.calcRHS();

		cout << "\n **Price: " << bn.getPrice() << endl;

		return 0;
}