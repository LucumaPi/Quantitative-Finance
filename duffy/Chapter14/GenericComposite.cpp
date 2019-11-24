// GenericComposite.hpp
//
// Simple Generic composite class using the STL list class.
// The composite stores Generic pointers. It does it's own memory management.
//
// 15 september 1998	RD	Started
// 2006-4-14 DD modified for creation of a generic composite
// 2006-4-27 DD remove an element from composite
//
// (C) Datasim Education BV

#ifndef GenericComposite_cpp
#define GenericComposite_cpp


#include "GenericComposite.hpp"

template <class T>
void GenericComposite<T>::Copy(const GenericComposite<T>& source)
{ // Copy the source composite to this Generic composite

	// Create STL list iterator
	std::list<T*>::const_iterator it;

	for (it=source.sl.begin(); it!=source.sl.end(); it++)
	{ // Copy the whole list

		// Add a copy of the Generic to our list
		sl.push_back((*it)->Clone());
	}
}

template <class T>
GenericComposite<T>::GenericComposite<T>(): T()
{ // Default constructor

	sl=std::list<T*>();
}

template <class T>
GenericComposite<T>::GenericComposite(const GenericComposite<T>& source): T(source)
{ // Copy constructor

	sl=std::list<T*>();
	Copy(source);
}
template <class T>
GenericComposite<T>::~GenericComposite()
{ // Destructor

	RemoveAll();
}

// Iterator functions
template <class T>
GenericComposite<T>::iterator GenericComposite<T>::Begin()
{ // Return iterator at begin of composite

	return sl.begin();
}

template <class T>
GenericComposite<T>::const_iterator GenericComposite<T>::Begin() const
{ // Return const iterator at begin of composite

	return sl.begin();
}

template <class T>
GenericComposite<T>::iterator GenericComposite<T>::End()
{ // Return iterator after end of composite

	return sl.end();
}

template <class T>
GenericComposite<T>::const_iterator GenericComposite<T>::End() const
{ // Return const iterator after end of composite

	return sl.end();
}

// Selectors
template <class T>
int GenericComposite<T>::Count() const
{ // Return the number of Generics in the composite

	return sl.size();
}

// Add functions
template <class T>
void GenericComposite<T>::AddFront(T& s)
{ // Add Generic at the beginning of Genericlist. No copy is made.

	sl.push_front(&s);
}

template <class T>
void GenericComposite<T>::AddBack(T& s)
{ // Add Generic at the end of Genericlist. No copy is made.

	sl.push_back(&s);
}

// Remove functions
template <class T>
void GenericComposite<T>::RemoveLast()
{ // Remove last Generic

	delete sl.back();		// Delete the Generic
	sl.pop_back();			// Remove Generic pointer from list
}

template <class T>
void GenericComposite<T>::RemoveFirst()
{ // Remove first Generic

	delete sl.front();		// Delete the Generic
	sl.pop_front();			// Remove Generic pointer from list
}

template <class T>
	void void GenericComposite<T>::Remove(T& t)
{ // Remove pointer that is address of t

	// Locate the pointer to t in the list
	list<T*>::iterator it = find(sl.begin(), sl.end(), &t);
	
	if (it != sl.end())
	{
		erase(it);
	}
	
}



template <class T>
void GenericComposite<T>::RemoveAll()
{ // Remove all Generics from the list

	// Create STL list iterator
	std::list<T*>::iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ // Delete every Generic in the list

		delete (*it);	// Delete Generic
	}

	// Remove the Generic pointers from the list
	sl.clear();
}

// Operators
template <class T>
// Operators
GenericComposite<T>& GenericComposite<T>::operator = (const GenericComposite<T>& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;

	// First clear our list
	RemoveAll();

	// Base class assignment
	Generic::operator = (source);

	// Copy other list
	Copy(source);

	return *this;
}

#endif