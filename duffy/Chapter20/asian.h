//
//
//      Asian.h
//
//		Path structure of an Asian option
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#ifndef ASIAN_H
#define ASIAN_H

#include "MCPathStructure.h"
#include "MCTemplateClass.h"
#include "MCPayOff.h"



class Asian : public PathStructure
{
public:
	//constructor
    Asian(const MCPath& DiscreteMonitor_, double DeliveryTime_, const MCTemplateClass<PayOff>& ThePayOff_);
	//destructor
    virtual ~Asian(){}
	//copy constructor
    virtual PathStructure* clone() const;
	//methods
    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MCPath PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MCPath& SpotValues, std::vector<CashFlow>& GeneratedFlows) const;

private:

    double DeliveryTime;
	MCTemplateClass<PayOff> ThePayOff;
    unsigned long NumberOfTimes;
};


#endif

