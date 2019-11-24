// ShapeComposite.hpp
//
// Simple shape composite class using the STL list class.
// The composite stores shape pointers. It does it's own memory management.
//
// (C) Datasim Education BV

#ifndef ShapeComposite_hpp
#define ShapeComposite_hpp

#include "Shape.hpp"

#include <list>
class ShapeComposite: public Shape
{
private:
	// The shapelist using the STL list
	std::list<Shape*> sl;
	
	void Copy(const ShapeComposite& source);		// Copy the source composite to this shape composite



public:
	// User can use the STL iterator
	typedef std::list<Shape*>::iterator iterator;
	typedef std::list<Shape*>::const_iterator const_iterator;

	// Constructors and destructor
	ShapeComposite();								// Default constructor
	ShapeComposite(const ShapeComposite& source);	// Copy constructor
	virtual ~ShapeComposite();						// Destructor

	// Iterator functions
    iterator Begin();								// Return iterator at begin of composite
	const_iterator Begin() const;					// Return const iterator at begin of composite
	iterator End();									// Return iterator after end of composite
    const_iterator End() const;						// Return const iterator after end of composite

	// Selectors
	int Count() const;								// The number of shapes in the list

	// Add functions
	void AddFront(Shape* s);						// Add shape at the beginning of shapelist. No copy is made but composite takes care of deletion.
	void AddBack(Shape* s);							// Add shape at the end of shapelist. No copy is made but composite takes care of deletion.

	// Remove functions
	void RemoveFirst();								// Remove first shape
	void RemoveLast();								// Remove last shape
	void RemoveAll();								// Remove all shapes from the list

	// Special copy function to create a copy of a shape when you only have a shape pointer
	virtual Shape* Clone() const;		// Create a copy of the shape

	void Accept(ShapeVisitor& v);	// Accept a visitor

	// Operators
	ShapeComposite& operator = (const ShapeComposite& source);
};

#endif	// ShapeComposite_hpp
