// TestLattice.cpp
//
// Testing the Latice class (basis for binomial and trinomial
// trees)
//
// In this version we have one class for both binomial and trinomial
// trees.
//
//	2005-1-5 DD Using namespaces
//	2006-3-10 DD new code for new C++ book
//
// (C) Datasim Education BV 2003-2006
//

#include <duffy/Lattice.hh>
#include "../src/TestLatticeNamespace.cc" // The beginnings of a class
#include <iostream>
#include <cmath>

template <class V, class I> Vector<V,I> CallPayOff(const V& K, const Vector<V,I>& StockArr)
{

		V tmp;

		Vector<V,I> result (StockArr.Size(), StockArr.MinIndex());

		for (I i = StockArr.MinIndex(); i <= StockArr.MaxIndex(); i++)
		{
			result[i] = 0.0;
			tmp = StockArr[i] - K;
			if (tmp > 0.0)
				result[i] = tmp;
		}

		return result;
}

template <class V, class I> Vector<V,I> PutPayOff(const V& K, const Vector<V,I>& StockArr)
{

		V tmp;

		Vector<V,I> result (StockArr.Size(), StockArr.MinIndex());

		for (I i = StockArr.MinIndex(); i <= StockArr.MaxIndex(); i++)
		{
			result[i] = 0.0;
			tmp = K - StockArr[i];
			if (tmp > 0.0)
				result[i] = tmp;
		}

		return result;
}


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
	std::cout << "Forward sweep, Wilmott, Student Edition p. 193\n";

	int depth;
	std::cout << "How many subdivisions? ";
	std::cin >> depth;

	// Create the binomal lattice data conainer
	const int n = 2;
	Lattice<double, int, n> lattice1(depth);


	// Test data; change to suit your own needs
	double rootValue = 12.0;// Stock price now
	double D0 = 0.04;		// Dividend yield
	double vol = 0.3;		// Volatility
	double r = 0.06;		// Interest
	double T = 1.0;				// Time to expiry

	std::cout << "Give value for expiry T: ";
	std::cin >> T;

	// Create the 'special' parameters
	double k = T / double (depth);
	double e = std::exp((r-D0)*k);
	double sr = std::sqrt(exp(vol*vol*k) - 1.0);

	double up = e * (1.0 + sr);
	double down = e * (1.0 - sr);

	// Populate lattice: forward induction
	Lattice<double, int, 2> newLattice = 
			StandardLattice::createLattice(depth, rootValue, up, down);

	// Now work back from the payoff function; BACKWARD INDUCTION

	// First make the discrete payoff
	double K = 10.0;
	Vector<double, int> RHS = CallPayOff(K, newLattice[newLattice.MaxIndex()]);
	Vector<double, int> RHS2 = PutPayOff(K, lattice1[lattice1.MaxIndex()]);

	double p = 0.5;
	double discounting = std::exp(- r*k);
	
	double optionPrice = StandardLattice::traverse(newLattice, RHS, p, discounting);
	double optionPrice2 = StandardLattice::traverse(newLattice, RHS2, p, discounting);

	std::cout << "\nOption price C " << optionPrice << std::endl;
	std::cout << "\nOption price P " << optionPrice2 << std::endl;

	return 0;
}