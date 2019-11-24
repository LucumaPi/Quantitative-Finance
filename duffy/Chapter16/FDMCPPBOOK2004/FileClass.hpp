//
// Just a file for output for my own convenience. It requires
// a "Vector<double,long>" for the X-axis and a matrix-like construction
// "Vector<Vector<double,long>,long>" for several results at the
// Y-axis. Mostly used for plotting stock-price (x-axis) versus
// option price, delta and gamma (y-axis). Directly after writing the
// output file is closed. Another file must be opened with SetFileName
// before writing other results.
//
// by Robbert Mirani

#ifndef File_HPP
#define File_HPP

#include "Vector.cpp"

class FileClass{

public:

	// constructor
	FileClass();
	
	// constructor
	FileClass(const long & Start);
	
	// destructor
	~FileClass();
	
	// set the contents of the vectors
	void SetAxis(const Vector<double,long> & X,
	             const Vector<Vector<double,long>,long > & Y);
	
	// write values in vectors to file
	void WriteToFile();
	
	// set the desired filename
	void SetFileName(char * name);

	
private:
	FILE * outputfile;
	long leap;
	Vector<double,long> X_Axis;
	Vector<Vector<double,long>,long > Y_Axis;
	
};

#endif