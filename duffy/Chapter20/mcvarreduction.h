//
//
//		MCVarReduction.h
//
//		Code for variance reduction techniques
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#ifndef MC_VAR_REDUCTION_H
#define MC_VAR_REDUCTION_H

#include "MCRandomNumbers.h"
#include "MCTemplateClass.h"

class AntiThetic : public Random
{

public:
    AntiThetic(const MCTemplateClass<Random>& innerGenerator );

    virtual Random* clone() const;
    
    virtual void GenerateUniforms(MCPath& variates);

    virtual void Skip(unsigned long numberOfPaths);

    virtual void SetSeed(unsigned long Seed);

    virtual void ResetDimensionality(unsigned long NewDimensionality);

    virtual void Reset();

private:
    MCTemplateClass<Random> InnerGenerator;

    bool OddEven;

    MCPath NextVariates;
};

#endif
