// Polyline.hpp
//
// Aggregation
//
// (C) Datasim Education BV 2006
//

#include <list>

class Polyline
{
private:
		std::list<Point*> elements;
public:
		
		// Members here
	
		// Manipulating elements
		void add(Point* pt);
		void remove(Point* pt);

};