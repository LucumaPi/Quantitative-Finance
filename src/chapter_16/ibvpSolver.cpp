// ivpSolver.cpp
//
//	Last modification dates:
//
//	DD 2003-4-5 Kick off
//	DD 2003-7-25 Predictor-corrector added
//	DD 2005-9-20 New derived classes
//	DD 2005-9-22/23 Finish off
//	DD 2005-9-26 Kick of for IBVP
//  DD 2005-10-1 next rev.
//	DD 2005-10-5 debugging
//	DD 2005-10-8 debugging
//	DD 2005-12-5 Rows are time, columns are x (null test); Also, no division 
//  by h stuff.
//
// (C) Datasim Component Technology BV 2003-2006
//


#ifndef IBVPSOlVER_CPP
#define IBVPSOLVER_CPP

#include "ibvpsolver.hpp"
#include "arraymechanisms.cpp"
#include <iostream>
using namespace std;

void IBVPFDM::initMesh(long NSteps, long JSteps)
{ // Utility function to initialise the discrete meshes

	N = NSteps;
	J = JSteps;

	k = ibvp -> trange().spread()/double(N);
	h = ibvp -> xrange().spread()/double(J);

	h2 = h*h;

	// Other numbers 
	DN = double(N);
	DJ = double(J);
	DJJ = double(J*J);

	// Allow range [A, B] in x direction and [t1, T] in t direction
	m = Mesher(ibvp -> xrange().low(), ibvp -> xrange().high(), 
					ibvp -> trange().low(), ibvp -> trange().high());

	xarr = m.xarr(J);
//	print(xarr);

	// Array in t direction
	tarr = Vector<double, long>(N+1,1);
	tarr[tarr.MinIndex()] = 0.0;

	for (long n = tarr.MinIndex()+1; n <= tarr.MaxIndex(); n++)
	{
		tarr[n] = tarr[n-1] + k;
	}


	vecOld = Vector<double, long> (xarr.Size(), xarr.MinIndex());
	vecNew = Vector<double, long> (xarr.Size(), xarr.MinIndex());

	// Rows are in time, columns in space
	res = NumericMatrix<double, long> (N+1, J+1, 1, 1);	

}

void IBVPFDM::initIC()
{ // Utility function to initialise the payoff function

	currentIndex = res.MinRowIndex();
	maxIndex = res.MaxRowIndex();

	tprev = tnow = ibvp -> trange().low();


	// Initialise at the boundaries
	vecOld[vecOld.MinIndex()] = ibvp -> BCL(0.0);
	vecOld[vecOld.MaxIndex()] = ibvp -> BCR(0.0);

	// Now initialise values in interior of interval using
	// the initial function 'IC' from the PDE
	for (int j = xarr.MinIndex()+1; j <= xarr.MaxIndex()-1; j++)
	{
		vecOld[j] = ibvp -> IC(xarr[j]);
	}

//	cout << "IC";
//	print(vecOld);
	
	res.Row(currentIndex, vecOld);
}

IBVPFDM:: IBVPFDM()
{

	ibvp = 0;

	initMesh(10, 10);

	initIC();
}

IBVPFDM:: IBVPFDM(IBVP& source, long NSteps, long JSteps)
{

	// Decide which contonuous problem to use
	ibvp = &source;

	// Crearte a mesh
	initMesh(NSteps, JSteps);

	// Initiase from the payoff function
	initIC();
}



IBVPFDM:: IBVPFDM(const IBVPFDM& source)
{	

	// Not allowed
}


IBVPFDM::~IBVPFDM()
{

}

 	
IBVPFDM&  IBVPFDM::operator = (const  IBVPFDM& source)
{

	// Not allowed

	return *this;
}



NumericMatrix<double, long>& IBVPFDM::result()
{ // The result of the calculation
	
L1:
	tnow = tprev + k;
	

	// Template Method pattern here
	
	// Variant part
	calculateBC(); // Calculate the BC at n+1

	// Variant part; pure virtual hook functions
	calculate (); // Calculate the solution at n+1

	if (currentIndex < maxIndex)
	{
	
		tprev = tnow;
		currentIndex++;
		// Now postprocess
		res.Row(currentIndex, vecNew);
		vecOld = vecNew;

		goto L1;
	}

	return res;
}

Vector<double, long> IBVPFDM::XValues() const
{ // Array of x values

	return xarr;
}

Vector<double, long> IBVPFDM::TValues() const
{ // Array of time values

	return tarr;
}


#endif

		