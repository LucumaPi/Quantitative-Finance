class ShapeComposite: public Shape
{ // N.B. Stripped down version 
private:
	// The shapelist using the STL list
	std::list<Shape*> sl;
	

public:
	// User can use the STL iterator
	typedef std::list<Shape*>::iterator iterator;
	typedef std::list<Shape*>::const_iterator const_iterator;


	// Iterator functions
    iterator Begin();								// Return iterator at begin of composite
	const_iterator Begin() const;					// Return const iterator at begin of composite
	iterator End();									// Return iterator after end of composite
    const_iterator End() const;						// Return const iterator after end of composite


	// Remove functions
	void RemoveAll();								// Remove all shapes from the list

};
