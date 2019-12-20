// ExcelMechanisms.hpp
//
// Useful functions for use with Excel.
//
// (C) Datasim Education BV 2005-2006
//

#ifndef ExcelMechanisms_HH
#define ExcelMechanisms_HH

#include "Vector.hh"
#include "NumericMatrix.hh"
#include "Tensor.hh"
#include "StringConversions.hh"
#include <string>
#include <list>

// Print one line graph
void printOneExcel(const Vector<double, long>& x,						
					const Vector<double, long>& functionResult,
					const std::string& title = std::string("Title"), 
					const std::string& horizontal = std::string("X"), 
					const std::string& vertical = std::string("Y"),
					const std::string& legend = std::string("*"));


// Print multiple lines on one graph
void printInExcel(const Vector<double, long>& x,						// X array
					const std::list<std::string>& labels,					// Names of each vector
					const std::list<Vector<double, long> >& functionResult,	// The list of Y values
					const std::string& title = std::string("Title"),
					const std::string& horizontal = std::string("X"), 
					const std::string& vertical = std::string("Y"));

// Print a matrix as cell
void printMatrixInExcel(const NumericMatrix<double, long>& matrix,
				 const Vector<double, long>& xarr, const Vector<double, long>& yarr, 
				 const std::string& SheetName = std::string("Matrix"));

// Print a matrix's rows as line graphs
void printMatrixChartsInExcel(int freq, const NumericMatrix<double, long>& matrix,
				 const Vector<double, long>& rowAarr, const Vector<double, long>& colArr,
				 const std::string& SheetName = std::string("Matrix"));

// Print an array of matrices
void printTensorInExcel(const Tensor<double, long>& tensor, long freq = 1);

// Print each matrix in tensor with associated row/column labels
void printTensorInExcel(const Tensor<double, long>& tensor,
						const Vector<double, long>& xarr, const Vector<double, long>& yarr, 
						const std::string& SheetName = std::string("Tensor"), long freq = 1);

// Print the vector that is the difference of two vectors
void printDifferenceInExcel(const Vector<double, long>& x,	const Vector<double, long>& y1,					
					const Vector<double, long>& y2,
					const std::string& title = std::string("Difference"), 
					const std::string& horizontal = std::string("X Values"), 
					const std::string& vertical = std::string("Y Values"),
					const std::string& legend = std::string("*"), long freq = 1);

// Differences of two matrices
void printMatrixDifferenceInExcel(const NumericMatrix<double, long>& matrix1,
						const NumericMatrix<double, long>& matrix2,
				 const Vector<double, long>& xarr, const Vector<double, long>& yarr, 
				 const std::string& SheetName = std::string("Matrix"));
// Print discrete values of a continuous function on interval [A,B]
void printDiscreteFunctionValues(double (*f) (double x), double A, double B,long nSteps, 
					const std::string& title, 
					const std::string& horizontal, 	const std::string& vertical,
					const std::string& legend);

#endif