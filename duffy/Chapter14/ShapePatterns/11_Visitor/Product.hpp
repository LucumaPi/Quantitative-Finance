// Product.hpp
//
// Base class for Products.
//
// (C) Datasim Education BV 1998

#ifndef Product_hpp
#define Product_hpp

//class CDOVisitor;

class Product
{
public:
	// Constructors and destructor
	Product();							// Default constructor
	Product(const Product& source);			// Copy constructor
	virtual ~Product();					// Destructor
	
	// Special copy function to create a copy of a Product when you only have a Product pointer
	virtual Product* Clone() const=0;		// Create a copy of the Product

	// Operator overloading
	Product& operator = (const Product& source);	// Assignment operator

	// Visitor functionality
//	virtual void Accept(CDOVisitor& v) = 0;	// Accept a visitor
};

#endif // Product_hpp