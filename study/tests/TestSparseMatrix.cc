// testSparseMatrix.cpp
//
// Testng properties of maps: creating sparse matrices
//
// 2006-3-27 DD Kick-off
// 2006-3-28 DD Modified for a simple sparse matrix class
// (can be optimised!!)
//
// (C) Datasim Education BV 2003-2006
//

#include <iostream>
#include <vector>
#include <map>
#include <string>

// Specific data types, can be generalised
typedef std::map<int, double> SparseRow;

template <int N> struct SparseMatrix
{
	std::map<int, SparseRow> data;

};

template <int N> void print(SparseMatrix<N>& sm)
{
	SparseRow sr;
	SparseRow::const_iterator it;//maybe optional typename

	for (int row = 0; row < N; row++)
	{
		SparseRow sr = sm.data[row];
	
		// Now iterate over row
		for (it = sm.data[row].begin(); it != sm.data[row].end(); it++)
		{
			std::cout << (*it).second << ", ";
		}
		std::cout << std::endl;
		
	}

}

	
int main()
{

	// Initialise the each row

	const int N = 5;

	SparseRow current;
	current.insert(std::pair<int, double> (0, -2.0));
	current.insert(std::pair<int, double> (1, 1.0));
	SparseMatrix<N> sparseMat;
	sparseMat.data[0] = current;
	
	int currentIndex = 0;

	for (int row = 1; row < N - 1; row++)
	{
		//Insert 3 elements.
		current.clear();
		current.insert(std::pair<int, double> (currentIndex, 1.0));
		current.insert(std::pair<int, double> (currentIndex + 1, -2.0));
		current.insert(std::pair<int, double> (currentIndex + 2, 1.0));

		sparseMat.data[row] = current;
	
		currentIndex++;
	}

	current.clear();
	current.insert(std::pair<int, double> (N - 2, 1.0));
	current.insert(std::pair<int, double> (N - 1, -2.0));
	sparseMat.data[N - 1] = current;

	print(sparseMat);

	return 0;
}