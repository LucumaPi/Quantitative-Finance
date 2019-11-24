// RangeMechanisms.hpp
//
// Utility functions for Range class that we
// we use in various applications in Finance and 
// Numerical Analysis.
//
// (C) Datasim Education BV 2005
//

#ifndef DatasimRangeMechanisms_hpp
#define DatasimRangeMechanisms_hpp

#include <vector>
using namespace std;

#include "range.cpp"

namespace DatasimRangeMechanisms
{
	
	// 'Magnitude' of an interval
	template <class V>
		V magnitude(const Range<V>& range);

	// Partial ordering between ranges
	template <class V>
		bool operator < (const Range<V>& range1, const Range<V>& range2);

	// Arithmetic operations with intervals
	template <class V>
		bool operator + (const Range<V>& range1, const Range<V>& range2);
	template <class V>
		bool operator - (const Range<V>& range1, const Range<V>& range2);
	template <class V>
		bool operator * (const Range<V>& range1, const Range<V>& range2);
	template <class V>
		bool operator / (const Range<V>& range1, const Range<V>& range2);

	// Range is a metric space with a given metric. Concept of distance between
	// 2 ranges
	template <class V>
		bool operator distance(const Range<V>& range1, const Range<V>& range2);
}

#endif
