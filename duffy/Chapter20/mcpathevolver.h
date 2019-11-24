//
//
//      MCPathEvolver.h
//
//		Base class for numerical integrators for SDE.
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#ifndef MC_PATH_EVOLVER_H
#define MC_PATH_EVOLVER_H
#include "MCTemplateClass.h"
#include "MCUnderlying.h"
#include "MCPathStructure.h"
#include "MCStats.h"
#include <vector>

class MCPathEvolver
{
public:
	//constructor
    MCPathEvolver(const MCTemplateClass<PathStructure>& TheProduct_, const MCUnderlyingParams& r_);
	//destructor
    virtual ~MCPathEvolver(){}

	//methods
	//compute a MC path
    virtual void GetOnePath(MCPath& SpotValues, int Type)=0;
	//store values to output table
    void MCSimulation(MCStats& MCOutputTable, unsigned long NumberOfPaths);
	//compute pv of derivative
    double EvolvePath(const MCPath& SpotValues) const;

private:

    MCTemplateClass<PathStructure> TheProduct;
    MCUnderlyingParams r;							//riskless rate
    MCPath Defalte;									//Discount factor or deflater
	int Type;										//Type refers to Normal or LogNormal dynamics; 0=LogNormal, 1 = Normal
    mutable std::vector<CashFlow> TheseCashFlows;
};

#endif