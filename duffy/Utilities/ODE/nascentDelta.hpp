// nascentDelta.hpp
//
// Nascent delta functions.
//
// 2005-9-27 DD Kick off
//
// (C) Datasim Education 2006
//

#define eps 0.01

#include <math.h>

double NormalNascentDelta(double x)
{
	double den = 1.0 / (::sqrt (2.0 * 3.1415) * eps);

	return den * :: exp(- 0.5 * (x*x)/(eps * eps));
}

double CauchyNascentDelta(double x)
{

	return eps / (3.1415 * (x*x + eps*eps));
}

double RectangleNascentDelta(double x)
{

	if (x > eps*0.5 || x < - eps*0.5)
	{
		return 0.0;
	}

	return 1.0/eps;

}

double CauchyPhiNascentDelta(double x)
{

	return ::exp(- ::fabs(x/eps))/ (2.0 * eps);

}
