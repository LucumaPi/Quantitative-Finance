//
//                              MCTemplateClass.h
//
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005
//

#ifndef MC_TEMPLATE_CLASS_H
#define MC_TEMPLATE_CLASS_H

template< class T> class MCTemplateClass
{
public:
//constructor
    MCTemplateClass()
    { 
		DataPtr =0;
	}

    MCTemplateClass(const T& source)
    {
        DataPtr = source.clone();
    }

//destructor
    virtual ~MCTemplateClass()
    {
        if (DataPtr !=0)
            delete DataPtr;
    }

//copy constructor
    MCTemplateClass(const MCTemplateClass<T>& original)
    {
        if (original.DataPtr !=0)
            DataPtr = original.DataPtr->clone();
        else
            DataPtr=0;
    }

//operators
    MCTemplateClass& operator=(const MCTemplateClass<T>& original)
    {
        if (this != &original)
        {
            if (DataPtr!=0)
                delete DataPtr;

            DataPtr = (original.DataPtr !=0) ? original.DataPtr->clone() : 0;
        }

        return *this;
    }

    T& operator*()
    {
        return *DataPtr; 
    }

    const T& operator*() const
    {
        return *DataPtr; 
    }

    const T* const operator->() const
    {
        return DataPtr;
    }

    T* operator->()
    {
        return DataPtr;
    }


// For valuation of options payoffs

	T& operator()(double Spot) const
	{
    return DataPtr->operator ()(Spot);
	}


private:
    T* DataPtr;

};
#endif



