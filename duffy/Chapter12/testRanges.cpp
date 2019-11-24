// testRanges.cpp
//
// Testing ranges in associative matrix classes
//
// (C) Datasim Education BV 2003-2006
//

#include "assocarray.cpp"
#include "assocmatrix.cpp"
#include "array.cpp"
#include "arraymechanisms.cpp"
#include "matrixmechanisms.cpp"
#include <string>
using namespace std;

void Modifier1(double& d)
{
	d += 0.5;
}

void print (const AssocArray<long, string>& assArr)
{

	// Iterating in the map
	AssocArray<long, string>::const_iterator i = assArr.Begin();

	while (i != assArr.End())
	{
			cout << (*i).first << ", " << ((*i).second) << endl;
			
			i++;
	}

	cout << endl;
}

int main()
{

	Set<string> columns;
	columns.Insert("A");
	columns.Insert("B");
	columns.Insert("C");
	columns.Insert("D");

	Set<long> rows;
	rows.Insert(1);
	rows.Insert(2);
	rows.Insert(3);
	rows.Insert(4);
	
	NumericMatrix<double, long> mat1(rows.Size(), columns.Size());
	AssocMatrix<double, long, string> myMat2(rows, columns, mat1);

	// Now work with ranges in this associative matrix
	SpreadSheetVertex<long, string> ul;	// Upper left
	ul.first = 1;
	ul.second = string("B");

	SpreadSheetVertex<long, string> lr;	// Lower right
	lr.first = 3;
	lr.second = string("D");

	SpreadSheetRange<long, string> myRange;
	myRange.upperLeft = ul;
	myRange.lowerRight = lr;

	myMat2.modify(myRange, Modifier1);
	print (*(myMat2.Data()));

	print(myMat2.extract(myRange));

	return 0;
}
