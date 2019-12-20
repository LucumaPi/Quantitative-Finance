// DatasimExceptions.hpp
//
// Ubiquitous class for basic exception handling
//
// (C) Datasim Education BV 2005 - 2006
//
#ifndef DatasimExceptions_HH
#define DatasimExceptions_HH

#include <iostream>
#include <vector>
#include <string>

class DatasimException
{ // Base class for my current exceptions
private:
	std::string mess;			// The error message
	std::string meth;			// The method that threw the exception
	std::string why;				// More info on message

	// Redundant data
	std::vector<std::string> result;

public:
	DatasimException();

	DatasimException (const std::string& message, const std::string& method,
						const std::string& extraInfo);
	

	std::string Message() const;		// The message itself
	std::string rationale() const;	// Extra information
	std::string Method() const;		// In which method?

	// Al information in one packet
	std::vector<std::string> MessageDump() const;	// Length 3

	// Print the full packet
	virtual void print() const;
};
#endif