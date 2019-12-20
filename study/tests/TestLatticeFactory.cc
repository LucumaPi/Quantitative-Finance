// testLatticeFactory.cpp
//

#include <duffy/LatticeFactory.hh>
#include <duffy/BinomialMethod.hh>
#include <duffy/Option.hh>

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
		using namespace Option;

		double U = 105.0;		// Later use Property Sets in NS
		double K = 100.0;
		double T = 0.5;
		double r = 0.10;
		double sig = 0.36;
		double b = 0.0;
		
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

		std::cout << "\n **Price: " << bn.getPrice() << std::endl;

		return 0;
}