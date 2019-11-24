// parabolicpde.hpp
//
// Modelling PDE as C++ classes. This is a simple model in one space
// dimension where we assume that Dirichlet boundary conditions are in 
// force.
//
// (C) Datasim Component Technology BV 2000-2006

#ifndef PDE_HPP
#define PDE_HPP

#include "range.cpp"
#include "detfunction.cpp"

class PDE
{};

template <class X, class T, class V> class ParabolicPDE : public PDE
{
private:
	Range<X> xaxis;						// Space interval
	Range<T> taxis;						// Time  interval
	TwoVarDFunction<X, T, V> sig, m, b, f;	// Coefficients in equation
	AtomicDFunction<X, V> ic;				// Initial condition
	AtomicDFunction<T, V> bcl, bcr;			// Left and right boundary conditions

public:
ParabolicPDE();
ParabolicPDE(const Range<X>& xrange, const Range<T>& trange,
	const TwoVarDFunction<X,T,V>& sigma, const TwoVarDFunction<X,T,V>& mu, 
	const TwoVarDFunction<X,T,V>& b, const TwoVarDFunction<X,T,V>& rhs,
	const AtomicDFunction<X,V>& initial, const AtomicDFunction<T,V>& bcL, 
	const AtomicDFunction<T,V>& bcR); 

virtual ~ParabolicPDE();
	

// Selector functions
// Coefficients of parabolic second order operator
virtual TwoVarDFunction<X,T,V> diffusion() const;	// Coefficient of second derivative
virtual TwoVarDFunction<X,T,V> convection() const;	// Coefficient of first derivative
virtual TwoVarDFunction<X,T,V> zeroterm() const;	// Coefficient of zero derivative
virtual TwoVarDFunction<X,T,V> RHS() const;			// Inhomogeneous forcing term

// Boundary and initial conditions
virtual AtomicDFunction<T,V> BCL() const;			// Left hand boundary condition
virtual AtomicDFunction<T,V> BCR() const;			// Right hand boundary condition
virtual AtomicDFunction<X,V> IC() const;			// Initial condition

		
// The domain in which the PDE is 'played'
virtual Range<X> first () const;
virtual Range<T> second() const;


// Modifier functions
// Coefficients of parabolic second order operator
virtual void diffusion(TwoVarDFunction<X,T,V>& new_function);		// Coefficient of second derivative
virtual void convection(const TwoVarDFunction<X,T,V>& new_function);// Coefficient of first derivative
virtual void zeroterm(const TwoVarDFunction<X,T,V>& new_function);	// Coefficient of zero derivative
virtual void RHS(const TwoVarDFunction<X,T,V>& new_function);		// Inhomogeneous forcing term

// Boundary and initial conditions
virtual void BCL(const AtomicDFunction<T,V>& new_function);			// Left hand boundary condition
virtual void BCR(const AtomicDFunction<T,V>& new_function);			// Right hand boundary condition
virtual void IC(const AtomicDFunction<X,V>& new_function);			// Initial condition

		
// The domain in which the PDE is 'played'
virtual void first (const Range<X>& new_range);
virtual void second(const Range<T>& new_range);

// Calculation of functions
virtual V diffusion(const X& xvalue, const T& tvalue) const;		// Sigma
virtual V convection(const X& xvalue, const T& tvalue) const;		// Mu
virtual V zeroterm(const X& xvalue, const T& tvalue) const;			// b
virtual V RHS(const X& xvalue, const T& tvalue) const;				// f
		
// Boundary and initial conditions
virtual V BCL(const T& tvalue) const;			
virtual V BCR(const T& tvalue) const;		
virtual V IC(const X& xvalue) const;					

};

#endif
