// LinearRegression.cpp
//
// A linear regression model in C. We keep everything 
// in one file for convenience
//
// Of course, an OO treatment is more powerful but that's
// not the objective of the exercise.
//
// Steps:
//			1. Create the arrays of points
//			2. Calculate the coefficients of the linear
//			    regression line
//          3. Do a test to see if it works
//
//	DD 2005-1-3 Kick-off code
//	DD 2005-11-19 Round off stuff and improvements
//
// (C) Datasim Education BV 2005
//

// Basic structs

#include <iostream>
using namespace std;

struct Point 
{
	double x;
	double y;
};

Point createPoint(double x, double y)
{
	Point result;

	result.x = x;
	result.y = y;

	return result;
}

struct Line 
{ // a + bx

	double a;
	double b;

	void print() const { cout << "a + bx: a = " << a << ", b =  " << b << endl;}
	double value(double xval) const { return a + b*xval; }
};

double getValue(Line lin, double xval)
{
	return lin.a + (lin.b * xval);
}

// Properties of vectors
double sum(double* x, int n)
{ // Sum of elements     

		double ans = x[0];

		for (int j = 1; j < n; j++)
		{
			ans += x[j];
		}

		return ans;
} 

double sumSquares(double* x, int n)
{ // Sum of squares

		double ans = x[0] * x[0];
		
		for (int j = 1; j < n; j++)
		{
			ans += (x[j] * x[j]);
		}

		return ans;
}

double innerProduct(double* x, double* y, int n)
{ // Inner product

		double ans = x[0] * y[0];
		
		for (int j = 1; j < n; j++)
		{
			ans += (x[j] * y[j]);
		}

		return ans;
}



Line LinearRegressionLine (double* xarr, double* yarr, int N)
{ // Find the regression line for a set of input data

	// Now the parameters for the linear regression line
	double sumx = sum(xarr, N);
	double sumy = sum(yarr, N);

	//cout << sumx << ". " << sumy << endl;

	double sumSx = sumSquares(xarr, N);
	double sumSy = sumSquares(yarr, N);
	// cout << sumSx << "," << sumSy << endl;

	double ip = innerProduct(xarr, yarr, N);
	// cout << "inner prod: " << ip << endl;

	double denominator = double(N)*sumSx - (sumx*sumx);
	double A = (sumy*sumSx - (sumx*ip))/denominator;
	double B = (double(N)*ip - (sumx*sumy))/denominator;

	Line lin;
	lin.a = A;
	lin.b = B;
	
	return lin;
}




int main()
{

	const int N = 4;
	struct Point polyline[N];

	for (int j = 0; j < N; j++)
	{
		polyline[j] = createPoint(j, j);

		cout << polyline[j].x << ", " << polyline[j].y << endl;
	}
	
	// Now extract the x and y arrays
	double* xarr = new double[N];
	double* yarr = new double[N];

	for (int i = 0; i < N; i++)
	{
		xarr[i] = polyline[i].x;
		yarr[i] = polyline[i].y;
		cout << xarr[i] << ", " << yarr[i] << endl;
	}

	
	double xval;
	cout << "Give x value: ";
	cin >> xval;


	Line lin = LinearRegressionLine (xarr, yarr, N);
	lin.print();

	cout << "Y value is: " << lin.value(xval);

	// Now example with 'real' data
	double Xarr[] = {65, 63, 67, 64, 68, 62, 70, 66, 68, 67, 69, 71};
	double Yarr[] = {68, 66, 68, 65, 69, 66, 68, 65, 71, 67, 68, 70};

	int n = 12;
	lin = LinearRegressionLine (Xarr, Yarr, n);
	lin.print();
	cout << "Give x value: ";
	cin >> xval;

	cout << "Y value is: " << lin.value(xval);


	delete [] xarr; delete [] yarr;

	return 0;
}

