// AssocMatrix.cpp
//
// Associative array class. In this case we access elements by 
// using non-integral indices.
// This is a proof-of-concept (POC) class.
//
// Last modification dates:
//
//	16 August 2003 DD kick off
//	12 January 2004 DD some new member functions
//	2006-3-24 DD use Set as control; must implement exceptions
//	2006-3-25 DD copy from ass array
//
// (C) Datasim Component Technology 1999-2006

#ifndef AssocMatrix_CC
#define AssocMatrix_CC

#include <duffy/AssocMatrix.hh>

#include <iostream>

template <class V, class AI1, class AI2> 
	AssocMatrix<V,AI1, AI2>::AssocMatrix()
{

	std::cout << "init";

	mat = 0;
	r = AssocArray<long, AI1> ();
	c = AssocArray<long, AI2> ();
	keysRows = Set<AI1>();
	keysColumns = Set<AI2>();
}

template <class V, class AI1, class AI2> 
	AssocMatrix<V,AI1, AI2>::AssocMatrix(const AssocMatrix<V,AI1, AI2>& mat2)
{

	mat = mat2.mat;
	r = mat2.r; c = mat2.c;
	keysRows = mat2.keysRows;
	keysColumns = mat2.keysColumns;

}



// Construct the map from a list of names and a REPEATED val


template <class V, class AI1, class AI2> 
AssocMatrix<V,AI1, AI2>::AssocMatrix(const Set<AI1>& Rnames, const Set<AI2>& Cnames,
								NumericMatrix<V, long>& matrix) 
			: keysRows(Rnames), keysColumns(Cnames)
{

	// Must build the associative arrays, they have the same values as the
	// indices in the matrix

	mat = &matrix;

	// Build rows
	long start = mat->MinRowIndex();
	typename Set<AI1>::const_iterator it; // Size == size of matrix
	r = AssocArray<long, AI1> (keysRows,start);

	for (it = keysRows.Begin(); it != keysRows.End(); it++)
	{
			std::cout << *it << ", " << start << std::endl;
			r[*it] = start;
			start++;
	}

	// Build columns
	start = mat->MinColumnIndex();
	typename Set<AI2>::const_iterator itc; // Size == size of matrix
	c = AssocArray<long, AI2> (keysColumns,start);

	for (itc = keysColumns.Begin(); itc != keysColumns.End(); itc++)
	{
			
			c[*itc] = start;
			start++;
	}

	// NO EXCEPTION HANDLING AT THE MOMENT
	//print(c);
}

// Change values in some range
template <class V, class AI1, class AI2> 
void AssocMatrix<V,AI1, AI2>::modify(const SpreadSheetRange<AI1, AI2>& range, void (*f)(V& cellValue))
{

	// Objective is to iterate in a range and apply a function to each 
	// element in thate range

		AI1 rmin = range.upperLeft.first;
		AI2 cmin = range.upperLeft.second;

		AI1 rmax = range.lowerRight.first;
		AI2 cmax = range.lowerRight.second;

		std::cout << rmin << ",r  " << rmax << std::endl;

		long Rmin = r[rmin]; long Rmax = r[rmax];
		long Cmin = c[cmin]; long Cmax = c[cmax];

		std::cout << Rmin << ", " << Rmax << std::endl;
		std::cout << Cmin << ", " << Cmax << std::endl;

		// Now must find the integer indices corresponding to these

		for (long ri = Rmin; ri <= Rmax; ri++)
		{
			for (long ci = Cmin; ci <= Cmax; ci++)
			{
				std::cout << ri << ", " << ci;

				f((*mat)(ri,ci));
			}
		}

}

template <class V, class AI1, class AI2> 
	NumericMatrix<V, long> AssocMatrix<V,AI1, AI2>::extract(const SpreadSheetRange<AI1, AI2>& range)
{

	// Slice a matrix
	AI1 rmin = range.upperLeft.first;
		AI2 cmin = range.upperLeft.second;

		AI1 rmax = range.lowerRight.first;
		AI2 cmax = range.lowerRight.second;

		std::cout << rmin << ",r  " << rmax << std::endl;

		long Rmin = r[rmin]; long Rmax = r[rmax];
		long Cmin = c[cmin]; long Cmax = c[cmax];

		std::cout << Rmin << ", " << Rmax << std::endl;
		std::cout << Cmin << ", " << Cmax << std::endl;

		int d;
		std::cin >> d;

		// Now must find the integer indices corresponding to these
		NumericMatrix<V, long> result(Rmax-Rmin+1, Cmax-Cmin+1, Rmin, Cmin);

		for (long ri = Rmin; ri <= Rmax; ri++)
		{
			for (long ci = Cmin; ci <= Cmax; ci++)
			{
					result(ri, ci) = (*mat)(ri, ci);
			}
		}

		return result;

}




template <class V, class AI1, class AI2> 
	AssocMatrix<V,AI1, AI2>& AssocMatrix<V,AI1, AI2>::operator = (const AssocMatrix<V,AI1, AI2>& mat2)
{
	if (&mat == this)
		return *this;

	mat = mat2.mat;
	r = mat2.r; c = mat2.c;
	keysRows = mat2.keysRows; keysColumns = mat2.keysColumns;
	
	return *this;

}



// New overloaded indexing operator
template <class V, class AI1, class AI2>
	V& AssocMatrix<V,AI1, AI2>::operator () (const AI1& index1, const AI2& index2)
{

	long rowIndex = r[index1];
	long colIndex = c[index2];

	return (*mat)(rowIndex, colIndex);
}


#endif	// AssocMatrix_CC