// functionmechanisms.cpp
//
// Common functions that convert standard C functions of 1, 2 and 3
// input variable to fully discrete and semi-discrete form. These
// functions are useful when working with FDM because much of the 
// nitty-gritty work is done here and not in the code for the FDM
// schemes (which in itself is difficult enough at the best of times).
// See chapter 9 of Duffy's book.
//
// Last modification dates:
//
//	2004-3-9 DD Kick-off code
//	2004-4-6 DD New stuff and testing
//	2004-4-8 DD Code review/testing
//	2005-12-8 DD !!!!!!!!!!!!!!!!!!!!! all indices are long NOW
//
// (C) Datasim Education BV 2003-2006

#ifndef FunctionMechanisms_cpp
#define FunctionMechanisms_cpp

#include "FunctionMechanisms.hpp"


// Major group I: Converting function values at discrete points. The 
// result will be a vector, matrix or tensor depending on the number 
// of arguments (the dimension).

// N.B. All functions are scalar-valued!

// Functions of a single variable


Vector<double, long> 
	createDiscreteFunction(double (*f)(double x), const Vector<double, long>& xarr)	

{

	Vector<double, long> result(xarr.Size(), xarr.MinIndex());
	

	for (long i = result.MinIndex(); i <= result.MaxIndex(); i++)
	{

		result[i] = (*f)(xarr[i]);
	}

	return result;

}

Vector<double, long> 
	createDiscreteFunction(double (*f)(double), const Range<double>& r, int numSteps)
{

	Vector<double, long> myMesh = r.mesh(numSteps);

	return createDiscreteFunction(f, myMesh);
}



Vector<double, long> 
	createDiscreteFunction(double (*f)(double x), const Range<double>& r, double h)
{
	long nSteps = (r.high() - r.low()) / h;
	
	return createDiscreteFunction(f, r, nSteps);
}

	
// GROUP B: Functions of two variables. Here we have the option of creating a matrix
// of values in one swoop or to create a vector of values based on a single value of 
// the second variable (the so-called semi-discrete case)

NumericMatrix<double, long> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
							const Vector<double, long>& x1Arr, const Vector<double, long>& x2Arr)
{

	NumericMatrix<double, long> result(x1Arr.Size(), x2Arr.Size(), 
										x1Arr.MinIndex(), x2Arr.MinIndex());


	for (long i = result.MinRowIndex(); i <= result.MaxRowIndex(); i++)
	{
		
		for (long j = result.MinColumnIndex(); j<= result.MaxColumnIndex(); j++)
		{
				result(i, j) = (*f)(x1Arr[i], x2Arr[j]);
		}

	}

	return result;
}

NumericMatrix<double, long> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
							const Range<double>& r1, const Range<double>& r2,
							long nSteps1, long nSteps2)
{

	Vector<double, long> myMesh1 = r1.mesh(nSteps1);
	Vector<double, long> myMesh2 = r2.mesh(nSteps2);

	return createDiscreteFunction(f, myMesh1, myMesh2);

}

NumericMatrix<double, long> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
							const Range<double>& r1, const Range<double>& r2,
							double h1, double h2)
{
	long nSteps1 = (r1.high() - r1.low()) / h1;
	long nSteps2 = (r2.high() - r2.low()) / h2;

	return createDiscreteFunction(f, r1, r2, nSteps1, nSteps2);

}


// Semi-discrete calculations
Vector<double, long> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
			const Vector<double, long>& x1Arr, double x2Val)
{

	Vector<double, long> result(x1Arr.Size(), x1Arr.MinIndex());


	for (int i = result.MinIndex(); i <= result.MaxIndex(); i++)
	{

		result[i] = (*f)(x1Arr[i], x2Val);
	}

	return result;


}

// GROUP C: Functions of three variables. In general, the resulting data set would 
// be a Tensor (three-d matrix).

Tensor<double, long> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
							const Vector<double, long>& x1Arr, const Vector<double, long>& x2Arr,
							const Vector<double, long>& x3Arr)	
{
	Tensor<double, long> result(x1Arr.Size(), x2Arr.Size(), x3Arr.Size(), 
								x1Arr.MinIndex(), x2Arr.MinIndex(), x3Arr.MinIndex());


	for (long k = result.MinThirdIndex(); k <= result.MaxThirdIndex(); k++)
	{

		for (long i = result[k].MinRowIndex(); i <= result[k].MaxRowIndex(); i++)
		{
			for (long j = result[k].MinColumnIndex(); j <= result[k].MaxColumnIndex(); j++)
			{
				result(i, j, k) = (*f)(x1Arr[i], x2Arr[j], x3Arr[k]);
			}
		}
	}


	return result;

}

Tensor<double, long> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
			const Range<double>& r1, const Range<double>& r2, const Range<double>& r3,
			long nSteps1, long nSteps2, long nSteps3)
{

	Vector<double, long> myMesh1 = r1.mesh(nSteps1);
	Vector<double, long> myMesh2 = r2.mesh(nSteps2);
	Vector<double, long> myMesh3 = r3.mesh(nSteps3);

	return createDiscreteFunction(f, myMesh1, myMesh2, myMesh3);

}


Tensor<double, long> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
			const Range<double>& r1, const Range<double>& r2, const Range<double>& r3,
			double h1, double h2, double h3)
{
	long nSteps1 = (r1.high() - r1.low()) / h1;
	long nSteps2 = (r2.high() - r2.low()) / h2;
	long nSteps3 = (r3.high() - r3.low()) / h3;

	return createDiscreteFunction(f, r1, r2, r3, nSteps1, nSteps2, nSteps3);

}


// 'Single' semi-discrete
NumericMatrix<double, long> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
							const Vector<double, long>& x1Arr, const Vector<double, long>& x2Arr,
							double x3Val)
{

	NumericMatrix<double, long> result(x1Arr.Size(), x2Arr.Size(), 
										x1Arr.MinIndex(), x2Arr.MinIndex());


	for (long i = result.MinRowIndex(); i <= result.MaxRowIndex(); i++)
	{
		
		for (long j = result.MinColumnIndex(); j<= result.MaxColumnIndex(); j++)
		{
				result(i, j) = (*f)(x1Arr[i], x2Arr[j], x3Val);
		}

	}

	return result;

}


#endif