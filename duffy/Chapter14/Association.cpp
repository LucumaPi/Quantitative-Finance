// Association.cpp
//
// Show use of Association
//
// (C) Datasim Education BV 2005-2006

#include <iostream>
using namespace std;


class C1
{ // 'Associate' class
private:
		int* iarr;
		int size;
public:
	C1(int N)
	{ 
		size = N;
		iarr = new int[size];
		for (int j = 0; j < N; j++)
		{
			iarr[j] = double(N-j);
		}
	}

	double getValue() const {return iarr[0]/double(size);}
	~C1() { delete [] iarr; }
};

class C2
{
private:
		C1* ass;
public:
	C2(C1& associate) { ass = &associate; }

	// The function that delegates
	double clientValue() const
	{
		double tmp = ass -> getValue();

		// Modify for current situation
		return tmp * 100.0;
	}
};

int main()
{
	int arraySize = 10;
	C1 myAssociate(arraySize);
	
	C2 myClient(myAssociate);

	cout << "Client value: " << myClient.clientValue() << endl;

	return 0;
}
