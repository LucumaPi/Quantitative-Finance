// StringConversions.hpp
//
// Handy string functions
//
// (C) Datasim Education BV 2006
//

#ifndef StringConversions_HH
#define StringConversions_HH

#include "Vector.hh"
#include <string>
#include <list>

// Simple and useful string converters
std::string getString(long j);

std::string getString(int j);

std::string getString(std::size_t j);

std::string getString(double d);

// Convert an array to a list of strings
std::list<std::string> convertToString(const Vector<double, long>& arr);
#include "../../src/StringConversions.cc"
#endif