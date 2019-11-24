// ShapeComposite.hpp
//
// Simple shape composite class using the STL list class.
// The composite stores shape pointers. It does it's own memory management.
//
// 15 september 1998	RD	Started
//
// (C) Datasim Education BV

#include "ShapeComposite.hpp"
#include "ShapeVisitor.hpp"

void ShapeComposite::Copy(const ShapeComposite& source)
{ // Copy the source composite to this shape composite

	// Create STL list iterator
	std::list<Shape*>::const_iterator it;

	for (it=source.sl.begin(); it!=source.sl.end(); it++)
	{ // Copy the whole list

		// Add a copy of the shape to our list
		sl.push_back((*it)->Clone());
	}
}

ShapeComposite::ShapeComposite(): Shape()
{ // Default constructor

	sl=std::list<Shape*>();
}

ShapeComposite::ShapeComposite(const ShapeComposite& source): Shape(source)
{ // Copy constructor

	sl=std::list<Shape*>();
	Copy(source);
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

// Special copy function to create a copy of a shape when you only have a shape pointer
Shape* ShapeComposite::Clone() const
{// Create a copy of the shape
	return new ShapeComposite(*this);
}

void ShapeComposite::Accept(ShapeVisitor& v)
{// Accept a visitor
	v.Visit(*this);
}

// Operators
ShapeComposite& ShapeComposite::operator = (const ShapeComposite& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;

	// First clear our list
	RemoveAll();

	// Base class assignment
	Shape::operator = (source);

	// Copy other list
	Copy(source);

	return *this;
}
