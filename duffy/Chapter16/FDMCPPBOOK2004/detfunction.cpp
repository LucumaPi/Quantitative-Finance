// detfunction.cpp
//
//	Last modification dates:
//	2000-7-27 DD classes for functions with 1 and 2 parameters
//	(oh ya, almost forget special thanks to Adriaan)
//	2000-7-28 DD No base class, just 2 template classes to represent 2
//	parameters and one parameter.
//	2000-11-12 DD more generic approach (less classes needed)
//	2001-1-9 DD mathematical functions
//	2001-1-20 DD New interpretation of MatrixDFunction (as a vector function of a 
//	vector variable).
//	2001-2-1 DD Decorator (composite) functions
//  2002-17-5 RM Constructor TwoVarDFunction now recieves pair
//  2002-17-5 RM operator = must return *this
//  2002-17-5 RM .hpp file contains function XX which is never declared. Removed it
//
// (C) Datasim Component Technology BV 2000
//
//

#ifndef DFunction_cpp
#define DFunction_cpp

#include "detfunction.hpp"

template <class D, class R> 
	AtomicDFunction<D, R>::AtomicDFunction ()
{

		f = 0;

}


template <class D, class R> 
	AtomicDFunction<D, R>::AtomicDFunction (const AtomicDFunction<D, R>& f2)
{
		f = f2.f;
}


template <class D, class R> 
	AtomicDFunction<D, R>::AtomicDFunction (R (*fp) (const D& x))
{

		f = fp;

}

template <class D, class R> 
	AtomicDFunction<D, R>::~AtomicDFunction ()
{

	

}


template <class D, class R> R
	AtomicDFunction<D,R>::calculate(const D& x) const
{

		return (*f)(x);

}

template <class D, class R> AtomicDFunction<D, R>&
	AtomicDFunction<D, R>::operator = (const AtomicDFunction<D,R>& f2) 
{ 
		if (this == &f2)
			return *this;

		f = f2.f;

		return *this;
}

// Choosing a new function
template <class D, class R> void
	AtomicDFunction<D, R>::function (R (*fp) (const D& x))
{

		f = fp;

}

template <class D, class R>	
	R AtomicDFunction<D,R>::add(const AtomicDFunction<D,R>& f2, const D& x) const
{

		return calculate(x) + f2.calculate(x);
}


template <class D1, class D2, class R> 
	TwoVarDFunction<D1,D2,R>::TwoVarDFunction() : AtomicDFunction<pair<D1,D2>, R>()
{

}

/* altered 1/5/2002 by R. Mirani (TwoVarFunction->TwoVarDFunction) AND <pair(D1,D2>,R>) -> <pair<D1,D2>,R>
template <class D1, class D2, class R> 
	TwoVarDFunction<D1,D2,R>::TwoVarFunction (R (*fp)(const D1& x, const D2& y)) : AtomicDFunction<pair(D1,D2>,R>) (fp)
{ // 'Normal' C functions as input
}*/

// 2002-17-5 RM function recieves a function with two variables but passes it on to AtomicDfunction
// which expects only one variable
/*template <class D1, class D2, class R>
	TwoVarDFunction<D1,D2,R>::TwoVarDFunction (R (*fp)(const D1& x, const D2& y)) : AtomicDFunction<pair<D1,D2>,R> (fp)
{ // 'Normal' C functions as input
}*/
template <class D1, class D2, class R>
	TwoVarDFunction<D1,D2,R>::TwoVarDFunction (R (*fp)(const pair<D1,D2>&)) : AtomicDFunction<pair<D1,D2>,R> (fp)
{ // 'Normal' C functions as input
}

template <class D1, class D2, class R> 
	TwoVarDFunction<D1,D2,R>::TwoVarDFunction(const TwoVarDFunction<D1,D2,R>& f2) : AtomicDFunction<pair<D1,D2>,R> (f2)
{

}

template <class D1, class D2, class R>
 	TwoVarDFunction<D1,D2,R>::~TwoVarDFunction()
{

}

template <class D1, class D2, class R> 	
	TwoVarDFunction<D1,D2,R>& TwoVarDFunction<D1,D2,R>::operator = (const TwoVarDFunction<D1,D2,R>& f2)
{
		if (this == &f2)
			return *this;

		AtomicDFunction<pair<D1,D2>,R>::operator = (f2);
		
		//2002-17-5 RM function must return *this
		return *this;
}
/*

template <class D1, class D2, class R> 	
	AtomicDFunction<D2,R> TwoVarDFunction<D1,D2,R>::XX(const D1& t)
{ // Instantiate one of the variables

		// Tricky function? Possible? Properties?
}
*/
template <class D1, class D2, class R> 	
	R TwoVarDFunction<D1,D2,R>::calculate2d(const D1& d1, const D2& d2) const
{
		return calculate(pair<D1, D2> (d1, d2));
}

