// Polyline.hpp
//
// Aggregation
//
// (C) Datasim Education BV 2006
//

class Polyline
{
private:
		list<Point*> elements;
public:
		
		// Members here
	
		// Manipulating elements
		void add(Point* pt);
		void remove(Point* pt);

};

