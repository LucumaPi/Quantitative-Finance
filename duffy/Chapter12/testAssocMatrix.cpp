// testAssocMatrix.cpp
//
// Testing associative arrays
//
// (C) Datasim Education BV 2003-2006
//

#include "assocarray.cpp"
#include "assocmatrix.cpp"
#include "array.cpp"
#include "arraymechanisms.cpp"
#include <string>
using namespace std;

void print (const AssocArray<double, string>& assArr)
{

	// Iterating in the map
	AssocArray<double, string>::const_iterator i = assArr.Begin();

	while (i != assArr.End())
	{
			cout << (*i).first << ", " << ((*i).second) << endl;
			
			i++;
	}

	cout << endl;
}

int main()
{

	Set<string> names;
	names.Insert("A1");
	names.Insert("A2");
	names.Insert("A3");
	names.Insert("A4");


	double defaultValue(0.0);

	AssocArray<double, string> myAssocArray(names, defaultValue);
	print(myAssocArray);
	myAssocArray["A4"] = 99.99;
	print(myAssocArray);


	// Test other functions
	AssocArray<double, string> myAssocArray2(myAssocArray);
	print(myAssocArray2);

	AssocMatrix<double, string, string> myMat;
	AssocMatrix<double, string, string> myMatcopy = myMat;

	NumericMatrix<double, long> mat1(names.Size(), names.Size());
	AssocMatrix<double, string, string> myMat2(names, names, mat1);


	return 0;
}
