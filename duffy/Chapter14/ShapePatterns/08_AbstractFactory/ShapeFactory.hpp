// ShapeFactory.hpp
//
// Base class for shape factories
//
// (C) Datasim Education BV 1998

#ifndef ShapeFactory_hpp
#define ShapeFactory_hpp

#include "Shape.hpp"
#include "Point.hpp"
#include "Circle.hpp"
#include "Line.hpp"

class ShapeFactory
{
private:
public:
	// Constructors and destructor
	ShapeFactory();								// Default constructor
	ShapeFatory(const ShapeFactory& source);	// Copy constructor
	virtual ~ShapeFactory();					// Destructor

	virtual Point* CreatePoint() = 0;			// Create a point
	virtual Circle* CreateCircle() = 0;			// Create a circle
	virtual Line* CreateLine() = 0;				// Create a line


	// Operators
	ShapeFactory& operator = (const ShapeFactory& source);
};

#endif // ShapeFactory_hpp
