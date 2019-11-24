//
//
//                           MCPath.cpp
//
//
//		Author: J. Kienitz	       
//		Date:   25.03.2006
//
//      Implementation of the MC Path class

#include "MCPath.h"
#include <algorithm>
#include <numeric>
//ww
MCPath::MCPath(unsigned long NoOfFactors_, unsigned long NoOfTimeSteps_): NoOfFactors(NoOfFactors_), NoOfTimeSteps(NoOfTimeSteps_) 
{
	if (NoOfTimeSteps_ <= 0 && NoOfFactors_ <= 0)
	{
		ValuesPtr = 0;
		EndPtr = 0;
	}
	else 
	{
		if(NoOfTimeSteps_ > 0 && NoOfFactors_ >0)
		{
			ValuesPtr = new double[NoOfTimeSteps_ * NoOfFactors_];
			EndPtr = ValuesPtr;
			EndPtr += (NoOfTimeSteps_ * NoOfFactors_);
		}
		else
		{
			if(NoOfTimeSteps_ > 0) ValuesPtr = new double[NoOfTimeSteps_];
			else ValuesPtr = new double[NoOfFactors_];
		}
		EndPtr = ValuesPtr;
		EndPtr += NoOfTimeSteps_ > 0 ? NoOfTimeSteps_ : NoOfFactors_;
	}
	Capacity = EndPtr - ValuesPtr;
}


MCPath::MCPath(const MCPath& original):	NoOfTimeSteps(original.NoOfTimeSteps), Capacity(original.Capacity), NoOfFactors(original.NoOfFactors)
{
	unsigned long newsize;
	if (NoOfTimeSteps <= 0 && NoOfFactors <= 0)
	{
		ValuesPtr = EndPtr = 0;
	}

	if (NoOfTimeSteps > 0 && NoOfFactors >0)
	{
		newsize = NoOfTimeSteps * NoOfFactors;
	}
	else
	{
	
		if(NoOfTimeSteps > 0)
		{
			newsize = NoOfTimeSteps;
		}
		else
		{
			newsize = NoOfFactors;		
		}
	}

		ValuesPtr = new double[newsize];		
		EndPtr = ValuesPtr;
		EndPtr += newsize;
		std::copy(original.ValuesPtr, original.EndPtr, ValuesPtr);
}


MCPath::~MCPath()
{
	if (ValuesPtr >0)
		delete [] ValuesPtr;
}


MCPath& MCPath::operator=(const MCPath& original)
{
	unsigned long orgsize;

	if (&original == this)
		return *this;


	if (original.NoOfTimeSteps > Capacity || original.NoOfFactors > Capacity || original.NoOfTimeSteps * original.NoOfFactors > Capacity)
	{
		if (Capacity > 0)
			delete [] ValuesPtr;
			if (original.NoOfTimeSteps > 0 && original.NoOfFactors > 0) 
			{
				orgsize = original.NoOfTimeSteps * original.NoOfFactors;
			}
			else
			{
				if (original.NoOfTimeSteps > 0) 
				{
					orgsize = original.NoOfTimeSteps;
				}
				else 
				{
					orgsize = original.NoOfFactors;
				}
			}
	}

	ValuesPtr = new double[orgsize];
	Capacity = orgsize;

	NoOfTimeSteps=original.NoOfTimeSteps;

	NoOfFactors=original.NoOfFactors;

	EndPtr = ValuesPtr;
	EndPtr += orgsize;
	
	std::copy(original.ValuesPtr, original.EndPtr, ValuesPtr);


	return *this;
}

void MCPath::resize(unsigned long newNoOfTimeSteps, unsigned long newNoOfFactors)
{
	unsigned long newsize;

	if (newNoOfTimeSteps <= 0 && newNoOfFactors <= 0) newsize = 0;
	else
	{
		if (newNoOfTimeSteps > 0 && newNoOfFactors > 0) newsize = newNoOfTimeSteps * newNoOfFactors;
		else newsize = newNoOfTimeSteps > 0 ? newNoOfTimeSteps : newNoOfFactors;
	}

	if (newsize > Capacity)
	{
		if (Capacity > 0) delete [] ValuesPtr;
		
		ValuesPtr = new double[newsize];
		Capacity = newsize;
	}


	NoOfTimeSteps = newNoOfTimeSteps;

	NoOfFactors = newNoOfFactors;
	
	EndPtr = ValuesPtr;
	EndPtr += newsize;
}


