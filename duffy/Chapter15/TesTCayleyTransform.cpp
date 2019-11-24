// TestCayleyTransform.cpp
//
// (C) Datasim Education BV 2006

#include <math.h>
#include <iostream>
using namespace std;

int main()
{

	double R1 = 2.0;
	double R2 = 4.44;

	long N = 1000000000;
/*
	for (long j = 1; j <= N; j++)
	{
		//cout << j << " ";
		double u1 = ::exp(R1 + R2);
		double d1 = ::exp(R1 - R2);
	}
*/
	cout << "finished 1\n";
	int k; cin >> k;

	// Cayley transform
	double z1 = (R1 + R2);
	double z2 = (R1 - R2);

	for (long i = 1; i <= N; i++)
	{
		double u2 = (2.0 + z1) / (2.0 - z1);
		double d2 = (2.0 + z2) / (2.0 - z2);
	}
	
	cout << "finished 2\n";

	return 0;
}