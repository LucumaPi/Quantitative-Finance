// ivp.cpp
//
// Modelling IVP as a Bridge. Will be the prototype for
// more relevant PDE in QF.
//
// This class is the generic continuous model and it is
// context-free. It is an abstraction and it delegates to
// its implementations. Bridge pattern
//
//	2005-9-20 DD Kick-off
//	2005-9-22 DD Finish
//
// (C) Datasim Education BV 2005
//
// u' + a(x)u = f(x)
//

#ifndef IVP_cpp
#define IVP_cpp

#include "ivpimp.cpp" // Base class for delegated functions
#include "range.cpp"

class IVP
{
public:
		IVPImp* imp;
		double A; // initial value
		Range<double> interval;

		IVP()
		{
			imp = 0;
			A = 1.0;
			interval = Range<double> (0.0, 1.0);
		}

		IVP (IVPImp& executor, const Range<double>& range,
					double initialValue)
		{
			imp = &executor;
			A = initialValue;
			interval = range;
			cout << "Interval " << interval.high() << endl;
		}

		double a(double x)
		{ 
			return imp -> a(x);
		}

		double f(double x)
		{
			return imp -> f(x);
		}

		double startValue() const
		{
			return A;
		}


};

#endif