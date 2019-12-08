// testRanges.cpp
//
// Testing ranges in associative matrix classes
//
// (C) Datasim Education BV 2003-2006
//

//#include <duffy/AssocArray.hh>
#include <duffy/AssocMatrix.hh>
//#include <duffy/Array.hh>
//#include <duffy/ArrayMechanisms.hh>
#include <duffy/MatrixMechanisms.hh>
#include <string>

void Modifier1(double& d)
{
	d += 0.5;
}

void print (const AssocArray<long, std::string>& assArr)
{

	// Iterating in the map
	AssocArray<long, std::string>::const_iterator i = assArr.Begin();

	while (i != assArr.End())
	{
			std::cout << (*i).first << ", " << ((*i).second) << std::endl;
			
			i++;
	}

	std::cout << std::endl;
}

int main()
{

	Set<std::string> columns;
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
	AssocMatrix<double, long, std::string> myMat2(rows, columns, mat1);

	// Now work with ranges in this associative matrix
	SpreadSheetVertex<long, std::string> ul;	// Upper left
	ul.first = 1;
	ul.second = string("B");

	SpreadSheetVertex<long, std::string> lr;	// Lower right
	lr.first = 3;
	lr.second = string("D");

	SpreadSheetRange<long, std::string> myRange;
	myRange.upperLeft = ul;
	myRange.lowerRight = lr;

	myMat2.modify(myRange, Modifier1);
	print (*(myMat2.Data()));

	print(myMat2.extract(myRange));

	return 0;
}