// IEulerIbvpSolver.hpp
//
// Solvers for initial boundary value problems. We 
// use an abstract base class; derived class implement
// specific behaviour.
//
// 2005-9-36 DD kick-off
// 2005-10-1 DD next rev.
// 2005-10-11 DD last revision?
// 2005-11-30 DD new cpp file
// 2006-1-10 fixng + aligning indices
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef IEulerBVPSOLVER_CPP
#define IEulerBVPSOLVER_CPP

#include "IEulerIbvpSolver.hpp"
#include "arraymechanisms.cpp"

ImplicitEulerIBVP::ImplicitEulerIBVP(): IBVPFDM()
{

		// !!! number of unknowns is J - 1 (Dirichlet)
		A = Vector<double, long> (J-1, 1);
		B = Vector<double, long> (J-1, 1);
		C = Vector<double, long> (J-1, 1);

		F = Vector<double, long> (J-1, 1);

}

ImplicitEulerIBVP::ImplicitEulerIBVP(IBVP& source, long NSteps, long JSteps)
		: IBVPFDM(source, NSteps, JSteps)
{
		// !!! number of unknowns is J - 1 (Dirichlet)
		A = Vector<double, long> (J-1, 1);
		B = Vector<double, long> (J-1, 1);
		C = Vector<double, long> (J-1, 1);

		F = Vector<double, long> (J-1, 1);

}

void ImplicitEulerIBVP::calculateBC()
{ // Tells how to calculate sol. at n+1

		vecNew[vecNew.MinIndex()] = ibvp->BCL(tnow);
		vecNew[vecNew.MaxIndex()] = ibvp->BCR(tnow);

//		cout << "IC";
//		print(vecOld);
//		int kk;
//		cin >> kk;

}

void ImplicitEulerIBVP::calculate()
{ // Tells how to calculate sol. at n+1

		// In general we need to solve a tridiagonal system

		double tmp1, tmp2;
		
		for (long i = F.MinIndex(); i <= F.MaxIndex(); i++)
		{
			tmp1 = (k*ibvp->diffusion(xarr[i+1],tnow ));
			tmp2 = (0.5 * k * h* (ibvp->convection(xarr[i+1], tnow)));

			// Coefficients of the U terms
			A[i] = tmp1 - tmp2;
			B[i] = -h2 - (2.0*tmp1) + (k*h2*(ibvp->zeroterm(xarr[i+1],tnow)));
			C[i] = tmp1 + tmp2;

			F[i] = h2*(k * (ibvp -> RHS(xarr[i+1], tnow)) - vecOld[i+1]); //?&
		}

//		cout << "Coeficients";
//		print(A); print(B); print(C); print(F);
//		int kl; cin >> kl;

		// Correction term for RHS
		F[1]	-= A[1] * vecNew[vecNew.MinIndex()];
		F[J-1]	-= C[J-1] * vecNew[vecNew.MaxIndex()] ;


		// Now solve the system of equations
		LUTridiagonalSolver<double, long> mySolver(A, B, C, F);

		// The matrix must be diagonally dominant; we call the
		// assert macro and the programs stops

		assert (mySolver.diagonallyDominant() == true);
		
		Vector <double, long> solution = mySolver.solve();

		for (long ii = vecNew.MinIndex()+1; ii <= vecNew.MaxIndex()-1; ii++)
		{
			vecNew[ii] = solution[ii-1];
		}
			
		//print(vecNew);
		//int k; cin >> k;
}

#endif