// FunctionSet.cpp
//
// Composite function class
//
//	7 November 2002 DD Kick-of
//
// (C) Datasim Education BV
#include "stdafx.h"
#ifndef FunctionSet_cpp
#define FunctionSet_cpp

#include "FunctionSet.hpp"

template <class D, class R,  class I>
FunctionSet<D,R,I>::FunctionSet()
{ // Default constructor

	nam = "";
	sl= list<pair<string, ScalarValuedFunction<D,R,I> > >();
}

template <class D, class R,  class I>
FunctionSet<D,R,I>::FunctionSet(const string& name)
{ // Default constructor

	nam = name;
	sl = list<pair<string, ScalarValuedFunction<D,R,I> > >();
}

template <class D, class R,  class I>
FunctionSet<D,R,I>::FunctionSet(const FunctionSet<D, R,I>& source)
{ // Copy constructor
	
		sl = source.sl;
}


template <class D, class R,  class I>
FunctionSet<D,R,I>::~FunctionSet()
{ // Destructor


}

// Iterator functions
template <class D, class R,  class I>
typename FunctionSet<D,R,I>::iterator FunctionSet<D,R,I>::Begin()
{ // Return iterator at begin of composite

	return sl.begin();
}

template <class D, class R,  class I>
typename FunctionSet<D,R,I>::const_iterator FunctionSet<D,R,I>::Begin() const
{ // Return const iterator at begin of composite

	return sl.begin();
}

template <class D, class R,  class I>
typename FunctionSet<D,R,I>::iterator FunctionSet<D,R,I>::End()
{ // Return iterator after end of composite

	return sl.end();
}

template <class D, class R,  class I>
typename FunctionSet<D,R,I>::const_iterator FunctionSet<D,R,I>::End() const
{ // Return const iterator after end of composite

	return sl.end();
}

// Selectors
template <class D, class R,  class I>
I FunctionSet<D,R,I>::Count() const
{ // Return the number of functions in the composite

	return I(sl.size());
}

template <class D, class R,  class I>
	Array<string> FunctionSet<D,R,I>::names() const
{ // The names of the functions

	// Create STL list iterator
	const_iterator it;

	Array<string> result(sl.size(), 1);

	I i = 1;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ // Iterate over each function in the composite and call ITS calculate

		result[i] = (*it).first;
		i++;
	}

	return result;
		
}

// Add functions
template <class D, class R,  class I>
void FunctionSet<D,R,I>::add(const string& name, const ScalarValuedFunction<D,R,I>& scf)
{ // Add a named function to the list

	pair<string, ScalarValuedFunction<D,R,I> > curr;
	curr.first = name;
	curr.second = scf;

	sl.push_front(curr);
}

template <class D, class R,  class I>
	void FunctionSet<D,R,I>::add(const string& name, R (*f)(const Vector<D,I>& x) )
{ // Add a named C_function to the function set

	ScalarFunction<Vector<D,I>, R, I> scf(f);
	ScalarValuedFunction<D,R,I> svf (scf);

	add(name, svf);

}


template <class D, class R,  class I>
void FunctionSet<D,R,I>::remove(const string& name)
{ // Remove a function with a given name

	// Create STL list iterator
	iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ // Delete every function the list

		if ((*it).first == name)
		{

			delete (*it);	// Delete function
		}
	}

}


template <class D, class R,  class I>
	void FunctionSet<D,R,I>::name(const string& newName)
{ // Change he name of the group

		nam = newName;
}



template <class D, class R,  class I>
	Vector<R, I> FunctionSet<D,R,I>::calculate(const Vector<D,I>& x) const
{

	// Create STL list iterator
	const_iterator it;

	Vector<R, I> result(sl.size(), 1);

	I i = 1;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ // Iterate over each function in the composite and call ITS calculate

		result[i] = (*it).second.calculate(x);
		i++;
	}

	return result;
}


// Operators
template <class D, class R,  class I>
	FunctionSet<D,R,I>& FunctionSet<D,R,I>::operator = (const FunctionSet<D,R,I>& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;

	// First clear our list
	removeAll();

	
	// Copy other list
	Copy(source);

	return *this;
}

template <class D, class R, class I>  
 void FunctionSet<D,R,I>::accept(FunctionVisitor<D,R,I>& v) 
{ // Make a copy of myself

	v.visit(*this);
}

#endif