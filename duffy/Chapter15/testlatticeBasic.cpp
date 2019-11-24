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

#include "lattice.cpp"
#include "latticemechanisms.cpp"

#include <iostream>
using namespace std;


int main()
{
	/*
	int Continue;			// Break point

	const int typeB = 2;	// BinomialLatticeType;
	const int typeT = 3;	// Trinomial Type

	int depth = 5;

	Lattice<double, int, typeB> lattice1(depth);
	Lattice<double, int, typeT> lattice2(depth);

	print(lattice1); 
	cout << endl << endl;
	print(lattice2);

	
	cout << endl;

	depth = 200;

	cout << "Consistent trinomial tree for short rate\n";
	cout << "How many time divisions: " << endl;
	cin >> depth;
	if (depth <= 0) return 0;

	int pr = 0;
	cout << "Wanna print tree on screen (Costs time) 1 Yes, 0 No " << endl;
	cin >> pr;
*/
	// Trinomial lattice with matrix entries
	int Nrows = 3;
	int Ncols = 2;
	int startIndex = 1;
	int N = 3;		// Number of time steps
	Matrix<double, int> nodeStructure(Nrows, Ncols, startIndex, startIndex);
	Lattice<Matrix<double, int>, int, 3> trinomialLattice(N, nodeStructure);
	cout << "Number of discrete points at end: " << trinomialLattice.BasePyramidSize() << endl;
	cout << "Total number of nodes: " << trinomialLattice.numberNodes() << endl;

	
	return 0;
}
