// NameDecorator.hpp
//
// Decorates a shape with a name
//
// 5 november 1998	RD	Started
//
// (C) Datasim Education BV 1998

#include "NameDecorator.hpp"
#include <typeinfo.h>

NameDecorator::NameDecorator(): ShapeDecorator()
{ // Default constructor

	name = "";
}

NameDecorator::NameDecorator(const Shape& s, const std::string& n): ShapeDecorator(s)
{ // Normal constructor

	name = n;
}

NameDecorator::NameDecorator(const NameDecorator& source): ShapeDecorator(source)
{ // Copy constructor

	name = source.name;
}

NameDecorator::~NameDecorator()
{ // Destructor
}

Shape* NameDecorator::Clone() const
{ // Create a copy of the shape

	return new NameDecorator(*this);
}

std::string NameDecorator::GetName() const
{// Return the name of the decorator
	return name;
}

// Operators
NameDecorator& NameDecorator::operator = (const NameDecorator& source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	// Call base assignment
	ShapeDecorator::operator = (source);

	name = source.name;

	return *this;
}

std::ostream& operator << (std::ostream& os, const NameDecorator& dec)
{ // Output line to ostream

	os <<"Decorator("<<dec.name<<")";
	os << "Contained shape" << typeid(*dec.getShape()).name() << std::endl;

	return os;
}
