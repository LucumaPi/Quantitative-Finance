// detfunction.hpp
//
// Deterministic functions. This is the base class for all kinds of 
// deterministic functions. Included are:
//
//		Atomic functions
//		Functions of two variables
//
// (C) Datasim Component Technology BV
//

#ifndef DFunction_HPP
#define DFunction_HPP

#include "function.cpp"


#include <map>
using namespace std;

template <class D, class R> class DFunction: public Function <D, R>
{ // Abstract base class for all deterministic functions

public:
	DFunction() {}

		// Empty
};

// Basic building blocks

template <class D, class R> class AtomicDFunction : public DFunction<D, R>
{
//private:
public:
		R (*f)(const D& x);		// Hidden classic C-type function

public:
	AtomicDFunction();
	AtomicDFunction (R (*fp)(const D& x));	// Using function objects
	AtomicDFunction(const AtomicDFunction<D, R>& f2);
	virtual ~AtomicDFunction();
	AtomicDFunction<D, R>& operator = (const AtomicDFunction<D, R>& f2);

	virtual R calculate(const D& x) const;

	// Choosing a new function
	void function(R (*fp)(const D& x));

	// Mathematical operations between 2 functions
	// Function <OP> Function
	R add(const AtomicDFunction<D,R>& f2, const D& x) const;	// +

};

template <class D1, class D2, class R> class TwoVarDFunction : public AtomicDFunction<pair<D1, D2>, R>
{ // A class representing a function of two variables. This is useful in PDE.

private:
		
public:
	// Constructors
	TwoVarDFunction();
	
	//altered 1/5/2002 by R. Mirani (TwoVarFunction->TwoVarDFunction)
	//TwoVarFunction (R (*fp)(const D1& x, const D2& y));	// 'Normal' C functions as input
	
	// 2002-17-5 RM constructor should recieve only one variable
	//TwoVarDFunction (R (*fp)(const D1& x, const D2& y));	// 'Normal' C functions as input
	TwoVarDFunction (R (*fp)(const pair<D1,D2>&));	// 'Normal' C functions as input	
	
	TwoVarDFunction(const TwoVarDFunction<D1,D2,R>& f2);
	virtual ~TwoVarDFunction();

	TwoVarDFunction<D1, D2, R>& operator = (const TwoVarDFunction<D1, D2,R>& f2);

	// Conversions (possible?)
	// 2002-17-5 RM function XX never defined. Therefore edited out here.
	//AtomicDFunction<D2,R> XX(const D1& t);		// Instantiate one of the variables
	
	
	// We need to instantiate both d1 and d2 and give an R!
	R calculate2d(const D1& d1, const D2& d2) const;
//	AtomicDFunction<D1,R> XX(const D2& t);		// Instantiate one of the variables

};

/*

// Vector-valued functions (Top-level composite class for deterministic functions)
template <class D, class R, class I> class VectorDFunction : public DFunction<D, R>
{ // Class representing vector-valued functions. These map D into R X R (n times).
  // D == Domain, R == Range, I == Index Type
private:
		
 		Array<AtomicDFunction<D,R>, I> components;			// Individual functions
		
public:
		VectorDFunction();										// Contains 1 function
		VectorDFunction(const I& size);							// Number of components
		VectorDFunction(const VectorDFunction<D,R,I>& f2);		// Copy constructor
		virtual ~VectorDFunction();	

		VectorDFunction<D, R, I>& operator = (const VectorDFunction<D, R, I>& f2);

		// Now set and get the individual functions
		void function(const I& position, const AtomicDFunction<D,R> func);
		AtomicDFunction<D,R> function (const I& size) const;

		Array<R,I> calculate(const D& x) const;

};


// Matrix-valued functions
template <class D, class R, class I> class MatrixDFunction : public DFunction<D, R>
{ // A full matrix of functions

// This class represents in essence the set of vector functions of vector variables. An 
// instance of this class is a mapping from n-dimensional space (domain)to m-dimensional space
// (range). The class can be visualised as some kind of matrix whose elements are 'atomic' functions
// (hence the name).

private:
		
		Array<VectorDFunction<D,R,I>, I> m;		// Array of Vector functions
		I nr, nc;								// Redundant variables

public:
		MatrixDFunction();										// 1 row & 1 column
		MatrixDFunction(const I& nrows, const I& ncolumns);		// Number of rows/columns
		MatrixDFunction(const MatrixDFunction<D,R,I>& arr2);	// Copy constructor
		virtual ~MatrixDFunction();	

		MatrixDFunction<D, R, I>& operator = (const MatrixDFunction<D, R, I>& f2);

		// Now set and get the individual functions
		void function(const I& row, const I& col,  const AtomicDFunction<D,R>& func);
		AtomicDFunction<D,R> function (const I& row, const I& col) const;

		NumericMatrix<R,I> calculate(const D& x) const;

};


///////////////////////////////
// Decorator classes
///////////////////////////////
template <class D, class Common, class R> class DecoratorDFunction: public AtomicDFunction <D,R>
{ // A function class that 'points' to another function class
  // outer function f: Common -> R, inner function g: D --> Common 
  // There are constraints

private:

		AtomicDFunction<D, Common> g;	// Inner function (first' g)
		AtomicDFunction<Common, R> f;	// Outer function (second, f)

public:
		DecoratorDFunction(const AtomicDFunction<D,Common>& inner_function,
							const AtomicDFunction<Common,R>& outer_function);
		DecoratorDFunction(const DecoratorDFunction<D,Common,R>& outer_function);

		// Usual stuff :) DD

		R calculate(const D& x) const;
		
};

template <class D, class I> class PowerDFunction: public AtomicDFunction <D,D>
{ // Powere of a function

private:

		I n;	// power 
public:
		PowerDFunction(const AtomicDFunction<D,D>& function, const I& power);

		// Usual stuff :) DD

		D calculate(const D& x) const;
		
};

// New, highly reusable classes

template <class D, class R> class VectorFunction: public Function <D, Array<R> >
{

};


template <class D, class R> class VectorValuedFunction: public Function <Array<D>, Array<R> >
{

};


template <class D, class R> class RealValuedFunction: public Function <Array<D>, R >
{

};
*/
#endif