/*
//////////////////////////
// Vector-valued functions
//////////////////////////
template <class D, class R, class I> 
	VectorDFunction<D,R,I>::VectorDFunction()
{ // Number of components

	I size = 1;

	components = Array<AtomicDFunction<D,R>, I > (size);

	for (int j = components.MinIndex(); j <= components.MaxIndex(); j++)
	{
		components[j] = AtomicDFunction<D,R>();
	}

}

template <class D, class R, class I> 
	VectorDFunction<D,R,I>::VectorDFunction(const I& size)
{ // Number of components


	components = Array<AtomicDFunction<D,R>, I > (size);

	for (int j = components.MinIndex(); j <= components.MaxIndex(); j++)

	{
		components[j] = AtomicDFunction<D,R>();
	}

}

template <class D, class R, class I> 
	VectorDFunction<D,R,I>::VectorDFunction(const VectorDFunction<D,R,I>& f2)
{ // Copy constructor

		components = f2.components;
}

template <class D, class R, class I> 
	VectorDFunction<D,R,I>::~VectorDFunction()
{ // Destructor



}

template <class D, class R, class I> 
	VectorDFunction<D, R, I>& VectorDFunction<D,R,I>::operator = (const VectorDFunction<D, R, I>& f2)
{ // Assignment operator

		if (this == &f2)
			return *this;

		components = f2.components;

		return *this;
}


// Now set and get the individual functions
template <class D, class R, class I> 
	void VectorDFunction<D,R,I>::function(const I& position,const AtomicDFunction<D,R> func)
{
	cout << "DEBUG vector function " << position << "," << endl;

	components[position].function(func.f);
}

template <class D, class R, class I> 
	AtomicDFunction<D,R> VectorDFunction<D,R,I>::function (const I& size) const
{

		return components[position];
}

template <class D, class R, class I> 
	Array<R,I> VectorDFunction<D,R,I>::calculate(const D& x) const
{
	
		Array<R,I> result(components.Size());


		for (I j = result.MinIndex(); j <= result.MaxIndex(); j++)
		{
			result[j] = components[j].calculate(x);
		}

		return result;
}

//////////////////////////
// Matrix-valued functions
//////////////////////////
template <class D, class R, class I> 
	MatrixDFunction<D,R,I>::MatrixDFunction()
{ // Number of components

	nr = 1; nc = 1;

	VectorDFunction<D,R,I> internal (nc);

	m = Array<VectorDFunction<D,R,I>, I> (nr);
	for (I i = 1; i <= nr; i++)
	{
		m[i] = VectorDFunction<D,R,I>(internal);
	
	}

}

template <class D, class R, class I> 
	MatrixDFunction<D,R,I>::MatrixDFunction(const I& nrow, const I& ncol)
{ // Number of components


	// We must create n rows, each row containing m basic functions (or a 
	// vector-valued function of length m).

	nr = nrow; nc = ncol;

	VectorDFunction<D,R,I> internal (nc);

	m = Array<VectorDFunction<D,R,I>, I> (nr);
	for (I i = 1; i <= nr; i++)
	{
		m[i] = VectorDFunction<D,R,I>(internal);
	
	}

}

template <class D, class R, class I> 
	MatrixDFunction<D,R,I>::MatrixDFunction(const MatrixDFunction<D,R,I>& f2)
{ // Copy constructor

		nr = f2.nr; nc = f2.nc;
		m = f.m;

}

template <class D, class R, class I> 
	MatrixDFunction<D,R,I>::~MatrixDFunction()
{ // Destructor



}

template <class D, class R, class I> 
	MatrixDFunction<D, R, I>& MatrixDFunction<D,R,I>::operator = (const MatrixDFunction<D, R, I>& f2)
{ // Assignment operator

	if (this == &f2)
		return *this;

	m = f2.m;
	nr = f2.nr; nc = f2.nc;

	return *this;
//altered by R. Mirani 1/5/2002
//	*}
}

// Now set and get the individual functions
template <class D, class R, class I> 
	void MatrixDFunction<D,R,I>::function(const I& row, const I& col, const AtomicDFunction<D,R>& func)
{

	cout << "DEBUG matrix function " << row << "," << col << endl;

	m[row].function(col, func);
}

template <class D, class R, class I> 
	AtomicDFunction<D,R> MatrixDFunction<D,R,I>::function (const I& row, const I& col) const
{

	return m[row].function(col);
}

template <class D, class R, class I> 
	NumericMatrix<R,I> MatrixDFunction<D,R,I>::calculate(const D& x) const
{
	
	NumericMatrix<R,I> result(nr, nc);
	Array<R,I> internal(nc);

	for (I i = 1; i <= nr; i++)
	{
			internal = m[i].calculate(x);
		//	result.Row(i,internal);
	}
	
	return result;
}

// Decorator functions

template <class D, class Common, class R> 
DecoratorDFunction<D,Common,R>::DecoratorDFunction(const AtomicDFunction<D,Common>& inner_function,
							const AtomicDFunction<Common,R>& outer_function)
{

	g = inner_function;
	f = outer_function;
}

template <class D, class Common, class R> 
DecoratorDFunction<D,Common,R>::DecoratorDFunction(const DecoratorDFunction<D,Common,R>& function2)
{
	g = function2.g;
	f = function2.f;
}

template <class D, class Common, class R> 
	R DecoratorDFunction<D,Common,R>::calculate(const D& x) const
{ // 2 stage process

	Common i = g.calculate(x);

	cout << "*Internal value: " << i << "*" << endl;

	R result = f.calculate(i);

	return result;
}

// Special Composites: powers of a function
template <class D, class I> 
PowerDFunction<D,I>::PowerDFunction(const AtomicDFunction<D,D>& function, const I& power) 
		: AtomicDFunction<D,D> (function)
{
	n = power;
}

template <class D, class I> 
D PowerDFunction<D,I>::calculate(const D& x) const
{ // Calculate n times

	D tmp;
	tmp = AtomicDFunction<D,D>::calculate(x);

	for (I i = 2; i <= n; i++)
	{
		tmp = AtomicDFunction<D,D>::calculate(tmp);
		
	}
		
	return tmp;
}
*/

#endif