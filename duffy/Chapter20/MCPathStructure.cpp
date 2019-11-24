//
//
//                      MCPathStructure.cpp
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include "MCPathStructure.h"

//implements the construction
PathStructure::PathStructure(const MCPath& DiscreteMonitor_) : DiscreteMonitor(DiscreteMonitor_)
{}

//implements methods
const MCPath& PathStructure::DiscreteMonitorGetTimes() const
{
    return DiscreteMonitor;
}

