// PrintVisitor.cpp
//
// Shape visitor that prints the shapes
//
// 4 november 1998	RD	Started
//
// (C) Datasim Education BV 1998

#include "PrintVisitor.hpp"
#include "Common.hpp"

// Constructors and Destructor
PrintVisitor::PrintVisitor(): ShapeVisitor()
{ // Default constructor
}

PrintVisitor::PrintVisitor(const PrintVisitor& source): ShapeVisitor(source)
{ // Copy constructor
}

PrintVisitor::~PrintVisitor()
{ // Destructor
}


// The visit functions
void PrintVisitor::Visit(Point& p)
{ // Visit point

	// Print point
	std::cout<<p;
}

void PrintVisitor::Visit(Line& l)
{ // Visit line

	std::cout<<l;
}

void PrintVisitor::Visit(Circle& c)
{ // Visit circle

	std::cout<<c;
}

void PrintVisitor::Visit(ShapeComposite& sc)
{ // Visit shape composite

	// Since we must print information between shapes we cannot just call the base visitor function

	ShapeComposite::iterator it;

	std::cout<<"ShapeComposite(";
	// Send all shapes in the composite to the visitor
	for (it=sc.Begin(); it!=sc.End(); it++)
	{
		// Separate shapes with comma
		if (it!=sc.Begin()) std::cout<<", ";
		(*it)->Accept(*this);
	}

	std::cout<<")";
}

void PrintVisitor::Visit(NameDecorator& nd)
{ // Visit NameDecorator

	std::cout<<"{Name: "<<nd.GetName()<<", Shape: ";
	ShapeVisitor::Visit(nd);
	std::cout<<"}";
}


// Operators
PrintVisitor& PrintVisitor::operator = (const PrintVisitor& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;

	// Call base assignment
	ShapeVisitor::operator = (source);

	return *this;
}