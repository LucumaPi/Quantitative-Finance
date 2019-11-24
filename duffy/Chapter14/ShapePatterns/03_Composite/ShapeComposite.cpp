// ShapeComposite.hpp
//
// Simple shape composite class using the STL list class.
// The composite stores shape pointers. It does it's own memory management.
//
// 15 september 1998	RD	Started
//
// (C) Datasim Education BV

#include "ShapeComposite.hpp"


ShapeComposite::ShapeComposite(): Shape()
{ // Default constructor

	sl=std::list<Shape*>();
}


ShapeComposite::~ShapeComposite()
{ // Destructor

	RemoveAll();
}

// Iterator functions
ShapeComposite::iterator ShapeComposite::Begin()
{ // Return iterator at begin of composite

	return sl.begin();
}

ShapeComposite::const_iterator ShapeComposite::Begin() const
{ // Return const iterator at begin of composite

	return sl.begin();
}

ShapeComposite::iterator ShapeComposite::End()
{ // Return iterator after end of composite

	return sl.end();
}

ShapeComposite::const_iterator ShapeComposite::End() const
{ // Return const iterator after end of composite

	return sl.end();
}

// Selectors
int ShapeComposite::Count() const
{ // Return the number of shapes in the composite

	return sl.size();
}

// Add functions
void ShapeComposite::AddFront(Shape* s)
{ // Add shape at the beginning of shapelist. No copy is made.

	sl.push_front(s);
}

void ShapeComposite::AddBack(Shape* s)
{ // Add shape at the end of shapelist. No copy is made.

	sl.push_back(s);
}

// Remove functions
void ShapeComposite::RemoveLast()
{ // Remove last shape

	delete sl.back();		// Delete the shape
	sl.pop_back();			// Remove shape pointer from list
}

void ShapeComposite::RemoveFirst()
{ // Remove first shape

	delete sl.front();		// Delete the shape
	sl.pop_front();			// Remove shape pointer from list
}

void ShapeComposite::RemoveAll()
{ // Remove all shapes from the list

	// Create STL list iterator
	std::list<Shape*>::iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ // Delete every shape in the list

		delete (*it);	// Delete shape
	}

	// Remove the shape pointers from the list
	sl.clear();
}

// Operators
