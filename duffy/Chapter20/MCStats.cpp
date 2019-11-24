//
//
//                           MCStats.cpp
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include "MCStats.h"
#include "NormalDist.h"
#include <cmath>
using namespace std;

StatsParam::StatsParam(double quantile_)
    :
    RunningAverage(0.0), RunningAverageVol(1.0), CI_Low(0.0), CI_High(0.0), quantile(quantile_), MCPaths(0UL)
{
}
    
void StatsParam::StoreValue(double value)
{
    MCPaths++;
    RunningAverage = RunningAverage + (value - RunningAverage)/MCPaths;
	if(MCPaths > 2) 
	{
		RunningAverageVol = (MCPaths-2)/(MCPaths-1)*RunningAverageVol + MCPaths*(value-RunningAverage)*(value - RunningAverage)/MCPaths/MCPaths;
		CI_Low = RunningAverage - quantile * sqrt(RunningAverageVol / MCPaths);
		CI_High = RunningAverage + quantile * sqrt(RunningAverageVol / MCPaths);
	}
	
}

vector<vector<double> > StatsParam::GetResults() const
{
    vector<vector<double> > Results(1); //number specifies the number of output vectors

    Results[0].resize(4);				//gives number of entries to be pathed back
    Results[0][0] = RunningAverage;
	Results[0][1] = RunningAverageVol;
	Results[0][2] = CI_Low;
	Results[0][3] = CI_High;


    return Results;
}

MCStats* StatsParam::clone() const
{
    return new StatsParam(*this);
}