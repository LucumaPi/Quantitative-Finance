//
//
//
//		MCPath.h	
//
//		This class models one run of a Monte Carlo simulation. It is in 
//		fact a matrix structure (nested vector class) that represnts the 
//		evolution (with possible correlation) of an asset in time.
//
//		Author: J. Kienitz	       
//		Date:   25.07.2005
//
//      Represents a collection of paths

#ifndef MCPath_H
#define MCPath_H

#ifdef USE_VAL_ARRAY

//#include <valarray>
#include <vector>

//typedef  std::valarray<std::valarray<double>> MCPath;
typedef  std::vector<std::vector<double>> MCPath;

#else   // ifdef USE_VAL_ARRAY


class MCPath
{

public:

	//constructor	
	explicit MCPath(unsigned long NoOfFactors_ = 0, unsigned long NoOfTimeSteps_ = 0);
	MCPath(const MCPath& original);
	
	//desctructor
	~MCPath();

	//operator overloading
	MCPath& operator=(const MCPath& original);
	MCPath& operator=(const double& val);

	MCPath& operator+=(const MCPath& operand);
	MCPath& operator-=(const MCPath& operand);
	MCPath& operator/=(const MCPath& operand);
	MCPath& operator*=(const MCPath& operand);

	MCPath& operator+=(const double& operand);
	MCPath& operator-=(const double& operand);
	MCPath& operator/=(const double& operand);
	MCPath& operator*=(const double& operand);

	MCPath apply(double f(double)) const;

	inline double operator()(unsigned long i, unsigned long j) const;
	inline double& operator()(unsigned long i, unsigned long j);

	inline double operator[](unsigned long j) const;
	inline double& operator[](unsigned long j);

	inline unsigned long timesteps() const;
	inline unsigned long factors() const;

	void resize(unsigned long newNoOfTimeSteps, unsigned long newNoOfFactors);
	void insert(unsigned long factor, unsigned long time, double value);

	//elements
	double sum() const;
	double min() const;
	double max() const;
	double last() const;


private:


	double* ValuesPtr;
	double* EndPtr;


	unsigned long NoOfTimeSteps;
	unsigned long Capacity;
	unsigned long NoOfFactors;
	

};

inline double MCPath::operator()(unsigned long i, unsigned long j) const
{
#ifdef RANGE_CHECKING
	if (j >= NoOfTimeSteps || i >= NoOfFactors)
	{
		throw("Index out of bounds");
	}
#endif 

	return ValuesPtr[i * NoOfTimeSteps + j];
}


inline double& MCPath::operator()(unsigned long i, unsigned long j)
{
#ifdef  RANGE_CHECKING
	if (j >= NoOfTimeSteps || i >= NoOfFactors)
	{
		throw("Index out of bounds");
	}
#endif 

	return ValuesPtr[i * NoOfTimeSteps + j];
}


inline double MCPath::operator[](unsigned long j) const
{
#ifdef RANGE_CHECKING
	if (j >= NoOfTimeSteps * NoOfFactors)
	{
		throw("Index out of bounds");
	}
#endif 

	return ValuesPtr[j];
}


inline double& MCPath::operator[](unsigned long j)
{
#ifdef  RANGE_CHECKING
	if (j >= NoOfTimeSteps * NoOfFactors)
	{
		throw("Index out of bounds");
	}
#endif
	
	return ValuesPtr[j];
}


inline unsigned long MCPath::timesteps() const
{
	return NoOfTimeSteps;
}

inline unsigned long MCPath::factors() const
{
	return NoOfFactors;
}


#endif // ifdef USE_VAL_ARRAY

#endif // ifndef MCPath_H
