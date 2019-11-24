// DistanceStrategy.hpp
//
// Abstract base class for strategies to calculate the distance between two points
//
// (C) Datasim Education BV 1998

#ifndef DistanceStrategy_hpp
#define DistanceStrategy_hpp

// Forward reference since Point includes DistanceStrategy.hpp
class Point;

class DistanceStrategy
{
private:

public:
	// Constructors and destructor
	DistanceStrategy();												// Default constructor
	DistanceStrategy(const DistanceStrategy& source);				// Copy constructor
	virtual ~DistanceStrategy();									// Destructor

	// Calculate the distance between two points
	virtual double Distance(const Point& p1, const Point& p2) const=0;

	// Operators
	DistanceStrategy& operator = (const DistanceStrategy& source);	// Assignment
};

template <class SingleType, class Type>
class Impl : public Type
{
public:
	Impl() {};
	~Impl() {};
	static SingleType* Instance() {return Singleton<SingleType>::instance();};
};

#endif	// DistanceStrategy_hpp
