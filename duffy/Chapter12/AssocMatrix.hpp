// AssocMatrix.hpp
//
// Associative matrix class. In this case we access elements by 
// using non-integral indices. This is potentially a very useful class
// and it can be used in many financial applications.
// 
// The elements of the matrix are numeric because we usually work with 
// spreadsheet applications.
//
// (C) Datasim Component Technology 1999-2006

#ifndef AssocMatrix_hpp
#define AssocMatrix_hpp

#include "NumericMatrix.cpp"
#include "AssocArray.cpp"
#include "Set.cpp"
using namespace std;

// Spreadsheet-like stuff
template <class AI1, class AI2> 
		struct SpreadSheetVertex
{
		AI1 first;
		AI2 second;
};		

template <class AI1, class AI2>
		struct SpreadSheetRange
{

		SpreadSheetVertex<AI1, AI2> upperLeft;
		SpreadSheetVertex<AI1, AI2> lowerRight;

};

 

template <class V, class AI1 = string, class AI2 = string> class AssocMatrix
{ // Note that the first index is the value and second indices are 
  // 'associative' key

private: 
		
		// The essential data
		NumericMatrix<V, long>* mat;// The real data
		AssocArray<long, AI1> r;	// Rows
		AssocArray<long, AI2> c;	// Columns

		// Redundant information for performance
		Set<AI1> keysRows;
		Set<AI2> keysColumns;

public:
	// Constructors & destructor
	AssocMatrix();
	AssocMatrix(const AssocMatrix<V, AI1, AI2>& arr2);
	// Construct the map from a list of names and values
	AssocMatrix(const Set<AI1>& Rnames, const Set<AI2>& Cnames, 
									 NumericMatrix<V, long>& matrix);

	AssocMatrix<V, AI1, AI2>& operator = (const AssocMatrix<V, AI1, AI2>& ass2);

	// New overloaded indexing operator
	virtual V& operator () (const AI1& index1, const AI2& index2);

	// Modifiers
	// Change values in some range
	void modify(const SpreadSheetRange<AI1, AI2>& range, void (*f)(V& cellValue));

	// Selectors; inline for convenience and readability
	long Size() const { return str.size(); }
	NumericMatrix<V, long> extract(const SpreadSheetRange<AI1, AI2>& range);

	// Return copies of keys
	Set<AI1> RowKeys() const { return keysRows; }	
	Set<AI2> ColumnKeys() const { return keysColumns; }		
	NumericMatrix<V, long>* Data() { return mat; }

};


#endif	// AssocMatrix_hpp