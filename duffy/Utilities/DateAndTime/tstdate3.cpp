// tstdat3.cpp
//
// Conversion stuff for dates
//
// (C) Datasim BV 1993-2004

#include "DatasimDate.hpp"
#include "array.cpp"
#include "datetimemechanisms.hpp"

#include <string>		// DO NOT FORGET
#include <iostream>
using namespace std;

int main()
{

	DatasimDate today;

	print(today, STD); cout << endl;
	print(today, EUROPEAN); cout << endl;
	print(today, ANSI); cout << endl;
	print(today, AMERICAN); cout << endl;

	cout << "Dates as strings\n";
	string s1 = DateToString(today, STD);
	cout << s1.c_str() << endl;

	string s2 = DateToString(today, EUROPEAN);
	cout << s2.c_str() << endl;

	string s3 = DateToString(today, ANSI);
	cout << s3.c_str() << endl;

	string s4 = DateToString(today, AMERICAN);
	cout << s4.c_str() << endl;



	cout << "Dates as strings with MY formatter\n";

	char form[] = "[%D]-[%MM]-[%YYYY]\0";
	
	s1 = DateToString(today, STD);
	cout << s1.c_str() << endl;

	s2 = DateToString(today, EUROPEAN, form);
	cout << s2.c_str() << endl;

	s3 = DateToString(today, ANSI,form);
	cout << s3.c_str() << endl;

	s4 = DateToString(today, AMERICAN, form);
	cout << s4.c_str() << endl;


	return 0;

}