// ExplicitFDM.cpp
//
// ** Explicit Euler ** scheme for the 2-d heat equation.
// The objective is to get an idea of setting up 
// fdm schemes.
//
// Simple case of Dirichlet boundary conditions.
//
// We march in time in both x and y. The results are 
// stored in a matrix for each time level. In total,
// we get a tensor as output.
// 
// DD 2006-12-8 testing and finish off
//
//
// In my book, please see Chapter 18, especially section 18.3
//
// Equations:
//
//			(18.30)
//
// This code is useful because it shows the time-marching features in
// a 2d case. The extension to BS is a matter of adding convection terms
// in each direction.
//
// By understanding the code you can see how a program is built up to solve
// 2d FDM.
//
// (C) Datasim Education BV 2005-2006
//

#include "numericmatrix.cpp"
#include "tensor.cpp"
#include "functionmechanisms.cpp"
#include "matrixmechanisms.cpp"
#include "ExcelDriver.hpp"
#include "ExcelMechanisms.hpp"
#include "DatasimException.hpp"
#include <list>
using namespace std;

// Define initial condition
double IC(double x, double y)
{
//	return x*(1.0 - x) * y * (1.0 - y);
	return (x*x) + (y*y);


}

// Define continuous boundary condition

double BC(double x, double y, double t)
{

	// The boundary itself is hard-coded at
	// the moment; latter model as a geometic
	// object or a formula.

	return 0.0;
//	return (x*x) - (y*y);

}

// Discretized boundary conditions; version 1 (reasonably
// hard-coded). We assume boundary is a rectangle.
void DiscreteBC(const Vector<double, long>& xMesh, const Vector<double, long>& yMesh, 
				double t,double (*BoundaryCondition)(double x, double y, double t),
				NumericMatrix<double, long>& Solution)
{

	// Initialise the 'extremities' of the solution, that is along
	// the sides of the domain

	long i, j; // Index for looping

	// Bottom
	long index = Solution.MinColumnIndex();
	
	for (i = Solution.MinRowIndex(); i <= Solution.MaxRowIndex(); i++)
	{
		Solution(i, index) = (*BoundaryCondition)(xMesh[i], 0.0, t);
	}

	// Top
	index = Solution.MaxColumnIndex();
	
	for (i = Solution.MinRowIndex(); i <= Solution.MaxRowIndex(); i++)
	{
		Solution(i, index) = (*BoundaryCondition)(xMesh[i], yMesh[yMesh.MaxIndex()], t);
	}

	// Left
	index = Solution.MinRowIndex();
	
	for (j = Solution.MinColumnIndex(); j <= Solution.MaxColumnIndex(); j++)
	{
		Solution(index, j) = (*BoundaryCondition)(0.0, yMesh[j], t);
	}

	// Right
	index = Solution.MaxRowIndex();
	
	for (j = Solution.MinColumnIndex(); j <= Solution.MaxColumnIndex(); j++)
	{
		Solution(index, j) = (*BoundaryCondition)(yMesh[yMesh.MaxIndex()], yMesh[j], t);
	}

}


int main()
{
	// Initialise continuous and discrete parameters
	// Region
	double L = 1.0; double M = 1.0;
	double T = 1.0;
	// Step sizes
	long NX = 10; long NY = 10; long NT = 2000;

//	cout << "Number of time steps: "; cin >> NT;

	// Calculated values
	double hx = L / double(NX);
	double hy = M / double(NY);
	double k = T / double(NT);


	cout << "Step sizes : " << hx << ", " << hy << ", " << k << endl;

	// Preprocess
	double a = hx*hx;
	double b = hy*hy;
	double lambda1 = k / a;
	double lambda2 = k / b;
	double factor = 1.0 - 2.0*(lambda1 + lambda2); // Positive for stability!
	cout << "Factor " << factor << endl;

	// Create mesh pooints in x and y directions (Useful)
	Range<double> rx(0.0, L);
	Range<double> ry(0.0, M);
	Vector<double, long> xMesh = rx.mesh(NX); // NX + 1 elements!!
	Vector<double, long> yMesh = ry.mesh(NY); // NY + 1

	// BLOCK "IC"
	// Calculate the discrete initial conditions, in the discrete closure of
	// the discrete domain
	NumericMatrix<double, long> MOld = createDiscreteFunction(IC,xMesh, yMesh);
	
	cout << "Matrix: " << MOld.Rows() << ", " << MOld.Columns() << endl;

	// Modify intial condition to take BC into account
	double current = 0.0; // Time counter
	DiscreteBC(xMesh, yMesh, current, BC, MOld);

	// Now the data structure to hold all values, all start indices 
	// start at 1.
	Tensor<double, long> repository(MOld.Rows(), MOld.Columns(), NT+1);

	long index = 1;	// Index for the array of matrices
	repository[index] = MOld;
	cout << "kk " << repository.sizeThird() << endl;


	// ENDBLOCK "IC"

	// Define matrix to hold values at level n+1
	NumericMatrix<double, long> MNew(MOld);

	cout << "ready";
	// The Marching Process; Calculate the next level values
	// This code mimics very closely the correspodnding FDM scheme
	// as far as notation is concerned


L1: // Calculate the next level

	// Go to next time level
	current += k;
	index++;

	// Discrete BC for level n+1
	DiscreteBC(xMesh, yMesh, current, BC, MNew);
	for (long j = MNew.MinColumnIndex()+1; j <= MNew.MaxColumnIndex() -1 ; j++)
	{
		for (long i = MNew.MinRowIndex()+1; i <= MNew.MaxRowIndex()- 1; i++) 
		{

			MNew(i, j) = (lambda1 * (MOld(i+1, j) + MOld(i-1, j)))
						+ (lambda2 * (MOld(i, j+1) + MOld(i, j-1)))
						+ (factor * MOld(i, j));
		}
	}


	
	// Postprocessing ...
	cout << "Index " << index;
	repository[index] = MNew; // Add matrix to tensor

	if (index < NT + 1) 
	{

		MOld = MNew;
		goto L1;
	}

	// EXCEL OUTPUT PART

	try 
	{

//		printTensorInExcel(repository, xMesh, yMesh, string("2d Heatexp"));
		printMatrixInExcel(repository[5], xMesh, yMesh, string("EXPE"));

	}
	catch(DatasimException& e)
	{
		e.print();

		ExcelDriver& excel = ExcelDriver::Instance();
		excel.MakeVisible(true);	

		excel.printStringInExcel(e.Message(), 1, 1, string("Err"));

		list<string> dump;
		dump.push_back(e.MessageDump()[0]);
		dump.push_back(e.MessageDump()[1]);
		dump.push_back(e.MessageDump()[2]);

		excel.printStringInExcel(dump, 1, 1, string("Err"));

		return 0;
	}

	return 0;
}