void MCPath::insert(unsigned long factor, unsigned long time, double value)
{
	ValuesPtr[factor * NoOfFactors + time] = value;

}


MCPath& MCPath::operator+=(const MCPath& operand)
{

	
#ifdef RANGE_CHECKING
	if ( NoOfTimeSteps != operand.timesteps() && NoOfFactors!= operand.factors())
	{
		throw("to apply += arrays must be of same timesteps");
	}
#endif 

	for (unsigned long i =0; i < NoOfTimeSteps * NoOfFactors; i++)
		ValuesPtr[i]+=operand[i];

	return *this;
}


MCPath& MCPath::operator-=(const MCPath& operand)
{
		
#ifdef RANGE_CHECKING
	if ( NoOfTimeSteps != operand.timesteps() && NoOfFactors != operand.factors())
	{
		throw("to apply -= arrays must be of same timesteps");
	}
#endif 

	for (unsigned long i =0; i < NoOfTimeSteps * NoOfFactors; i++)
		ValuesPtr[i]-=operand[i];

	
	return *this;
}


MCPath& MCPath::operator/=(const MCPath& operand)
{
	
#ifdef RANGE_CHECKING
	if ( NoOfTimeSteps != operand.timesteps() && NoOfFactors != operand.factors())
	{
		throw("to apply /= arrays must be of same timesteps");
	}
#endif


	for (unsigned long i =0; i < NoOfTimeSteps * NoOfFactors; i++)
		ValuesPtr[i]/=operand[i];

	return *this;
}


MCPath& MCPath::operator*=(const MCPath& operand)
{
	
#ifdef RANGE_CHECKING
	if ( NoOfTimeSteps != operand.timesteps() && NoOfFactors != operand.factors())
	{
		throw("to apply *= arrays must be of same timesteps");
	}
#endif


	for (unsigned long i =0; i < NoOfTimeSteps * NoOfFactors; i++)
		ValuesPtr[i]*=operand[i];

	return *this;
}


/////////////////////////////

MCPath& MCPath::operator+=(const double& operand)
{

	for (unsigned long i =0; i < NoOfTimeSteps * NoOfFactors; i++)
		ValuesPtr[i]+=operand;

	return *this;
}


MCPath& MCPath::operator-=(const double& operand)
{
	for (unsigned long i =0; i < NoOfTimeSteps * NoOfFactors; i++)
		ValuesPtr[i]-=operand;

	
	return *this;
}


MCPath& MCPath::operator/=(const double& operand)
{
	for (unsigned long i =0; i < NoOfTimeSteps * NoOfFactors; i++)
		ValuesPtr[i]/=operand;

	return *this;
}


MCPath& MCPath::operator*=(const double& operand)
{
	for (unsigned long i =0; i < NoOfTimeSteps * NoOfFactors; i++)
		ValuesPtr[i]*=operand;

	return *this;
}


MCPath& MCPath::operator=(const double& val)
{
	for (unsigned long i =0; i < NoOfTimeSteps * NoOfFactors; i++)
		ValuesPtr[i]=val;

	return *this;
}

double MCPath::sum() const
{
	return std::accumulate(ValuesPtr,EndPtr,0.0);

}


double MCPath::min() const
{
	
#ifdef RANGE_CHECKING
	if ( NoOfTimeSteps==0||NoOfFactors==0)
	{
		throw("Array Empty!");
	}
#endif RANGE_CHECKING

	double* tmp = ValuesPtr;
	double* endTmp = EndPtr;

	return *std::min_element(tmp,endTmp);

}


double MCPath::max() const
{
	
#ifdef RANGE_CHECKING
	if ( NoOfTimeSteps == 0 || NoOfFactors == 0)
	{
		throw("Array Empty!");
	}
#endif RANGE_CHECKING
	double* tmp = ValuesPtr;
	double* endTmp = EndPtr;

	return *std::max_element(tmp,endTmp);
}

MCPath MCPath::apply(double f(double)) const
{
	MCPath result(timesteps() * factors());

	std::transform(ValuesPtr,EndPtr,result.ValuesPtr,f);

	return result;

}

double MCPath::last() const
{
	
#ifdef RANGE_CHECKING
	if ( NoOfTimeSteps == 0 || NoOfFactors == 0)
	{
		throw("Array Empty!");
	}
#endif RANGE_CHECKING
	double* tmp = ValuesPtr;
	double* endTmp = EndPtr;

	return *std::max_element(endTmp-1,endTmp-1);
}

