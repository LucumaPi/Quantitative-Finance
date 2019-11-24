// TestTechnicalAnalysis.cpp
//
// Program to test data structures in Technical Analysis
//
// 2004-9-19 DD Kick-off
//
// (C) Datasim BV 1993-2004
//

#include "SimplePropertySet.cpp"
#include "datetimemechanisms.hpp"
#include "arraymechanisms.cpp"

/*
enum DateType	
{			STD,		// d[d]-mon-yy[yy]
			EUROPEAN,	// d[d]-m[m]-yy[yy]
			ANSI,		// yy[yy]-m[m]-d[d]
			AMERICAN	// m[m]-d[d]-yy[yy]
};

// Print a Date in some format and give your delimiter
void print(const DatasimDate& date, DateType dtype, char delimiter = '/');
*/


void printTS(const SimplePropertySet<DatasimDate,  SimplePropertySet<string, double> >& ts)
{ // Print a time series 'ts' by use of an outer iterator and an inner iterator

	// Useful code because we can see the use of two STL iterators, one is the outer
	// and the other is the inner

	SimplePropertySet<DatasimDate,  SimplePropertySet<string, double> >::const_iterator itO;
	
	cout << "\n Printing a time series\n";

	DatasimDate current;

	for (itO = ts.Begin(); itO!= ts.End(); itO++)
	{ // Outer loop

		current = (*itO).first;
		print(current, STD); cout << " -> ";

		// Inner Loop
		SimplePropertySet<string,double>::const_iterator itI;
	
		for (itI = (*itO).second.Begin(); itI != (*itO).second.End(); itI++)
		{ 
	
			cout << (*itI).first << ", " << (*itI).second << "::";
		}

		cout << endl;
	}
	
	

}

int main()
{

	// Offsets; quarters + half years
	cout << "Offset stuff\n";
	DatasimDate today;
	print(today, STD, '-');


	int nYears = 2;
	int nPeriodsperYear = 4;
	Vector<DatasimDate, int> result = createDateArray(today, nYears, nPeriodsperYear);
//	print(result);

	typedef SimplePropertySet<string, double> CandleStickNode;
	CandleStickNode candlestickPrototype; // Bullish
	candlestickPrototype.add("DH", 100.0);	// Daily High
	candlestickPrototype.add("DL", 70.0);	// Daily Low
	candlestickPrototype.add("CP", 90.0);	// Closing Price
	candlestickPrototype.add("OP", 80.0);	// Opening Price

	SimplePropertySet<DatasimDate,  CandleStickNode> timeSeries;

	// Now populate the Time series at each date with the default Prototype values

	for (int j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		timeSeries.add(result[j], candlestickPrototype);

	}

	printTS(timeSeries);

	// Now add new information/property to the candlestick and insert into
	// time series. Shows the flexibility of our data structure.
	candlestickPrototype.add("Volume", 1000);	// Trading Volume

	/* Use the modifier function
	void value(const N& name, const V& value) const;	// Change value of Property, key 'name'
	*/

	for (int j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		timeSeries.value(result[j], candlestickPrototype);

	}


	printTS(timeSeries);

/*
	SimplePropertySet<string, double> newCandleStick;
	newCandleStick.add(string("DH"), 200.0);	// BIG HIGH
	newCandleStick.add("DL", 70.0);	// Daily Low
	newCandleStick.add("CP", 90.0);	// Closing Price
	newCandleStick.add("OP", 80.0);	// Opening Price

	timeSeries.value(result[result.MaxIndex()], newCandleStick);

	// Find Band Level (Closing price, most interesting)
	SimplePropertySet<string, double> current = timeSeries.value(result[result.MinIndex()]);
	double high = current.value("DH");
	double tmp = high;

	for (j = result.MinIndex()+1; j <= result.MaxIndex(); j++)
	{
		current = timeSeries.value(result[j]);
		tmp = current.value("DH");
		if (tmp > high)
			high = tmp;
	}

	cout << "High Value: " << high << endl;
*/
	return 0;

}