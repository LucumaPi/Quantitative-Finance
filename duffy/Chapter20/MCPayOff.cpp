//
//
//     MCPayOff.cpp
//
// Standard C++ class hierarchy for 1-factor optioms. It is
// similar to one of the approaches in chapter 8. At the moment
// we have support for call and put options.
//
// This class is in fact a Strategy for the underlyings in this chapter,
// in particular Asian options and Up/Out options.
//
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include "MCPayOff.h"
#include <minmax.h>	// V2 use std::max instead

PayOffCall::PayOffCall(double Strike_) : Strike(Strike_)
{
}

double PayOffCall::operator () (double Spot) const
{
	return max(Spot-Strike,0.0);
}

PayOff* PayOffCall::clone() const
{
    return new PayOffCall(*this);
}


double PayOffPut::operator () (double Spot) const
{
	return max(Strike-Spot,0.0);
}

PayOffPut::PayOffPut(double Strike_) : Strike(Strike_)
{
}

PayOff* PayOffPut::clone() const
{
    return new PayOffPut(*this);
}

