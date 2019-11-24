// DistanceStrategy.hpp
//
// Abstract base class for strategies to calculate the distance between two points.
//
// 15 september 1998	RD	Started
//
// (C) Datasim Education BV 1998

#include "DistanceStrategy.hpp"

DistanceStrategy::DistanceStrategy()
{ // Default constructor
}

DistanceStrategy::DistanceStrategy(const DistanceStrategy& source)
{ // Copy constructor
}

DistanceStrategy::~DistanceStrategy()
{ // Destructor
}

// Operators
DistanceStrategy& DistanceStrategy::operator = (const DistanceStrategy& source)
{ // Assignment

	return *this;
}

