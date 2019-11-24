//
//
//
//                    Asian.cpp
//
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include "Asian.h"

Asian::Asian(const MCPath& DiscreteMonitor_, double DeliveryTime_, const MCTemplateClass<PayOff>& ThePayOff_)
			 :
             PathStructure(DiscreteMonitor_), DeliveryTime(DeliveryTime_), ThePayOff(ThePayOff_), NumberOfTimes(DiscreteMonitor_.timesteps())
{
}


unsigned long Asian::MaxNumberOfCashFlows() const
{
     return 1UL;
}

MCPath Asian::PossibleCashFlowTimes() const
{
    MCPath tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long Asian::CashFlows(const MCPath& SpotValues, std::vector<CashFlow>& GeneratedFlows) const
{
    double sum = SpotValues.sum();
    double mean = sum/NumberOfTimes;

    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = (*ThePayOff)(mean);

    return 1UL;
}

PathStructure* Asian::clone() const
{
    return new Asian(*this);
}

