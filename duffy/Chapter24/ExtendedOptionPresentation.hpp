// ExtendedOptionPresentation.hpp
//
// Some functions when working with options.
//
// 2005-10-16 DD Kick-off code (BTW it worked first time
// because of modular approach).
//
// (C) Datasim Education BV 2005
//

#ifndef ExtendedOptionPresentation_HPP
#define ExtendedOptionPresentation_HPP

#include "ExtendedOption.hpp"
#include "excelmechanisms.hpp"
#include "arraymechanisms.hpp"
#include "vector.cpp"
#include "range.cpp"
#include <iostream>

// This class display 1 line graph in Excel
// (Get it working)

enum OptionValueType {Value, Delta, Gamma, Vega, Theta, Rho, Coc, Elasticity};

class ExtendedOptionPresentation
{
private:

		ExtendedOption* curr;

		Range<double> r;	// Extent of x axis
		long nSteps;		// Number of subdivisions


		Vector<double, long> XARR;

		ExtendedOptionPresentation() {}

public:
		ExtendedOptionPresentation(ExtendedOption& option, const Range<double>& extent, 
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

			if (yval == Gamma)
			{
				for (int j = XARR.MinIndex(); j <= XARR.MaxIndex(); j++)
				{

					result[j] = curr -> Gamma(XARR[j]);
				}
		//	print(result);
		///	int yy; cin >> yy;
			}

			if (yval == Vega)
			{
				for (int j = XARR.MinIndex(); j <= XARR.MaxIndex(); j++)
				{

					result[j] = curr -> Vega(XARR[j]);
				}

			}

			if (yval == Theta)
			{
				for (int j = XARR.MinIndex(); j <= XARR.MaxIndex(); j++)
				{

					result[j] = curr -> Theta(XARR[j]);
				}

			}

			if (yval == Rho)
			{
				for (int j = XARR.MinIndex(); j <= XARR.MaxIndex(); j++)
				{

					result[j] = curr -> Rho(XARR[j]);
				}

			}

			if (yval == Coc)
			{
				for (int j = XARR.MinIndex(); j <= XARR.MaxIndex(); j++)
				{

					result[j] = curr -> Rho(XARR[j]);
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
			if (yval == Gamma)
			{
				text = string("Gamma");
			}

			if (yval == Vega)
			{
				text = string("Vega");
			}

			if (yval == Theta)
			{
				text = string("Theta");
			}
			if (yval == Rho)
			{
				text = string("Rho");
			}

			if (yval == Coc)
			{
				text = string("Coc");
			}

			Vector<double, long> yarr = calculate(yval);
		//	cout << "array ..."; int yy; cin >> yy;
		//	print(yarr);
			printOneExcel(XARR, yarr, text);
		}

};

#endif