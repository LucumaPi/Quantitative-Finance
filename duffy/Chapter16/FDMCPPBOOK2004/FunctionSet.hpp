// FunctionSet.hpp
//
// Class represeting a heterogenous list of functions. This is a special 
// class because it allows us to add and remove functions from a function list. 
// The class is specialised inthe sense that it works with the class of 
// scalar-valued functions 
//	
//		ScalarValuedFunction: n-space to 1-space mapping
//
//	It is possible to give each function a name. This is useful for identification purposes.
//
// This class is useful when modellling coefficients of differential equations, for example.
//
// (C) Datasim Education BV 2002

#ifndef FunctionSet_hpp
#define FunctionSet_hpp

#include "detfunction.cpp"
#include <list>
#include <string>

template <class D, class R, class I> class FunctionVisitor;

using namespace std;

template <class D, class R, class I> class FunctionSet
{
private:
	string nam;		// The name ofthe logicaly-related functions
	// The FunctionSet list using the STL list
	list<pair<string, ScalarValuedFunction<D,R,I> > > sl;
	
	FunctionSet();
	FunctionSet<D, R, I>(const FunctionSet<D, R,I>& source);	// Copy constructor

public:
	// User can use the STL iterator
	typedef typename list<pair<string, ScalarValuedFunction<D,R,I> > >::iterator iterator;
	typedef typename list<pair<string, ScalarValuedFunction<D,R,I> > >::const_iterator const_iterator;

	// Constructors and destructor
	FunctionSet(const string& name);		// Default constructor + name 

	virtual ~FunctionSet();				// Destructor

	// Iterator functions
    iterator Begin();					// Return iterator at begin of composite
	const_iterator Begin() const;		// Return const iterator at begin of composite
	iterator End();						// Return iterator after end of composite
    const_iterator End() const;			// Return const iterator after end of composite

	// Selectors
	I Count() const;					// The number of functions in the list
	Array<string> names() const;		// The names of the functions

	// Add and remove functions
	void add(const string& name, const ScalarValuedFunction<D,R,I>& scf); // C++ function	
	void add(const string& name, R (*f)(const Vector<D,I>& x) );				
	void remove(const string& name);				// Remove function with given name
	void name(const string& newName);				// Change he name of the group

	// Operators
	FunctionSet<D,R,I>& operator = (const FunctionSet<D,R,I>& source);

	// Calculate the function
	Vector<R, I> calculate(const Vector<D,I>& x) const; 

	// Adding extra functionality
	void accept(FunctionVisitor<D,R,I>& v);		// Extending functionality (Visitor)

};

#endif	// FunctionSet_hpp
