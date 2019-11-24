#ifndef QUASI_RANDOM_NUMBER_TEMPLATE_H
#define QUASI_RANDOM_NUMBER_TEMPLATE_H

#include <vector>


template< class RNG> class QuasiRandomTemplate
{
public:

	QuasiRandomTemplate()
	{
	};

	QuasiRandomTemplate(unsigned long Dim=1, unsigned long Seed = 1, const RNG& QMC)
	{	
		QMCNumberGen = &QMC;
		InitialSeed = Seed;
		Dimensionality = Dim;
	};

    //QuasiRandomSequence(unsigned long Dimensionality, unsigned long Seed=1);

	inline unsigned long GetDimensionality() const;

    virtual QuasiRandomTemplate* clone() const;    
    virtual void GenerateQuasiRandomSequence(MCPath& variates);    
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
	virtual void GenerateNormals(MCPath& variates);
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:

    RNG* QMCNumberGen;
    unsigned long InitialSeed;
	unsigned long Dimensionality;

};

unsigned long QuasiRandomTemplate<RNG>::GetDimensionality() const
{
	return Dimensionality;
}


QuasiRandomTemplate* QuasiRandomTemplate<RNG>::clone() const
{
    return new QuasiRandomTemplate(*this);   
}

void QuasiRandomTemplate<RNG>::GenerateQuasiRandomSequence(MCPath& variates)
{
	RNG.SetBase(GetDimensionality());
	for (unsigned long j=0; j < GetDimensionality(); j++)
        variates[j] = RNG.GetQuasiRandomNumber(j+1);	
}
    
void QuasiRandomTemplate<RNG>::Skip(unsigned long numberOfPaths)
{
    MCPath tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GenerateQuasiRandomSequence(tmp);
}

void QuasiRandomTemplate<RNG>::SetSeed(unsigned long Seed)
{
    InitialSeed = Seed;
    RNG.SetSeed(Seed);
}

void QuasiRandomTemplate<RNG>::Reset()
{
    RNG.SetSeed(InitialSeed);
}


void QuasiRandomTemplate<RNG>::ResetDimensionality(unsigned long NewDimensionality)
{
    QuasiRandomTemplate<RNG>::ResetDimensionality(NewDimensionality);
    RNG.SetSeed(InitialSeed);
}


#endif
