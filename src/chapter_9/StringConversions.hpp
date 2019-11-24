// StringConversions.hpp
//
// Handy string functions
//
// (C) Datasim Education BV 2006
//

#ifndef StringConversions_HPP
#define StringConversions_HPP

#include "Vector.hpp"
#include <string>
#include <list>

// Simple and useful string converters
std::string getString(long j);

std::string getString(int j);

std::string getString(size_t j);

std::string getString(double d);

// Convert an array to a list of strings
std::list<std::string> convertToString(const Vector<double, long>& arr);

#endif