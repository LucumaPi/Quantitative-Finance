// testSingleton.cpp
//
// Testing the generic Singleton pattern.
//
// (C) Datasim Education BV 2004
//

#include "singleton.cpp"
#include <iostream>
using namespace std;

class AnyOldThing
{
private:
	int j;
public:
	AnyOldThing() { j = 0;}

	int coeff() const { return 0;}

};

int main()
{
	AnyOldThing* pp = Singleton<AnyOldThing>::instance();

	cout << pp -> coeff() << endl;

	return 0;
}