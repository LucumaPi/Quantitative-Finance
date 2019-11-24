// GenericVisitor.hpp
//
// Generic Visitor
//
// (C) Datasim Education BV 2006
#include "GenericComposite.cpp" // New!! template class

template <class Context, class Name>
	class GenericVisitor
{
public:
	void visit(GenericComposite<Context>& context)
	{

	GenericComposite<Context>::iterator it;

	// Send all shapes in the composite to the visitor
	for (it=sc.Begin(); it!=sc.End(); it++)
	{
		(*it)->accept(*this);
	}
	
	}
};
