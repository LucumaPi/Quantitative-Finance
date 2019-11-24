// TestSwap.cpp
//
// Using generic (non-member) functions.
//
// (C) Datasim Education BV 2005
//


#include "Range.cpp"

#include <iostream>
using namespace std;

template <class Numeric>
void print(const Range<Numeric>& range)
{
	cout << "[" << range.low() << "," << range.high() << "]\n";
}

template <class V> void mySwap(V& v1, V& v2)
{

	V tmp = v2;
	v2 = v1;

	v1 = tmp;
}

int main()
{
	int j = 10;
	int k = 20;

	mySwap(j, k);
	cout << j << ", " << k << endl;

	Range<int> range1 (0, 10);
	Range<int> range2 (20, 30);

	mySwap (range1, range2);
	print (range1);
	print (range2);

	return 0;
}
