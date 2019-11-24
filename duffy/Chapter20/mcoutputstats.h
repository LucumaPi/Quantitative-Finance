//
//
//      MCOutputStats.h
//
//		Output information pertaining to the MC simulation.
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#ifndef MC_OUTPUT_STATS_H
#define MC_OUTPUT_STATS_H
#include "MCStats.h"
#include "MCTemplateClass.h"

class MCOutput : public MCStats
{
public:

    MCOutput(const MCTemplateClass<MCStats>& Inner_);

    virtual MCStats* clone() const;
    virtual void StoreValue(double value);
    virtual std::vector<std::vector<double> > GetResults() const;

    
private:

    MCTemplateClass<MCStats> Inner;
    std::vector<std::vector<double> > ResultsSoFar;
    unsigned long Counter;
	unsigned long Factor;
    unsigned long MCPaths;
};

#endif