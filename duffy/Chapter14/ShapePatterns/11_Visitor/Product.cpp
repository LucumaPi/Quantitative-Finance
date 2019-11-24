// Product.cpp
//
// Base class for Products.
//
// 5 june 1998	MB	Started
// 2004-1-28 DD adapted for CDOs

//
// (C) Datasim Education BV 1998

#include "Product.hpp"

// Constructors and destructor
Product::Product()
{ // Default constructor
}

Product::Product(const Product& source)
{ // Copy constructor
}

Product:: ~Product()
{ // Destructor
}

// Operator overloading
Product& Product::operator = (const Product& source)
{ // Assignment operator

	return *this;
}
