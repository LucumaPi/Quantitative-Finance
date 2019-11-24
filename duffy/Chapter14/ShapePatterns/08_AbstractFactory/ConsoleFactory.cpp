// ConsoleFactory.cpp
//
// Shape factory that creates shapes by querying the user using the console
//
//
// (C) Datasim Education BV 2001

#include "ConsoleFactory.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Circle.hpp"

ConsoleFactory::ConsoleFactory(): ShapeFactory()
{ // Default constructor
}

ConsoleFactory::ConsoleFactory(const ConsoleFactory& source): ShapeFactory(source)
{ // Copy constructor
}

ConsoleFactory::~ConsoleFactory()
{ // Destructor
}

Point* ConsoleFactory::CreatePoint() 
{ // Create point

	double x, y;

	std::cout << "Creating a point" << std::endl;

	// Input point
	std::cout<<"Input x: ";
	std::cin>>x;
	std::cout<<"Input y: ";
	std::cin>>y;

	return new Point(x, y);
}

Line* ConsoleFactory::CreateLine() 
{ // Create line

	double x1, x2, y1, y2;

	std::cout << "Creating a line" << std::endl;

	// Input start- and endpoint
	std::cout<<"Input x1: ";
	std::cin>>x1;
	std::cout<<"Input y1: ";
	std::cin>>y1;
	std::cout<<"Input x2: ";
	std::cin>>x2;
	std::cout<<"Input y2: ";
	std::cin>>y2;

	return new Line(Point(x1, y1), Point(x2, y2));
}

Circle* ConsoleFactory::CreateCircle() 
{ // Create circle

	double x, y, r;

	std::cout << "Creating a circle" << std::endl;

	// Input centerpoint and radius
	std::cout<<"Input x: ";
	std::cin>>x;
	std::cout<<"Input y: ";
	std::cin>>y;
	std::cout<<"Input radius: ";
	std::cin>>r;

	return new Circle(Point(x, y), r);
}


ConsoleFactory& ConsoleFactory::operator = (const ConsoleFactory& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;

	// Call base assignment
	ShapeFactory::operator = (source);

	return *this;
}
