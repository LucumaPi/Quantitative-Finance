// testAssocArraytypedef.cpp
//
// Testing associative arrays. In this case the new keyword
//
//		typename
//
// (C) Datasim Education BV 2003
//

#include <iostream>
#include <duffy/AssocArray.hh>
//#include <duffy/Array.hh>
#include <string>

typedef AssocArray<double, std::string> AArray;

class DD
{
public:
	typedef Array<double> DArray;
};

void print (const AArray& assArr)
{
	// Iterating in the map
	AArray::const_iterator i = assArr.Begin();

	while (i != assArr.End())
	{
		std::cout << "Element pair [" << (*i).first << "," << (*i).second << "]\n";
//		std::cout << assArr[(*i).first] << ", " ;
			i++;
	}

	std::cout << std::endl;
}

int main()
{
	std::list<std::string> names;
	names.push_back("A1");
	names.push_back("A2");
	names.push_back("A3");
	names.push_back("A4");


	Array<double> myArr(4);
	myArr[1] = 2.0;
	myArr[2] = 3.0;
	myArr[3] = 4.0;
	myArr[4] = 5.0;

	AArray myAssocArray(names, myArr);
/*
	// Iterating in the map
	print(myAssocArray);

	
	myAssocArray["A4"] = 99.99;

	print(myAssocArray);

	AssocArray<double, std::string> myAssocArray2(names, 3.14);
	print(myAssocArray2);


	Array<std::string> mystrArray(4, 1);
	mystrArray[1] = "A";
	mystrArray[2] = "B";
	mystrArray[3] = "C";
	mystrArray[4] = "D";

	Array<double> myArr3(4);
	myArr3[1] = -2.0;
	myArr3[2] = 3.0;
	myArr3[3] = 4.0;
	myArr3[4] = -5.0;

	AArray myAssocArray3(mystrArray, myArr3);
	std::cout << "Last one\n";
	print(myAssocArray3);

	// Iterating
	std::cout << "Iterating\n";
	AArray::const_iterator i;
	
	// Print every character in the vector
	for (i=myAssocArray3.Begin(); i!=myAssocArray3.End(); i++)
	{
		std::cout<< "{" << (*i).first << ", " << (*i).second << "}\n";
	}

*/
	return 0;
}