// ExactDistance.hpp
//
// Strategy to calculate the distance between two points exact.
//
// (C) Datasim Education BV 1998

#ifndef ExactDistance_hpp
#define ExactDistance_hpp

#include "DistanceStrategy.hpp"
#include "Singleton.cpp"

class ExactDistance: public Impl<ExactDistance,DistanceStrategy>
{
private:
	// Constructors and destructor
	ExactDistance();											// Default constructor
	ExactDistance(const ExactDistance& source);					// Copy constructor
	// Operators
	ExactDistance& operator = (const ExactDistance& source);	// Assignment

	friend class Singleton<ExactDistance>;

public:
	virtual ~ExactDistance();									// Destructor

	// Calculate the distance between two points
	virtual double Distance(const Point& p1, const Point& p2) const;

};

#endif	// ExactDistance_hpp
