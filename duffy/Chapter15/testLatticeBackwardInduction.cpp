// testLatticeBackwardInduction.cpp
//
// Using namespaces to create different a backward induction
// algorithm for a binomial tree. The algorithm is similar to 
// template method pattern; we have two function with variant
// behaviours and these must be initialised in a main program.
//
//	2005-1-4 DD Kick-off code
//	2005-1-5 DD might be OVERKILL

// (C) Datasim Education BV 2005

#include "Lattice.cpp"
#include "Vector.cpp"

namespace BackwardInduction
{
		 // Functions to be overridden
		Vector<double, int> (*createTerminalVector)(const Lattice<double, int, 2>& lattice);

		// Calculate a node value from two upper ones
		double (*nodeValue)(double, upper, double lower);
		

		// Code here corresponds to backward induction
		double taverse(const Lattice<double, int, 2>& lattice)
		{

				int ei = lattice.MaxIndex();
				lattice[ei] = createTerminalVector(lattice);

				// Loop from the max index to the start (min) index
				for (int n = lattice.MaxIndex() - 1; n >= lattice.MinIndex(); n--)
				{

				for (int i = copy[j].MinIndex(); i <= copy[j].MaxIndex(); i++)
				{
			
		//			copy[n][i] = discounting * (p * copy[n+1][i+1] + (1.0-p) * copy[n+1][i]);
					lattice[n][i] = nodeValue(copy[n+1][i+1], copy[n+1][i]))

				}

		}

		int si = lattice.MinIndex();
		return lattice[si][lattice[si].MinIndex()];

}

Vector<double, int> mycreateTerminalVector(const Lattice<double, int, 2>& lattice)
{

	//
}
	
double mynodeValue(double upper, double lower)
{

	//
}

int main()
{

	Lattice<double, int, 2> lattice;
	BackwardInduction::createTerminalVector = mycreateTerminalVector(latttice);

	double upper = 
	double lower = 
	BackwardInduction::nodeValue = mynodeValue(uppper, lower, latttice);

	using namespace BackwardInduction;

	double result = taverse(const Lattice<double, int, 2>& lattice);
}
