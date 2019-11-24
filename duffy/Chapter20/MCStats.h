//
//
//
//      MCStats.h
//
//		
//		Base class for output statistics.
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#ifndef MC_STATS_H
#define MC_STATS_H

#include <vector>
//#include <NormalDistribution.h>

class MCStats
{
public:

    MCStats(){}

    virtual void StoreValue(double value)=0;
    virtual std::vector<std::vector<double> > GetResults() const=0;
    virtual MCStats* clone() const=0;
    virtual ~MCStats(){}

private:

};

//using templates it is possible to determine what parameters can be collected!!!!

class StatsParam : public MCStats
{

public:

    StatsParam(double quantile);
    virtual void StoreValue(double value);
    virtual std::vector<std::vector<double> > GetResults() const;
    virtual MCStats* clone() const;

private:

    double RunningAverage;
	double RunningAverageVol;
	double CI_Low;
	double CI_High;
	double quantile;
    unsigned long MCPaths;

};

#endif
