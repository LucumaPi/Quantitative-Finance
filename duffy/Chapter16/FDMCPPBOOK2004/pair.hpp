// pair.hpp
//

// (C) Datasim Component Technology 2000 BV
//

#ifndef pair_HPP
#define pair_HPP

// 1/5/2002 edited out by D. Duffy and R. Mirani
// because previously defined in stl_pair.h, line 50:
//		template <class _U1, class _U2>
//			pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}
//
/*
template <class F, class S> class pair
{

public:
	
		F first;
		S second;

public:
	pair() { first = F(); second = S();}
	pair(const F& First, const S& Second) { first = First; second = Second;}
};
*/
#endif