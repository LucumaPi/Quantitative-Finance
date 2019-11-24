// ConsoleFactory.hpp
//
// Shape factory that creates shapes by querying the user using the console
//
// (C) Datasim Education BV 2001

#ifndef CONSOLEFACTORY_HPP
#define CONSOLEFACTORY_HPP

#include "ShapeFactory.hpp"

class ConsoleFactory: public ShapeFactory
{
private:

public:
	// Constructors and destructor
	ConsoleFactory();								// Default constructor
	ConsoleFactory(const ConsoleFactory& source);		// Copy constructor
	virtual ~ConsoleFactory();						// Destructor

	Point* CreatePoint();			// Create a point
	Circle* CreateCircle();			// Create a circle
	Line* CreateLine();				// Create a line

	// Operators
	ConsoleFactory& operator = (const ConsoleFactory& source);
};

#endif // ShapeAscii_hpp
