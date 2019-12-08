// testHeatEquationExact.cpp
//
// 2005-9-20 DD kick off
// 2005-9-26 DD new stuff fo IBVP
// 2005-10-9 DD code for exact solution of heat equation
// 2005-12-1 DD Heat equation null test exact solution from
// Smith 1978 page 15
//
// Good example to show how to present in Excel
//
// (C) Datasim Education BV 2005
//
#include "ExcelMechanisms.hpp"
#include "mesher.hpp"
#include "vector.cpp"
#include "StringConversions.hpp"
#include <math.h>
#include <list>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "matrixmechanisms.cpp"

//
// 
// Use special code names for specific exact solutions
//
// We have three functions for presentation
//
//	1. Get the solution at one point (x,t)
//									: output double
//	2. Get the solution at a space array and one time (xarr, t)
//									: output Vector
//	3. Get solution for a space array for a number of time levels
//									: output list<Vector>
//
// This idea can be applied to other problems. For example, we could
// use function pointers 
//	
//				double (*f) (doible x, double t)
//
// Here are the steps for the IBV problem
//
//		Ut = Uxx for 0 < x < 1, t > 0
//		
//		BC U(0,t) = U(1,t) = 0, t > 0
//		IC
//				U(x,0) = 2x for 0 <= x <= 0.5
//				U(x,0) = 2(1-x) for 0.5 <= x <= 1.0
//

vector<string> AskChartAnnotation()
{

	cout << "Title: ";
	string title; cin >> title;

	cout << "Horizontal: ";
	string hor = "X Space";// cin >> hor;

	cout << "Vertical: ";
	string ver = "Temp";// cin >> ver;

	cout << "Legend: ";
	string legend; cin >> legend;

	vector<string> result(4);
	result[0] = title;
	result[1] = hor;
	result[2] = ver;
	result[3] = legend;


	return result;
}



// Step 1
double SeriesSolution(double x, double t)
{ // Exact solution using separation of variable; one point(x,t)

	double A, tmp;
	double nd = 1.0;

	double pi = 3.1415; double pi2 = pi*pi; double a = 8.0/pi2;

	double result = 0.0; double tol = 0.001;

L1: // Excuses ! This is the only scenario where I use it


	A = a * ::sin (0.5 * nd * pi)/(nd*nd);

	tmp = ::exp(- nd * nd * pi2 * t);
	
	result += A * ::sin(nd * pi * x) * tmp;

	if (tmp >= tol && tmp != 1.0)
	{ // Keep summing series until terms become small enough

		nd += 1.0;
		goto L1;
	}

	return result;

}

// Step 2
Vector<double, long> SeriesSolutionArray(const Vector<double, long>& xarr, double t)
{ // Exact solution using separation of variable

	Vector<double, long> result	(xarr);	// Dimension aligning

	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		result[j] = SeriesSolution(xarr[j], t);
	}

	return result;
}


// Step 2 for a special time level
void printSeriesSolutionArray()
{
	Mesher m(0.0, 1.0, 0.0, 1.0);

	cout << "Number of space subdivisions: ";
	int J; cin >> J;

	cout << "At what time level in interval (0, 1): ";
	double v; cin >> v;

	Vector<double, long> XARR = m.xarr(J);

	Vector<double, long> value = SeriesSolutionArray(XARR, v);
	
	vector<string> anno = AskChartAnnotation();
	printOneExcel(XARR, value, anno[0], anno[1], anno[2], anno[3]);
}

// Step 3 printing
void printSeriesSolutionListOfArray()
{ 

	Mesher m(0.0, 1.0, 0.0, 1.0);

	cout << "Number of space subdivisions: ";
	int J; cin >> J;

	cout << "Number of time subdivisions: ";
	int N; cin >> N;

	Vector<double, long> XARR = m.xarr(J);
	Vector<double, long> TARR = m.yarr(N);

	list<Vector<double, long> > result;
	list<string> labels;
	
	for (long j = TARR.MinIndex(); j <= TARR.MaxIndex(); j++)
	{
			result.push_back(SeriesSolutionArray(XARR, TARR[j]));
			labels.push_back(getString(TARR[j]));
	}

	vector<string> anno = AskChartAnnotation();
	printInExcel(XARR, labels, result, anno[0], anno[1], anno[2]);
}

void printMatrixSolution()
{ 

	Mesher m(0.0, 1.0, 0.0, 1.0);

	cout << "Number of space subdivisions: ";
	int J; cin >> J;

	cout << "Number of time subdivisions: ";
	int N; cin >> N;

	Vector<double, long> XARR = m.xarr(J);
Vector<double, long> TARR = m.yarr(N);

	// Start row + column == 1
	NumericMatrix<double, long> result(N+1, J+1, 1, 1);
	list<string> labels;

	for (long i = TARR.MinIndex(); i <= TARR.MaxIndex(); i++)
	{
		for (long j = XARR.MinIndex(); j <= XARR.MaxIndex(); j++)
		{
			result(i, j) = SeriesSolution(XARR[j], TARR[i]);
		}
	}

	print(result);

//	cout << result.Rows() << ", " << result.Columns() << endl;

	printMatrixInExcel(result, TARR, XARR, string("EXACT"));
}



int main()
{

	int choice; // It's one or the other
	cout << "1) one time level, 2) multiple time levels, 3) Multiple charts: ";
	cin >> choice;
	
	if (choice == 1)
	{
		printSeriesSolutionArray();
	}
	else if (choice == 2)
	{
		printSeriesSolutionListOfArray();
	}
	else
	{
		printMatrixSolution();
	}
	
	return 0;
}