// testlattice.cpp
//
// Testing the Latice class (basis for binomial and trinomial
// trees)
//
// In this version we have one class for both binomial and trinomial
// trees.
//
// (C) Datasim Education BV 2003-2005
//

#include <duffy/Lattice.hh>
#include <duffy/ArrayMechanisms.hh>
#include "../src/LatticeMechanisms.cc"
#include <cmath>

int main()
{
	
	int lattice = 2;	// BinomialLatticeType;
	int depth = 3;

	Lattice<double, int> lattice1(depth);

//	print(lattice1);

	std::cout << "Forward sweep, Wilmott p. 193\n";
	double rootValue = 5.0;	 // Stock price now
	double D0 = 0.0;		// Dividend yield
	double vol = 0.5;		// Volatility
	double r = 2*0.06;		// Interest
	double T = 1.0;			// Time to expiry

	double k = T / double (depth);
	double e = std::exp((r-D0)*k);
	double sr = std::sqrt(exp(vol*vol*k) - 1.0);


	double up = e * (1.0 + sr);
	double down = e * (1.0 - sr);

	// Call the function from ArrayMechanisms package
	modify(lattice1, rootValue, up, down);
	std::cout << "modified lattice";
//	print (lattice1);
	// Now work back from the payoff function

	// First make the discrete payoff
	double K = 10.0;
//	Vector<double, int> RHS = CallPayOff(K, lattice1[lattice1.MaxIndex()]);
	Vector<double, int> RHS = PutPayOff(K, lattice1[lattice1.MaxIndex()]);

	//print (RHS);

	double probValue = 0.5;
	double discounting = ::exp(- r*k);
	ExerciseType type = EuropeanExerciseType;

	Lattice<double, int> treeValues(lattice1);	// Will be initialised in traverse()
	double optionPrice = traverse(lattice1, RHS, probValue, discounting, type, treeValues);

//	print(treeValues);

	std::cout << "\nOption price " << optionPrice << std::endl;

	// Sensitivities (greeks)
	Lattice<double, int> deltaLattice = dividedDifference(treeValues, lattice1); // Y and X values so to speak
//	print (deltaLattice);

	std::cout << "Finish";

	return 0;
}