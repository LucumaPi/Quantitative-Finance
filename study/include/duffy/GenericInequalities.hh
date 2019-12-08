// GenericInequalities.hpp
//
// Header file containing declarations of functions
//
// This is the template/generic version.
//
// (C) Datasim Education BV 2006
//

// Preprocessor directives; ensures that we do not 
// include a file twice (gives compiler error)
#ifndef GenericInequalities_HH
#define GenericInequalities_HH

/////////// Useful functions //////////////////

// Max and Min of two numbers
template <class Numeric>
Numeric Max(const Numeric& x, const Numeric& y);
template <class Numeric>
Numeric Min(const Numeric& x, const Numeric& y);

// Max and Min of three numbers
template <class Numeric>
Numeric Max(const Numeric& x, const Numeric& y, const Numeric& z);
template <class Numeric>
Numeric Min(const Numeric& x, const Numeric& y, const Numeric& z);

////////////////////////////////////////////////
#include "../../src/GenericInequalities.cc"
#endif