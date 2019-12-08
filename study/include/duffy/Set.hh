// Set.hpp
//
// C++ template class that implements the concept of
// a mathematical set.
// This class is composed of an STL set and uses Information
// Hiding.
//
// (C) Datasim Education BV 2004-2006

#ifndef Set_HH
#define Set_HH

#include <set>
#include <list>

template <class V> class SetThing {};

template <class V> class Set : public SetThing<V>
{
private:
		std::set<V> s;

public:
		// Iterator functions; Navigating in a set
		typedef typename std::set<V>::iterator iterator;
		typedef typename std::set<V>::const_iterator const_iterator;

public:
		// Constructors
		Set();						// Empty set
		Set(const std::set<V>& stlSet);	// Create a Set from STL set
		Set(const Set<V>& s2);		// Copy constructor
		// Construct a set from V that has STL-compatible iterators
		Set(const std::list<V>& con);	// From anm STL list
		Set<V> operator = (const Set<V>& s2);
		virtual ~Set();

		// Standard set operations from High School
		friend Set<V> Intersection(const Set<V>& s1, const Set<V>& s2)
		{
			std::set<V> myintersect;
			typename std::set<V>::iterator i = myintersect.begin();
			std::insert_iterator<std::set<V> > insertiter(myintersect, i);
			set_intersection(s1.s.begin(), s1.s.end(), s2.s.begin(), s2.s.end(), insertiter);

			return Set<V>(myintersect);
		}
		Set<V> operator ^ (const Set<V>& s2)	// Intersection
		{
			return Intersection(*this, s2);
		}

		friend Set<V> Union(const Set<V>& s1, const Set<V>& s2)
		{
			std::set<V> myunion;
			typename std::set<V>::iterator i = myunion.begin();
			std::insert_iterator<std::set<V> > insertiter(myunion, i);
			set_union(s1.s.begin(), s1.s.end(), s2.s.begin(), s2.s.end(), insertiter);

			return Set<V>(myunion);
		}
		Set<V> operator + (const Set<V>& s2)	// Union
		{
			return Union(*this, s2);
		}

		friend Set<V> Difference(const Set<V>& s1, const Set<V>& s2)
		{
			std::set<V> mydiff;
			typename std::set<V>::iterator i = mydiff.begin();
			std::insert_iterator<std::set<V> > insertiter(mydiff, i);
			set_difference(s1.s.begin(), s1.s.end(), s2.s.begin(), s2.s.end(), insertiter);

			return Set<V>(mydiff);
		}
		Set<V> operator - (const Set<V>& s2)	// Difference
		{
			return Difference(*this, s2);
		}

		friend Set<V> SymmetricDifference(const Set<V>& s1, const Set<V>& s2)
		{
			std::set<V> mysdiff;
			typename std::set<V>::iterator i = mysdiff.begin();
			std::insert_iterator<std::set<V> > insertiter(mysdiff, i);
			set_symmetric_difference(s1.s.begin(), s1.s.end(), s2.s.begin(), s2.s.end(), insertiter);

			return Set<V>(mysdiff);
		}
		Set<V> operator % (const Set<V>& s2)	// Symmetric Difference
		{
			return SymmetricDifference(*this, s2);
		}

		template <class V2> 
			Set<std::pair<V, V2> > operator * (const Set<V2>& s2)
			{ // Product Set(set of pairs)
					return CartesianProduct(s2);
			}

		template <class V2> 
			Set<std::pair<V, V2> > CartesianProduct(const Set<V2>& s2)
		{

				Set<std::pair<V, V2> > result;

				// Iterate from begin to end of first set
				// At each level create a pair with second element from s2

				typename std::set<V>::const_iterator iOuter;
				typename std::set<V2>::const_iterator iInner;

				for (iOuter = (*this).s.begin(); iOuter != (*this).s.end(); iOuter++)
				{
					for (iInner = s2.Begin(); iInner != s2.End(); iInner++)
					{
						result.Insert(std::pair<V,V2>(*iOuter, *iInner));
					}

				}

				return result;
			}

		iterator Begin();				// Return iterator at begin of set
		const_iterator Begin() const;	// Return const iterator at begin of set
		iterator End();					// Return iterator after end of set
		const_iterator End() const;		// Return const iterator after end of set

		// Operations on a single set
		long Size() const;				// Number of elements	
		void Insert(const V& v);		// Insert an element
		void Insert(const Set<V>& v);	// Insert another set
		void Remove(const V& v);		// Remove an element
		void Replace(const V& Old, const V& New);	// Replace old by new
		void Clear();					// Remove all elements
		bool Contains(const V& v) const;			// Is v in set?
		bool Empty() const;				// Contains no elements

		// Using 'clever' operators
		void operator + (const V& v);	// Insert an element
		void operator - (const V& v);	// Remove an element

		// Relations between sets (s1 == *this)
		bool Subset(const Set<V>& s2) const;	// s1 a subset of s2?
		bool Superset(const Set<V>& s2) const;	// s1 a superset of s2?
		bool Intersects(const Set<V>& s2) const;	// s1 and 22 have common elements?
	

};
#include "../../src/Set.cc"
#endif