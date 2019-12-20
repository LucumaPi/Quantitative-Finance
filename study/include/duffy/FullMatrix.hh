// FullMatrix.hpp
//
// Template class for normal matrices.
// A size_t is used for indexing. Indexing starts at 1.
//
// (C) Datasim Component Technology 1999

#ifndef FullMatrix_hh
#define FullMatrix_hh

#include "MatrixStructure.hh"
#include "FullArray.hh"

template <class TValue, class TA=std::allocator<TValue> >
class FullMatrix: public MatrixStructure<TValue>
{
	FullArray<FullArray<TValue, TA>, std::allocator<FullArray<TValue, TA> > > m_structure;

	// Redundant data 
	std::size_t nr, nc;

public:
	// Constructors & destructor
	FullMatrix();													// Default constructor
	FullMatrix(std::size_t rows, std::size_t columns);						// Constructor with size
	FullMatrix(const FullMatrix<TValue, TA>& source);				// Copy constructor
	virtual ~FullMatrix();											// Destructor

	// Selectors
	virtual std::size_t Rows() const;									// Number of rows
	virtual std::size_t Columns() const;									// Number of columns

	// Modifiers

	// Operators
	virtual ArrayStructure<TValue>& operator[] (std::size_t index);					// Subscripting operator
	virtual const ArrayStructure<TValue>& operator[] (std::size_t index) const;		// Subscripting operator

	FullMatrix<TValue, TA>& operator = (const FullMatrix<TValue, TA>& source);
};
#include "../../src/FullMatrix.cc"
#endif	// FullMatrix_hh