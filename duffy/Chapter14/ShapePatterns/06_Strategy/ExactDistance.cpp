// ExactDistance.hpp
//
// Strategy to calculate the distance between two points exact.
//
// 15 september 1998	RD	Started
//
// (C) Datasim Education BV 1998

#include "ExactDistance.hpp"
#include "Point.hpp"

ExactDistance::ExactDistance()//: DistanceStrategy()
{ // Default constructor
}

ExactDistance::ExactDistance(const ExactDistance& source)// DistanceStrategy(source)
{ // Copy constructor
}

ExactDistance::~ExactDistance()
{ // Destructor
}

double ExactDistance::Distance(const Point& p1, const Point& p2) const
{ // Calculate distance between this point and second point 
  // To compute this, the law of Pythagoras is used: sqrt(dx^2 + dy^2)

	// If coordinates are equal, return distance of 0.0 
	if (p1==p2) return 0.0;   

	// Difference in x direction
	double dif_x=p1.X() - p2.X();	

	// Difference in y direction 
	double dif_y=p1.Y() - p2.Y();  

	// Calculate squares of coordinates
	dif_x*=dif_x;		
	dif_y*=dif_y;

	// Return square root
	return sqrt(dif_x + dif_y); 
}

// Operators
ExactDistance& ExactDistance::operator = (const ExactDistance& source)
{ // Assignment

	//DistanceStrategy::operator = (source);

	return *this;
}


/*
ExactDistance* ExactDistance::Instance()
{
	return Singleton<ExactDistance>::instance();
}
*/