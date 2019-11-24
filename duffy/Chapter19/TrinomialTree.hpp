// TrinomialTree.hpp
//
// This class represents a trinomial tree model of the asset price.
// This model assumes that the asset price can reach tree values.
// When x = lnS, than the tree values can be calculated via:
// lnS = x + dx, lnS = x, lnS = x - dx. Thus S can become larger, smaller or
// stay same in a defined way.
//
// (C) Datasim Component Technology 2000-2006


#include "Vector.cpp"
#include "TrinomialParameters.hpp"


#ifndef TRINOMIALTREE_HPP
#define TRINOMIALTREE_HPP

namespace Datasim
{

class TrinomialTree
{
private:

	TrinomialParameters* par;	// The source of the data

	long N;						// Redundant parameter, number of time steps

	// Representing the base for making of the trinomial tree structure (array of arrays which are vectors)
	//Vector<Vector<TV,I,FullArray<TV> >,I,FullArray<Vector<TV,I,FullArray<TV> > > >* TriTree;

	// This data structure is an array (in time 0 to N) of simpler structure. Each simpler structure
	// is a Vector (in S space) whose elements are a two-dimensional vector containg the asset price
	// S and option price (C or P)
	// Vector<Vector<double,long>, long>* TriTree;
	// N.B. In this version we do NOT model the tree explicitly

	Vector<double,long>* option; // The option data at each time level and underlying

private:

	// Some constructors are private
	TrinomialTree();	// Default constructor
	TrinomialTree(const TrinomialTree& tritree); // Copy-constructor
	// Operator overloading
	TrinomialTree& operator=(const TrinomialTree& tritree);	// Assignment

public:
	// Construct a tree with given option data
	TrinomialTree(TrinomialParameters& optinData); 
	virtual ~TrinomialTree();	// Destructor

	
	// Calculate call price
	double Price(double S);
  
};

} // End of namespace Datasim

#endif // TRINOMIALTREE_HPP