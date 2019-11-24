// ApproxDistance.hpp
//
// Strategy to calculate the distance between two points approximately
//
// (C) Datasim Education BV 1998

#ifndef ApproxDistance_hpp
#define ApproxDistance_hpp

#include "DistanceStrategy.hpp"
#include "Singleton.cpp"

class ApproxDistance: public DistanceStrategy
{
private:
	ApproxDistance();											// Default constructor
	ApproxDistance(const ApproxDistance& source);					// Copy constructor

	// Operators
	ApproxDistance& operator = (const ApproxDistance& source);	// Assignment

	friend class Singleton<ApproxDistance>;

public:
	// Constructors and destructor
	virtual ~ApproxDistance();									// Destructor

	// Calculate the distance between two points
	virtual double Distance(const Point& p1, const Point& p2) const;

	// Singleton function
	static ApproxDistance* Instance();
};

#endif	// ApproxDistance_hpp
