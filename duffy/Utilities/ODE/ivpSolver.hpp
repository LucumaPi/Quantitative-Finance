// ivpsolver.hpp
//
// Solvers for initial value problems. 
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef IVPSolver_hpp
#define IVPSolver_hpp


#include "ivp.cpp"
#include "vector.cpp"
#include <math.h>

class  IVPFDM
{ // Set of finite difference to solve scalar initial
  // value problems

protected:
	
	IVP* ivp;				// Pointer to 'parent'

	long N;					// The number of subdivision of interval in IVP 
	double k;				// Step length; redundant data but is efficient				

	IVPFDM(const IVPFDM& source); 

	IVPFDM& operator = (const IVPFDM& source);

	// Help functions (Strategy) and redundant data
	Vector<double, long> res;		// Will contain the results of the calculations

public:
	IVPFDM();
	IVPFDM(IVP& source, long NSteps);

	virtual ~IVPFDM();
 	
	// Modifier functions
	void steps(long Nsteps);

	// Output
	double stepSize() const;

	// N.B. !!! Resulting output of size N+1 and start index 1 !!!!!!1
	Vector<double, long> result();		// The result of the calculation

	// Hook function for Template Method pattern 
	virtual void calculate() = 0;
};

class EEulerIVP : public IVPFDM
{
public:
	EEulerIVP() : IVPFDM() {}
	EEulerIVP(IVP& source, long NSteps) : 	IVPFDM(source, NSteps) {}

	void calculate()
	{
		for (long i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
		{
			res[i] = res[i-1]*( 1.0 - (k* ivp->a((i-1)*k)) ) + (k* ivp->f((i-1)*k));
		}
	
	}
};

class IEulerIVP : public IVPFDM
{
public:
	IEulerIVP() : IVPFDM() {}
	IEulerIVP(IVP& source, long NSteps) : 	IVPFDM(source, NSteps) {}

	void calculate()
	{

		for (int i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
		{
			res[i] = ( res[i-1] + (k* ivp->f(i*k)) ) / ( 1.0 + (k* ivp->a(i*k)) );
		}
	
	
	}
};

class PredictorCorrectorIVP : public IVPFDM
{
public:
	PredictorCorrectorIVP() : IVPFDM() {}
	PredictorCorrectorIVP(IVP& source, long NSteps) : 	IVPFDM(source, NSteps) {}

	void calculate()
	{
	
		for (int i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
		{

			// First get the predictor (Explicit Euler)
			double predictor = res[i-1]*( 1.0 - (k* ivp->a((i-1)*k)) ) + (k* ivp->f((i-1)*k));
		
			// Corrector (this IS the solution)
			double vup = 1.0 - ( k * 0.5 *ivp->a((i-1)*k) );
			double pTerm = (k * 0.5 * ivp->a(i*k) ) * predictor;
	
			double favg = k * 0.5 * ( ivp->f(i*k) + ivp->f((i-1)*k) );
		
			res[i] = (res[i-1] * vup - pTerm + favg) ;

		
		}
	}
};

class FittedIVP : public IVPFDM
{
public:
	FittedIVP() : IVPFDM() {}
	FittedIVP(IVP& source, long NSteps) : 	IVPFDM(source, NSteps) {}

	void calculate()
	{

		double fit, coeff;
		for (int i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
		{

			if (ivp->a(i*k) == 0.0)
				fit = 1.0;
			else
			{
				coeff = (ivp->a(i*k)) * k;
				fit = coeff / (::exp(coeff) - 1.0);
			}
	
			res[i] = ( fit*res[i-1] + (k* ivp->f(i*k)) ) / ( fit + (k* ivp->a(i*k)) );
		}
		
	
	}
};

class FittedBoxIVP : public IVPFDM
{
public:
	FittedBoxIVP() : IVPFDM() {}
	FittedBoxIVP(IVP& source, long NSteps) : 	IVPFDM(source, NSteps) {}

	void calculate()
	{

	 double fit, coeff, tmp;
		for (int i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
		{
	
			coeff = (ivp->a((i-0.5)*k)) * k;
		//	if (ivp->a((i-0.5)*k) == 0.0)
		//		fit = 2.0;
		//	else
		//	{
				tmp = ::exp(coeff);
				fit = (0.5 * coeff * (tmp + 1.0) ) / (tmp - 1.0);
		//	}

			res[i] = ( (fit - coeff*0.5)* res[i-1] + k* ivp->f((i-0.5)*k)   ) / (fit + coeff*0.5);
		}	
	
	}
};

class ExtrapEulerIVP : public IVPFDM
{
public:
	ExtrapEulerIVP() : IVPFDM() {}
	ExtrapEulerIVP(IVP& source, long NSteps) : 	IVPFDM(source, NSteps) {}

	void calculate()
	{
		// Extrapolated implicit Euler; we create two solution based on k/2 and k called
		// v(k/2) and v(k), respectively.  Then form the new array 2*v(k/2) - v(k)

		// Code can be optimised (later)
	
		// Refined mesh and solution
		Vector<double, long> res2 (2*N + 1, 1);
		double k2 = k * 0.5;


		res2[res2.MinIndex()] = (ivp -> startValue());
		for (long i = res2.MinIndex() + 1; i <= res2.MaxIndex(); i++)
		{
			res2[i] = ( res2[i-1] + (k2 * ivp->f(i*k2)) ) / ( 1.0 + (k2 * ivp->a(i*k2)) );
		}


		// Rougher mesh
		Vector<double, long> res1 (N + 1, 1);
		res1[res1.MinIndex()] = (ivp -> startValue());
		for (long ii = res1.MinIndex() + 1; ii <= res1.MaxIndex(); ii++)
		{
			res1[ii] = ( res1[ii-1] + (k* ivp->f(ii*k)) ) / ( 1.0 + (k* ivp->a(ii*k)) );
		}

		// Extrapolated solution
		for (long iii = res1.MinIndex() + 1; iii <= res1.MaxIndex(); iii++)
		{
			res[iii] = (2.0 * res2[(2*iii)]) - res1[iii];
		}
	
	}
};

#endif
