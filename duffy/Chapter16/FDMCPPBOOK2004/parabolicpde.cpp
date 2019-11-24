
// pde.cpp
//
// Modellling Parabolic PDE as C++ classes
//
//	Last modification dates:
//	2000-7-27 DD Kick-off (N.B. client MUST know in which order the functions
//	are given. Jasmin to finish off!! (Please)
//	2000-7-29 DD new set and get functions.
//	2001-2-1 DD Some more constructors
//  2002-1-8 DD Cleanup mostly
//  2002-22-5 RM added virtual destructor
//
//  (C) Datasim Component Technology BV 2000-2006


#ifndef PPDE_CPP
#define PPDE_CPP

#include "parabolicpde.hpp"

template <class X, class T, class V>
ParabolicPDE<X, T, V>::ParabolicPDE()
{
		xaxis = Range<X>();
		taxis = Range<T>();
				
		sig	= m = b = f = TwoVarDFunction<X,T,V>();
		bcl  = bcr = AtomicDFunction<T,V> ();
		ic = AtomicDFunction<X,V>();		
}

template <class X, class T, class V> 
ParabolicPDE<X, T, V>::ParabolicPDE(const Range<X>& xrange, const Range<T>& trange, 
	const TwoVarDFunction<X,T,V>& sigma, const TwoVarDFunction<X,T,V>& mu, const TwoVarDFunction<X,T,V>& freeterm, 
	const TwoVarDFunction<X,T,V>& rhs, const AtomicDFunction<X,V>& initial, const AtomicDFunction<T,V>& bcL, const AtomicDFunction<T,V>& bcR)
{
		xaxis = xrange;
		taxis = trange;
		
		sig		= sigma;
		m		= mu;
		b		= freeterm;
		f		= rhs;

		ic		= initial;
		bcl		= bcL;
		bcr		= bcR; 
}

// 2002-22-5 RM virtual destructor is desired
template <class X, class T, class V>
ParabolicPDE<X, T, V>::~ParabolicPDE()
{;}

// Selector functions
// Coefficients of parabolic second order operator
template <class X, class T, class V> TwoVarDFunction<X,T,V>  ParabolicPDE<X, T, V>::diffusion() const
{ // Coefficient of second derivative

		return sig;
}

template <class X, class T, class V> TwoVarDFunction<X,T,V>  ParabolicPDE<X, T, V>::convection() const
{ // Coefficient of first derivative

		return m;
}

template <class X, class T, class V> TwoVarDFunction<X,T,V>  ParabolicPDE<X, T, V>::zeroterm() const
{ // Coefficient of free term

		return b;
}

template <class X, class T, class V> TwoVarDFunction<X,T,V>  ParabolicPDE<X, T, V>::RHS() const
{ // Coefficient of right-hand side forcing term

		return f;
}

template <class X, class T, class V> AtomicDFunction<T,V>  ParabolicPDE<X, T, V>::BCL() const
{ // Left-hand boundary condition

		return bcl;
}

template <class X, class T, class V> AtomicDFunction<T,V>  ParabolicPDE<X, T, V>::BCR() const
{ // Right-hand boundary condition

		return bcr;
}

template <class X, class T, class V> AtomicDFunction<X,V>  ParabolicPDE<X, T, V>::IC() const
{ // The initial condition

		return ic;
}



// The domain in which the PDE is 'played'
template <class X, class T, class V> Range<X> ParabolicPDE<X, T, V>::first () const
{


		return xaxis;
}

template <class X, class T, class V> Range<T> ParabolicPDE<X, T, V>::second() const
{
		return taxis;
}



	

// Modifier functions
// Coefficients of parabolic second order operator
template <class X, class T, class V> void ParabolicPDE<X, T, V>::diffusion(TwoVarDFunction<X,T,V>& new_function)
{ // Coefficient of second derivative

		sig = new_function;
}


template <class X, class T, class V> void ParabolicPDE<X, T, V>::convection(const TwoVarDFunction<X,T,V>& new_function)
{ // Coefficient of first derivative

		m = new_function;
}


template <class X, class T, class V> void ParabolicPDE<X, T, V>::zeroterm(const TwoVarDFunction<X,T,V>& new_function)
{ // Coefficient of zero derivative

		b = new_function;
}

template <class X, class T, class V> void ParabolicPDE<X, T, V>::RHS(const TwoVarDFunction<X,T,V>& new_function)
{ // Inhomogeneous forcing term

		f = new_function;
}


// Boundary and initial conditions
template <class X, class T, class V> void ParabolicPDE<X, T, V>::BCL(const AtomicDFunction<T,V>& new_function)
{ // Left hand boundary condition

		bcl = new_function;
}


template <class X, class T, class V> void ParabolicPDE<X, T, V>::BCR(const AtomicDFunction<T,V>& new_function)
{ // Right hand boundary condition

		bcr = new_function;
}

template <class X, class T, class V> void ParabolicPDE<X, T, V>::IC(const AtomicDFunction<X,V>& new_function) 
{ // Initial condition

		ic = new_function;
}


		
// The domain in which the PDE is 'played'
template <class X, class T, class V> void ParabolicPDE<X, T, V>::first (const Range<X>& new_range) 
{

		xaxis = new_range;
}

template <class X, class T, class V> void ParabolicPDE<X, T, V>::second(const Range<T>& new_range) 
{

		taxis = new_range;
}



// Calculation of functions
template <class X, class T, class V> V ParabolicPDE<X, T, V>::diffusion(const X& xvalue, const T& tvalue) const
{

	return sig.calculate(pair<X,T> (xvalue, tvalue));
}

template <class X, class T, class V> V ParabolicPDE<X, T, V>::convection(const X& xvalue, const T& tvalue) const
{
	return m.calculate(pair<X,T> (xvalue, tvalue));

}

template <class X, class T, class V> V ParabolicPDE<X, T, V>::zeroterm(const X& xvalue, const T& tvalue) const
{
	return b.calculate(pair<X,T> (xvalue, tvalue));

}

template <class X, class T, class V> V ParabolicPDE<X, T, V>::RHS(const X& xvalue, const T& tvalue) const
{

	return f.calculate(pair<X,T> (xvalue, tvalue));

}


		
// Boundary and initial conditions
template <class X, class T, class V> V ParabolicPDE<X, T, V>::BCL(const T& tvalue) const
{
	return bcl.calculate(tvalue);

}


template <class X, class T, class V> V ParabolicPDE<X, T, V>::BCR(const T& tvalue) const
{
	return bcr.calculate(tvalue);
}


template <class X, class T, class V> V  ParabolicPDE<X, T, V>::IC(const X& xvalue) const
{
	return ic.calculate(xvalue);
}



	
#endif