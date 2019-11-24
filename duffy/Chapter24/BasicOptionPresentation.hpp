// BasicOptionPresentation.hpp
//
// Some functions when working with options.
//
// 2005-10-16 DD Kick-off code (BTW it worked first time
// because of modular approach).
//
// (C) Datasim Education BV 2005
//

#ifndef BasicOptionPresentation_HPP
#define BasicOptionPresentation_HPP

#include "basicoption.hpp"
#include "excelmechanisms.cpp"
#include "vector.cpp"
#include "range.cpp"

// This class display 1 line graph in Excel
// (Get it working)

enum OptionValueType {Value, Delta};

class BasicOptionPresentation
{
private:

		BasicOption* curr;

		Range<double> r;	// Extent of x axis
		long nSteps;		// Number of subdivisions


		Vector<double, long> XARR;

		BasicOptionPresentation() {}

public:
		BasicOptionPresentation(BasicOption& option, const Range<double>& extent, 
								long NumberSteps)
		{
			r = extent;
			nSteps = NumberSteps;
			curr = &option;

			XARR = r.mesh(nSteps);
		}

		Vector<double, long> calculate(OptionValueType yval)
		{

			// Contains value at end-points
			Vector<double, long> result (nSteps+1, 1);

			if (yval == Value)
			{
				for (int j = XARR.MinIndex(); j <= XARR.MaxIndex(); j++)
				{

					result[j] = curr -> Price(XARR[j]);
				}

			}

			if (yval == Delta)
			{
				for (int j = XARR.MinIndex(); j <= XARR.MaxIndex(); j++)
				{

					result[j] = curr -> Delta(XARR[j]);
				}

			}

			return result;

		}

// RECALL: void printOneExcel(Vector<double, long> & x,	
//						Vector<double, long>& functionResult,string& title)

		void displayinExcel( OptionValueType yval)
		{

			string text("Value");
			if (yval == Delta)
			{
				text = string("Delta");
			}

			Vector<double, long> yarr = calculate(yval);
			printOneExcel(XARR, yarr, text);
		}

};

#endif