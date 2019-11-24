// ApproxDistance.hpp
//
// Strategy to calculate the distance between two points approximately
//
// 15 september 1998	RD	Started
//
// (C) Datasim Education BV 1998

#include "ApproxDistance.hpp"
#include "Point.hpp"

ApproxDistance::ApproxDistance()//: Impl()
{ // Default constructor
}

ApproxDistance::ApproxDistance(const ApproxDistance& source)//: Impl(source)
{ // Copy constructor
}

ApproxDistance::~ApproxDistance()
{ // Destructor
}

double ApproxDistance::Distance(const Point& p1, const Point& p2) const
{ // Calculate distance between this point and second point 
  // To compute this, we use the taximan's formula: dx + dy

	// If coordinates are equal, return distance of 0.0 
	if (p1==p2) return 0.0;   

	// Difference in x direction
	double dif_x=p1.X() - p2.X();	

	// Difference in y direction 
	double dif_y=p1.Y() - p2.Y();  

	// Return square root
	return fabs(dif_x+dif_y); 
}

// Operators
ApproxDistance& ApproxDistance::operator = (const ApproxDistance& source)
{ // Assignment

	//Impl::operator = (source);

	return *this;
}

/*
ApproxDistance* ApproxDistance::Instance()
{
	return Singleton<ApproxDistance>::instance();
}
*/
