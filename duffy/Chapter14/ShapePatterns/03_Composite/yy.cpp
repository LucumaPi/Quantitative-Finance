template <class N, class V> class SimplePropertySet
{ // N.B. Stripped down version
private:

	N nam;		// The name of the set

	// The SimplePropertySet list using the STL list
	list<Property<N,V> > sl;


public:
	// User can use the STL iterator
	typedef list<Property<N,V> >::iterator iterator;
	typedef list<Property<N,V> >::const_iterator const_iterator;


	// Iterator functions
    iterator Begin();			
	const_iterator Begin() const;
	iterator End();				
    const_iterator End() const;	


};