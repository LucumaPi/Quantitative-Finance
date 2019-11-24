// Inequalities.hpp

#ifndef Inequalities_HPP
#define Inequalities_HPP

/////////// Useful functions ///////////////////
double DMax(double x, double y)
{
	if (x > y)
		return x;

	return y;
}

double DMin(double x, double y)
{
	if (x < y)
		return x;

	return y;
}

double DMax(double x, double y, double z)
{
	return DMax(DMax(x,y), z);
}

double DMin(double x, double y, double z)
{
	return DMin(DMin(x,y), z);
}
///////////////////////////////////////////////////////
#endif