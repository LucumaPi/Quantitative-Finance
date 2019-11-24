// doublesweep.hpp
// 
// The Godunov Balayage method for solving tridiagonal systems. We
// should be careful with start and end indices. The solution vector
// is in the range [1, J-1] as well as the vectors representing the 
// the main and of-diagonals of the tridiagonal system.
//
//	Note that this kind of problem originates typically from problems 
//  with Dirichlet boundary conditions. It is a competitor of the LU
//	decomposition for tridiagonal matrices.
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef DOUBLESWEEP_HPP
#define DOUBLESWEEP_HPP

#include "Vector.cpp"

template <class V, class I>
class DoubleSweep
{ // The Balayage method from Godunov

private:
	
		// The vectors of length J and start index J
		Vector<V,I> aa, bb, cc, ff;

		V left;		// Left boundary condition
		V right;	// Right boundary condition

public:
		// Constructors and destructor
		DoubleSweep();							
		DoubleSweep (const DoubleSweep<V,I>& s2);	

		// Create members to initialise input for AU = F, A = (a,b,c)
		DoubleSweep(const Vector<V,I>& a, const Vector<V,I>& b, 
					const Vector<V,I>& c,
					const Vector<V,I>& f, const V& bc_left, const V& bc_right);
		virtual ~DoubleSweep();


		// Operator overloading
		DoubleSweep<V,I>& operator = (const DoubleSweep<V,I>& i2);

		// Result; this is a vector in range [1, J-1]
		Vector<V,I> result() const;
		Vector<V,I> solve() const; // synonym
};



#endif
