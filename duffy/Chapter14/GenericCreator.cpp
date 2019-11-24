// GenericCreator.cpp
//
// The Abstract Factory to end all abstract factories?
//
// Policy classes, policies and required interaces are 
// important in this context.
//
// (C) Datasim Education BV 2006
//

#include <iostream>
#include "Point.hpp"
using namespace std;

template <class T> class AbstractFactory
{
public:
		virtual T* Create() = 0;

};

template <class T> class HeapCreator : public AbstractFactory<T>
{
public:
		virtual T* Create()
		{
			return new T();
		}

};

template <class T> class PrototypeCreator : public AbstractFactory<T>
{
private:
		T* proto;
public:
	PrototypeCreator () {proto = 0;}
	PrototypeCreator (T* prototype) { proto = prototype; }

	virtual T* Create()
	{
			return new T(*proto);
	}

};

template <class T>
	AbstractFactory<T>* GetFactory()
{
	int choice = 1;
	cout << "Factories: 1) Heap 2) Prototype ";
	cin >> choice;

	if (choice == 1)
	{
		return new HeapCreator<T>();
	}
	else
	{
		return new PrototypeCreator<T>();
	}
}

int main()
{

	HeapCreator<int> hfac;
	int* myInt = hfac.Create();
	cout << *myInt << endl;

	HeapCreator<Point> hfac2;
	Point* myPt = hfac2.Create();
	cout << (*myPt).X() << ", " << (*myPt).Y() << endl;

	AbstractFactory<double>* fac = GetFactory<double>();

	return 0;
}