// OriginPoint.cpp
//
// Singleton origin point. Operations involving the origin point use this
// origin point. Herefore we can use origin point that are not (0,0)
//
// 15 september 1998	RD	Started
//
// (C) Datasim Education BV 1998

#include "OriginPoint.hpp"
#include "Point.hpp"

OriginPoint::OriginPoint(): Singleton<Point>()
{ // Default constructor
}

OriginPoint::OriginPoint(const OriginPoint& source): Singleton<Point>(source)
{ // Copy constructor
}

OriginPoint::~OriginPoint()
{ // Destructor
}

OriginPoint& OriginPoint::operator = (const OriginPoint& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;

	Singleton<Point>::operator = (source);

	return *this;
}
