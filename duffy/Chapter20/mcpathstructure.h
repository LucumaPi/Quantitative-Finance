//
//
//      MCPathStructure.h
//
//		Base class for different kinds of underlying cash flow models,
//		e.g. Asian, Up/Out etc.
//
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#ifndef MC_PATH_STRUCTURE_H
#define MC_PATH_STRUCTURE_H

#include "MCPath.h"
#include <vector>

//For the CashFlow class we implemented the Assets Value, The weight, The time
class CashFlow
{
public:

    double Amount;
	double Weight;
    unsigned long TimeIndex;
    
	CashFlow(unsigned long TimeIndex_=0UL, double Amount_=0.0, double Weight_=1.0) 
                : TimeIndex(TimeIndex_), Amount(Amount_), Weight(Weight_){}; 

};

class PathStructure
{
public:
	//construction
    PathStructure(const MCPath& DiscreteMonitor);
	//virtual destruction
    virtual ~PathStructure(){}
	//copy constructor
    virtual PathStructure* clone() const=0;    

	//(pure virual) methods
    virtual unsigned long MaxNumberOfCashFlows() const=0;
	/* Computes the max number of CashFlows for memory allocation */
    virtual MCPath PossibleCashFlowTimes() const=0;
	/* Computes the possible CashFlowTimes of the Product and stores them into MCPath object */
    virtual unsigned long CashFlows(const MCPath& SpotValues, std::vector<CashFlow>& GeneratedFlows) const=0;
	/* CashFlows generates flows and returns the number of generated flows*/
	//methods
	const MCPath& DiscreteMonitorGetTimes() const;
	/* Returns the Times to be observed */

private:

    MCPath DiscreteMonitor;

};

#endif


