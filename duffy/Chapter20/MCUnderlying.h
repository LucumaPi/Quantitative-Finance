//
//
//
//      MCUnderlying.h
//
//		Class to model the SDE for use in MC simulation
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005
//

#ifndef MCUNDERLYING_H
#define MCUNDERLYING_H

#include <vector>
using namespace std; // dd

// Only defines the interface for Bridge Pattern; Needs an acutal Implementation for each Model;
// e.g. given for constant parameters in the Black-Scholes world

class MCUndParamsBridgeToModel
{

public:
    MCUndParamsBridgeToModel(){}

    virtual MCUndParamsBridgeToModel* clone() const=0;
    virtual double DriftPart(double time1, double time2) const=0;
    virtual double DiffusionPart(double time1, double time2) const=0;
	//virtual double JumpPart(double time1, double time2) const=0;

private:

};

//Big class

class MCUnderlyingParams
{

public:
	MCUnderlyingParams(const MCUndParamsBridgeToModel& MCModel);
    MCUnderlyingParams(const MCUnderlyingParams& original);
    MCUnderlyingParams& operator=(const MCUnderlyingParams& original);
    virtual ~MCUnderlyingParams();

    inline double DriftPart(double time1, double time2) const;
    inline double DiffusionPart(double time1, double time2) const;
	//inline double JumpPart(double time1, double time2) const;
    
    double FirstMoment(double time1, double time2) const;
    double SecondMoment(double time1, double time2) const;
	//double Jump(double time1, double time2) const;

private:

    MCUndParamsBridgeToModel* PtrToModel;

};

inline double MCUnderlyingParams::DriftPart(double time1, double time2) const
{
    return PtrToModel->DriftPart(time1,time2);
}

inline double MCUnderlyingParams::DiffusionPart(double time1, double time2) const
{
    return PtrToModel->DiffusionPart(time1,time2);
}


/*
// Only defines the interface for Bridge Pattern; Needs an acutal Implementation for each Model;
// e.g. given for constant parameters in the Black-Scholes world

class MCUndParamsBridgeToModel
{

public:
    MCUndParamsBridgeToModel(){}

    virtual MCUndParamsBridgeToModel* clone() const=0;
    virtual double DriftPart(double time1, double time2) const=0;
    virtual double DiffusionPart(double time1, double time2) const=0;
	//virtual double JumpPart(double time1, double time2) const=0;

private:

};

*/

//Actual implementation for the Black-Scholes world

class MCUnderlyingParamsConstant : public MCUndParamsBridgeToModel
{
public:

    MCUnderlyingParamsConstant(double constant);
    
    virtual MCUndParamsBridgeToModel* clone() const;
    virtual double DriftPart(double time1, double time2) const;
    virtual double DiffusionPart(double time1, double time2) const;
//  virtial double JumpPart(double time1, double time2) const;

private:

    double Constant;
    double ConstantSquare;

};

#endif