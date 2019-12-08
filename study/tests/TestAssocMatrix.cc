// testAssocMatrix.cpp
//
// Testing associative arrays
//
// (C) Datasim Education BV 2003-2006
//

#include <duffy/AssocArray.hh>
#include <duffy/AssocMatrix.hh>
#include <duffy/Array.hh>
#include <duffy/ArrayMechanisms.hh>
#include <string>

void print (const AssocArray<double, std::string>& assArr)
{

	// Iterating in the map
	AssocArray<double, std::string>::const_iterator i = assArr.Begin();

	while (i != assArr.End())
	{
			std::cout << (*i).first << ", " << ((*i).second) << std::endl;
			
			i++;
	}

	std::cout << std::endl;
}

int main()
{

	Set<std::string> names;
	names.Insert("A1");
	names.Insert("A2");
	names.Insert("A3");
	names.Insert("A4");


	double defaultValue(0.0);

	AssocArray<double, std::string> myAssocArray(names, defaultValue);
	print(myAssocArray);
	myAssocArray["A4"] = 99.99;
	print(myAssocArray);


	// Test other functions
	AssocArray<double, std::string> myAssocArray2(myAssocArray);
	print(myAssocArray2);

	AssocMatrix<double, std::string, std::string> myMat;
	AssocMatrix<double, std::string, std::string> myMatcopy = myMat;

	NumericMatrix<double, long> mat1(names.Size(), names.Size());
	AssocMatrix<double, std::string, std::string> myMat2(names, names, mat1);


	return 0;
}