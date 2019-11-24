// GenericComposite.hpp
//
// Simple Generic composite class using the STL list class.
// The composite stores Generic pointers. It does it's own memory management.
//
// (C) Datasim Education BV

#ifndef GenericComposite_hpp
#define GenericComposite_hpp

#include "Shape.hpp"

#include <list>
using namespace std;

template <class T> 
	class GenericComposite: public T
{
private:
	// The Genericlist using the STL list
	std::list<T*> sl;
	
	GenericComposite(const GenericComposite& source);	// Copy constructor
	void Copy(const GenericComposite<T>& source);

public:
	// User can use the STL iterator
	typedef std::list<T*>::iterator iterator;
	typedef std::list<T*>::const_iterator const_iterator;

	// Constructors and destructor
	GenericComposite();								// Default constructor

	virtual ~GenericComposite();						// Destructor

	// Iterator functions
    iterator Begin();								// Return iterator at begin of composite
	const_iterator Begin() const;					// Return const iterator at begin of composite
	iterator End();									// Return iterator after end of composite
    const_iterator End() const;						// Return const iterator after end of composite

	// Selectors
	int Count() const;								// The number of Generics in the list

	// Add functions
	void AddFront(T& s);							// Add Generic at the beginning of Genericlist. No copy is made but composite takes care of deletion.
	void AddBack(T& s);							// Add Generic at the end of Genericlist. No copy is made but composite takes care of deletion.

	// Remove functions
	void RemoveFirst();								// Remove first Generic
	void RemoveLast();								// Remove last Generic
	void RemoveAll();								// Remove all Generics from the list

	// Operators
	GenericComposite& operator = (const GenericComposite& source);

	// Generic Visitor pattern
	template <class S>
		void accept(S& v) {v.visit(*this);}

};

#endif	// GenericComposite_hpp
