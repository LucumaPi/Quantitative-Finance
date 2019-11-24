//
//
//      MCPathGenerator_Euler.h
//
//		Implements explicit Euler Scheme and Milstein scheme for 1d SDE. 
//		It is derived from MCPathEvolver
//
//		Author: J. Kienitz	       
//		Date:   11.08.2005

#ifndef MC_PATH_GENERATOR_EULER_H
#define MC_PATH_GENERATOR_EULER_H

#include "MCPathEvolver.h"
#include "MCRandomNumbers.h"

class GeneratePath_Euler : public MCPathEvolver
{
public:

	GeneratePath_Euler(const MCTemplateClass<PathStructure>& TheProduct_,
				       const MCUnderlyingParams& R_,
				       const MCUnderlyingParams& D_,
				       const MCUnderlyingParams& Vol_,
				       const MCTemplateClass<Random>& TheGenerator_,
					   std::vector<double> Spot_,
				       int Type_);

      virtual void GetOnePath(MCPath& SpotValues, int Type_);
      virtual ~GeneratePath_Euler(){};

private:

    MCTemplateClass<Random> TheGenerator;
    MCPath Drifts;
	MCPath Drifts2;
    MCPath Volatilities;
    mutable std::vector<double> Spot;
	int Type;
    unsigned long NumberOfTimes;
	unsigned long NumberOfFactors;
    MCPath Variates;
};

#endif

