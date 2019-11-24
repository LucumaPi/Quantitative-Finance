// ShapeDecorator.hpp
//
// Base class for shape decorators
//
// (C) Datasim Education BV 1998

#ifndef ShapeDecorator_hpp
#define ShapeDecorator_hpp

#include "Shape.hpp"

class ShapeDecorator: public Shape
{
private:
	Shape* shape;

public:
	// Constructors and destructors
	ShapeDecorator();								// Default constructor
	ShapeDecorator(const Shape& s);					// Normal constructor
	ShapeDecorator(const ShapeDecorator& source);	// Copy constructor
	virtual ~ShapeDecorator();						// Destructor

	// Selectors
	Shape* getShape() const;						// Get the contained shape
	
	// Operators
	ShapeDecorator& operator = (const ShapeDecorator& source);
};

#endif // ShapeDecorator_hpp