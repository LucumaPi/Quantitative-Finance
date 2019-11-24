// Point.hpp
//
// Generic point class. The first coordinate is of one
// type and the second coordinate is of the second type.
//
// (C) Datasim Education BV 2006

#ifndef Point_hpp
#define Point_hpp

#include <iostream.h>
//using namespace std;

template <class TFirst, class TSecond>
class Point
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
	//	ONLY IN MC++ 6.0, higher versions uncommented

//	template <class TFirst, class TSecond> 
	friend ostream& operator << (ostream& os, const Point<TFirst, TSecond>& p);
};


#endif
