// TestSwap.cpp
//
// Using generic (non-member) functions.
//
// (C) Datasim Education BV 2005
//


#include <duffy/range.hh>
#include <iostream>

template <class Numeric>
void print(const Range<Numeric>& range)
{
	std::cout << "[" << range.low() << "," << range.high() << "]\n";
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
	std::cout << j << ", " << k << std::endl;

	Range<int> range1 (0, 10);
	Range<int> range2 (20, 30);

	mySwap (range1, range2);
	print (range1);
	print (range2);

	return 0;
}
