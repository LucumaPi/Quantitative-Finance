// Rectangle.cpp
//
// Simple Rectangle and Square classes. We 
// create them to show difference between inheritance
// and composition.
//
// Solutions:
//
//	1. Inheritance
//	2. Composition and delegation
//
// (C) Copyright Datasim BV 2005
//

#include "point.hpp"

// Inheritance Solution
class Rectangle : public Shape
{
protected:	// Derived classes can access this data directly

		Point bp;	// Base point, Point class given 	
		double h;	// height
		double w;	// width

public:
		Rectangle()
		{
			bp = Point();
			h = 1.0;
			w = 2.0;
		}

		Rectangle(const Point& basePoint, double height, double width)
		{
			bp = basePoint;
			h = height;
			w = width;
		}

		void setHeight(double newHeight)
		{
			h = newHeight;
		}

		void setWidth(double newWidth)
		{
			w = newWidth;
		}

		void print() const
		{

			cout << bp;
			cout << "Dimensions (H, W): " << h << ", " << w <<endl;
		}

};

class BadSquare : public Rectangle
{ // Version 1, a Square is a Rectangle
private:
		
		// No member data, inherited from Rectangle

public:
		BadSquare() : Rectangle (Point(), 1.0, 1.0)
		{

			// We must implement this, otherwise this default constructor
			// inherits a default rectangle
		}

		BadSquare (const Point& basePoint, double size)
		{
			bp = basePoint;
			h = w = size;		// Starts off well
		}

		
};


class GoodSquare : public Shape
{ // Version 2, adapts a Rectangle's interface
private:
		Rectangle r;
public:
		GoodSquare ()
		{
			double size = 1.0;
			r = Rectangle (Point(), size, size); // Unit square
			
		}

		GoodSquare (const Point& basePoint, double size)
		{
			r = Rectangle (basePoint, size, size);
			
		}

		void setSize(double newSize)
		{ // An adpator function, this ensures that constraints
		  // on the square are always satisfied

			r.setHeight(newSize);
			r.setWidth(newSize);
		}


		void print() const 
		{
			// Delegate to the embedded rectangle's output mechanism
			r.print();
		}
};