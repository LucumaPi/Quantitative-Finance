//
//
//
//                  MCUnderlying.cpp
//
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005

#include "MCUnderlying.h"

MCUnderlyingParams::MCUnderlyingParams(const MCUndParamsBridgeToModel& MCModel)
{
   PtrToModel = MCModel.clone();
}

MCUnderlyingParams::MCUnderlyingParams(const MCUnderlyingParams& original)
{
   PtrToModel = original.PtrToModel->clone();
}

MCUnderlyingParams& MCUnderlyingParams::operator=(const MCUnderlyingParams& original)
{
   if (this != &original)
   {   
      delete PtrToModel;
      PtrToModel = original.PtrToModel->clone();
   }
   return *this;
}

MCUnderlyingParams::~MCUnderlyingParams()
{
   delete PtrToModel;
}

double MCUnderlyingParams::FirstMoment(double time1, double time2) const
{
    double total = DriftPart(time1,time2);
    return total/(time2-time1);
}

double MCUnderlyingParams::SecondMoment(double time1, double time2) const
{
    double total = DiffusionPart(time1,time2);
    return total/(time2-time1);
}



// Implementation for Black-Scholes Model; constant drift and constant vol

double MCUnderlyingParamsConstant::DriftPart(double time1, double time2) const
{
    return (time2-time1)*Constant;
}

double MCUnderlyingParamsConstant::DiffusionPart(double time1, double time2) const
{
    return (time2-time1)*ConstantSquare;
}

MCUnderlyingParamsConstant::MCUnderlyingParamsConstant(double constant)
{
    Constant = constant;
    ConstantSquare = Constant*Constant;
}

MCUndParamsBridgeToModel* MCUnderlyingParamsConstant::clone() const
{
    return new MCUnderlyingParamsConstant(*this);
}
