//
//
//                        MCRandomNumberGenerator.h
//
//
//		Author: J. Kienitz	       
//		Date:   11.08.2005

#ifndef MC_RANDOM_NUMBER_GENERATOR_H
#define MC_RANDOM_NUMBER_GENERATOR_H

#include <MCPath.h>
#include <MCRandomNumberGenerator.cpp>

template<class T> class MCRandomNumber
{
public:
	//Constructors
	MCRandomNumber();
    MCRandomNumber(unsigned long Dimensionality, unsigned long Seed=1);

	//Desctuctor
	virtual ~MCRandomNumber();

	//Accessing funcitons
    inline unsigned long GetDimensionality() const;

	virtual void SetSeed(unsigned long Seed);
    virtual void Reset();

	//Methods
    virtual void GenerateUniforms(MCPath& variates);
    virtual void Skip(unsigned long numberOfPaths);
    virtual void GenerateNormals(MCPath& variates);
	virtual void GenerateLogNormals(MCPath& variates);

	//Modifying functions
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
    unsigned long Dimensionality;
	unsigned long InitialSeed;
	T MCNumberGen;
	double Reciprocal;
	
};

unsigned long MCRandomNumber::GetDimensionality() const
{
    return Dimensionality;
}

#endif