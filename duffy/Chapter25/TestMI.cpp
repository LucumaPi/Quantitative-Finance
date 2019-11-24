// TestMI.cpp
//
// Some code the use and misuse of multiple
// inheritance.
//
// (C) Datasim Education BV 2005-2006
//

#include <iostream>
using namespace std;

// Group I: Orthogonal Base Classes
class B1
{ // Base class
public:
	B1() { cout << "B1 instantiated\n"; }
	virtual ~B1() { cout << "arrivederci B1\n";}
};

class B2
{ // Base class
public:
	B2() { cout << "B2 instantiated\n"; }
	virtual ~B2() { cout << "arrivederci B2\n";}
};


// Declaraton determines order of initialisation (from
// left to right)
class D1 : public B1, public B2 
{ // Derived class
public:
	D1() : B2(), B1() 
	{ 
		cout << "D1 instantiated\n"; 
	}

	virtual ~D1() { cout << "arrivederci D1\n";}
};

// Group II: Semi-Orthoginal Base Classes, they 
// each implement a common function
class Base1
{ // Base class
public:
	Base1() { cout << "Base1 instantiated\n"; }
	virtual ~Base1() { cout << "arrivederci Base1\n";}

	virtual void print() const {cout << "Print a Base1\n";}
};

class Base2
{ // Base class
public:
	Base2() { cout << "Base2 instantiated\n"; }
	virtual ~Base2() { cout << "arrivederci Base2\n";}

	virtual void print() const {cout << "Print a Base2\n";}

};


// Declaration determines order of initialisation (from
// left to right)
class Derived1 : public Base1, public Base2 
{ // Derived class
public:
	Derived1() : Base2(), Base1() 
	{ 
		cout << "Derived1 instantiated\n"; 
	}

	virtual ~Derived1() { cout << "arrivederci Derived1\n";}
};

// Group III: Common Base Class
class BigBase
{
public:
	
	// Common data member for all children
	int val;

	BigBase() 
	{ cout << "BigBase instantiated\n"; 
	  val = 10;
	}
	virtual ~BigBase() { cout << "arrivederci BigBase\n";}
};

class Base11 : public BigBase
{ // Base class
public:
	Base11() { cout << "Base11 instantiated\n"; }
	virtual ~Base11() { cout << "arrivederci Base11\n";}

};


class Base12 : public BigBase
{ // Base class
public:
	Base12() { cout << "Base12 instantiated\n"; }
	virtual ~Base12() { cout << "arrivederci Base12\n";}

};


// Declaration determines order of initialisation (from
// left to right)
class Derived11: public Base11, public Base12
{ // Derived class
public:
	Derived11() : Base12(), Base11() 
	{ 
		cout << "Derived11 instantiated\n"; 
	}

	virtual ~Derived11() { cout << "arrivederci Derived11\n";}
};

// Group IV: Resolving problems with Common Base Class
class BigBaseA
{
public:
	
	// Common data member for all children
	int val;

	BigBaseA() 
	{ cout << "BigBaseA instantiated\n"; 
	  val = 10;
	}
	virtual ~BigBaseA() { cout << "arrivederci BigBaseA\n";}
};

class Base11A : virtual public BigBaseA
{ // Base class
public:
	Base11A() { cout << "Base11A instantiated\n"; }
	virtual ~Base11A() { cout << "arrivederci Base11A\n";}

};


class Base12A : virtual public BigBaseA
{ // Base class
public:
	Base12A() { cout << "Base12A instantiated\n"; }
	virtual ~Base12A() { cout << "arrivederci Base12A\n";}

};


// Declaraton determines order of initialisation (from
// left to right)
class Derived11A: public Base11A, public Base12A
{ // Derived class
public:
	Derived11A() : Base12A(), Base11A() 
	{ 
		cout << "Derived11A instantiated\n"; 
	}

	virtual ~Derived11A() { cout << "arrivederci Derived11A\n";}
};


int main()
{
	D1 d1;

	Derived1 d2;
	// d2.print(); AMBIGIUOUS

	d2.Base1::print();
	d2.Base2::print();

	Derived11 d11;
	d11.Base11::val = 1;
	d11.Base12::val = 2;
	//d11.val = 3; // Ambiguous

	Derived11A d11A;
	d11A.Base11A::val = 1;
	d11A.Base12A::val = 2;
	d11A.val = 3; // No Ambiguity

	return 0;
}
