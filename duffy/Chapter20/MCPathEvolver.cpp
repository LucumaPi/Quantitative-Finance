//
//
//                       MCPathEvolver.cpp
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include <MCPathEvolver.h>
#include <cmath>

MCPathEvolver::MCPathEvolver(const MCTemplateClass<PathStructure>& TheProduct_, const MCUnderlyingParams& r_)
                 :
                 TheProduct(TheProduct_), r(r_), Defalte(TheProduct_->PossibleCashFlowTimes())
{
    for (unsigned long i=0; i < Defalte.timesteps(); i++)
        Defalte[i] = exp(-r.DriftPart(0.0, Defalte[i]));

    TheseCashFlows.resize(TheProduct->MaxNumberOfCashFlows());
}

void MCPathEvolver::MCSimulation(MCStats& MCOutputTable, unsigned long NumberOfPaths)
{
    MCPath SpotValues(TheProduct->DiscreteMonitorGetTimes().timesteps());

    TheseCashFlows.resize(TheProduct->MaxNumberOfCashFlows());
    double thisValue;
    
    for (unsigned long i =0; i < NumberOfPaths; ++i)
    {
        GetOnePath(SpotValues, Type);
        thisValue = EvolvePath(SpotValues);
        MCOutputTable.StoreValue(thisValue);
    }

    return;
}

double MCPathEvolver::EvolvePath(const MCPath& SpotValues) const
{
    unsigned long NumberFlows = TheProduct->CashFlows(SpotValues, TheseCashFlows);
    double Value=0.0;
    
    for (unsigned i =0; i < NumberFlows; ++i)
        Value += TheseCashFlows[i].Amount * Defalte[TheseCashFlows[i].TimeIndex];

    return Value;
}



