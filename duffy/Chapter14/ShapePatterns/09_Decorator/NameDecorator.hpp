// NameDecorator.hpp
//
// Decorates a shape with a name
//
// (C) Datasim Education BV 1998

#ifndef NameDecorator_hpp
#define NameDecorator_hpp

#include "ShapeDecorator.hpp"
#include <string>

class NameDecorator: public ShapeDecorator
{
private:
	std::string name;
public:
	// The name of the contained shape
	

	// Constructors and destructors
	NameDecorator();										// Default constructor
	NameDecorator(const Shape& s, const std::string& n);	// Normal constructor
	NameDecorator(const NameDecorator& source);				// Copy constructor
	virtual ~NameDecorator();	// Destructor

	// Selectors
	std::string GetName() const;		// Return the name of the decorator

	// Special copy function to create a copy of a shape when you only have a shape pointer
	virtual Shape* Clone() const;							// Create a copy of the shape
	
	// Operators
	NameDecorator& operator = (const NameDecorator& source);
	// Friends
	friend std::ostream& operator << (std::ostream& os, const NameDecorator& l);	// Output name decorator to ostream
};

#endif // NameDecorator_hpp