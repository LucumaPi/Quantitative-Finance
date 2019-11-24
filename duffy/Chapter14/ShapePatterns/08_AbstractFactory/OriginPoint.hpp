// OriginPoint.hpp
//
// Singleton origin point. Operations involving the origin point use this
// origin point. Herefore we can use origin point that are not (0,0)
//
// (C) Datasim Education BV 1998

#ifndef OriginPoint_hpp
#define OriginPoint_hpp

#include "Singleton.cpp"

class Point;
class OriginPoint: public Singleton<Point>
{
private:
	OriginPoint();											// Default constructor
	OriginPoint(const OriginPoint& source);					// Copy constructor
	OriginPoint& operator = (const OriginPoint& source);	// Assignment

public:
	virtual ~OriginPoint();
};

#endif	// OriginPoint_hpp
