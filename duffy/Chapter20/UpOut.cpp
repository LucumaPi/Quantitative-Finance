//
//
//
//                    UpOut.cpp
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include "UpOut.h"

UpOut::UpOut(const MCPath& DiscreteMonitor_, 
             double DeliveryTime_,
			 const MCTemplateClass<PayOff>& ThePayOff_)
             :
             PathStructure(DiscreteMonitor_),
             DeliveryTime(DeliveryTime_),
             ThePayOff(ThePayOff_),
             NumberOfTimes(DiscreteMonitor_.timesteps())
{
}

unsigned long UpOut::MaxNumberOfCashFlows() const
{
     return 1UL;
}

MCPath UpOut::PossibleCashFlowTimes() const
{
    MCPath tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long UpOut::CashFlows(const MCPath& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const
{
    double minvalue = SpotValues.min();
    double last = SpotValues.last();
	if(minvalue <= 0.0)
	{
    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = minvalue;//(*ThePayOff)(last);

    return 1UL;
	}
	else
	{
	GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = (*ThePayOff)(last);

    return 1UL;
	}
}

PathStructure* UpOut::clone() const
{
    return new UpOut(*this);
}