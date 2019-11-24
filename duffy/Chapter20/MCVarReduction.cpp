//
//
//                  MCVarReduction.cpp
//
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include "MCVarReduction.h"

//Antithetic Variables up to now

AntiThetic::AntiThetic(const MCTemplateClass<Random>& innerGenerator )
            : Random(*innerGenerator), 
              InnerGenerator(innerGenerator)
{
    InnerGenerator->Reset();
    OddEven =true;
    NextVariates.resize(GetDimensionality(), NextVariates.factors());
}

Random* AntiThetic::clone() const
{
    return new AntiThetic(*this);
}
    
void AntiThetic::GenerateUniforms(MCPath& variates)
{
    if (OddEven)
    {
        //InnerGenerator->GenerateUniforms(variates);
		InnerGenerator->GenerateUniforms(variates);

        for (unsigned long i =0; i < GetDimensionality(); i++)
            NextVariates[i] = 1.0-variates[i];
        
        OddEven = false;
    }
    else
    {
        variates = NextVariates;

        OddEven = true;
    }
}

void AntiThetic::SetSeed(unsigned long Seed)
{
    InnerGenerator->SetSeed(Seed);
    OddEven = true;
}

void AntiThetic::Skip(unsigned long numberOfPaths)
{
    if (numberOfPaths ==0)
        return;

    if (OddEven)
    {
        OddEven = false;
        numberOfPaths--;
    }

    InnerGenerator->Skip(numberOfPaths  / 2);

    if (numberOfPaths % 2)
    {
        MCPath tmp(GetDimensionality());

        GenerateUniforms(tmp);
		
    }



}

void AntiThetic::ResetDimensionality(unsigned long NewDimensionality)
{
    Random::ResetDimensionality(NewDimensionality);

    NextVariates.resize(NewDimensionality, NextVariates.factors());

    InnerGenerator->ResetDimensionality(NewDimensionality);
}

void AntiThetic::Reset()
{
    InnerGenerator->Reset();
    OddEven =true;
}