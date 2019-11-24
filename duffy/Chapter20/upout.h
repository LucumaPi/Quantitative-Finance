//
//
//      UpOut.h
//
//		Path structure of an up and out option
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#ifndef UP_OUT_H
#define UP_OUT_H

#include "MCPathStructure.h"
#include "MCTemplateClass.h"
#include "MCPayOff.h"

class UpOut : public PathStructure
{
public:

    UpOut(const MCPath& DiscreteMonitor_, 
          double DeliveryTime_,
		  const MCTemplateClass<PayOff>& ThePayOff_);

    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MCPath PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MCPath& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~UpOut(){}
    virtual PathStructure* clone() const;

private:

    double DeliveryTime;
	MCTemplateClass<PayOff> ThePayOff;
    unsigned long NumberOfTimes;
};


#endif
