// Point.hpp
//
// Generic point class. The first coordinate is of one
// type and the second coordinate is of the second type.
//
// (C) Datasim Education BV 2006

#ifndef PointTemplate_hh
#define PointTemplate_hh

#include <iostream>

template <class TFirst, class TSecond> class Point
{
private:
	// The two coordinates
	TFirst m_first;
	TSecond m_second;

public:
	// Constructors & destructor
	Point();											// Default constructor
	Point(TFirst first, TSecond second);				// Constructor with coordinates
	Point(const Point<TFirst, TSecond>& source);		// Copy constructor
	virtual ~Point();									// Destructor

	// Selectors
	TFirst First() const;								// Get first coordinates
	TSecond Second() const;								// Get second coordinate

	// Modifiers
	void First(const TFirst& val);						// Set first coordinate
	void Second(const TSecond& val);					// Set second coordinates

	// Functions
	double Distance(const Point<TFirst, TSecond>& p) const;	// Calculate distance

	// Assignment operator
	Point<TFirst, TSecond>& operator = (const Point<TFirst, TSecond>& source);

	// Print
	//template <class TFirst, class TSecond> 
	friend std::ostream& operator << (std::ostream& os, const Point<TFirst, TSecond>& p)
	{
		os << "(" << p.m_first << "," << p.m_second << ")\n";
		return os;
	}
};
#include "../../src/PointTemplate.cc"
#endif