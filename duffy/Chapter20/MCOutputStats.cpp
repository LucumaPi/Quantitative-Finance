//
//
//
//                          MCOutputStats.cpp
//
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include "MCOutputStats.h"

MCOutput::MCOutput(const MCTemplateClass<MCStats>& Inner_)
: Inner(Inner_)
{
    Counter=1;
	Factor=10;
    MCPaths=0;
}

MCStats* MCOutput::clone() const
{
    return new MCOutput(*this);
}

void MCOutput::StoreValue(double value)
{
    Inner->StoreValue(value);
    ++MCPaths;
    Counter++;

    if (Counter % Factor ==1 && Counter != MCPaths)
    {
        std::vector<std::vector<double> > thisResult(Inner->GetResults());

        for (unsigned long i=0; i < thisResult.size(); i++)
        {
            thisResult[i].push_back(MCPaths);
            ResultsSoFar.push_back(thisResult[i]);
        }
    }

    return;

}

std::vector<std::vector<double> >  MCOutput::GetResults() const
{
    std::vector<std::vector<double> > tmp(ResultsSoFar);

    if (MCPaths != Counter)
    {
        std::vector<std::vector<double> > thisResult(Inner->GetResults());

        for (unsigned long i=0; i < thisResult.size(); i++)
        {
            thisResult[i].push_back(MCPaths);
            tmp.push_back(thisResult[i]);
        }
    }
    return tmp;
}



