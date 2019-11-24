// MadeTwoFactor.cpp
//
/////////////////////////////////////////////////////////////////
///
// This scheme is for 2-factor basket option. the setup is based on
// the code and structure for the explicit Euler for the 2d heat equation
//
// Differences
//
//	1. Initial and boundary conditions are now part of the TwoBasketOption class.
//	2. More parameters to initialise than in the 1d case.
//
//////////////////////////////////////////////////////////////////
//
// Simple case of Dirichlet boundary conditions.
//
// We march in time in both x and y. The results are 
// stored in a matrix for each time level. In total,
// we get a tensor as output.
// 
// DD 2005-12-8 testing and finish off
// DD 2006-1-30 new code for basket
// DD 2006-2-2 1 now use new payoff functions of options on the boundaries
// DD 2006-2-10 Option to print array of matrix results (Tensor) or just the
// matrix at t = N; also interactive selection of NX, NY, NT. Also optimising
// the loops.
// DD 2006-5-18 New efficient matrix class
//
// In my book, please see Chapte 24, especially sections on explicit
// Euler.
//
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

#include "vector.cpp"
//#include "numericmatrix.cpp"
#include "numericmatrix3.hpp" // 1 d vector now
//#include "tensor.cpp"
#include "tensor2.cpp" // ditto
#include "functionmechanisms.cpp"
#include "matrixmechanisms.cpp"
#include "ExcelDriver.hpp"
#include "ExcelMechanisms.hpp"
#include "DatasimException.hpp"
#include "TwoBasketOption.hpp"	// New, 2-factor IBVP
#include <list>
using namespace std;

#include "clock.hpp" // For timing


// In this the parameters of the Basket Option need to be initialised
// and we do this using several factories. In the current case we have defined
// a simple Console factory in order the test the algorithm.

InstrumentFactory* GetInstrumentFactory()
{
	int choice = 1;
	cout << "Factories: 1) Console 2) Prototype ";
	cin >> choice;

	if (choice == 1)
	{
		return new ConsoleInstrumentFactory;
	}
	else
	{
		return new PrototypeInstrumentFactory;
	}
}

////
////////////////////// Block for discrete Boundary and Initial Conditions //////////////////////////////////
////
// Discretized boundary conditions; version 1 (reasonably
// flexible because we are talking to an Option). We assume boundary is a rectangle.
void DiscreteBCatTimeZero(const Vector<double, long>& xMesh, const Vector<double, long>& yMesh, 
						  TwoBasketOption& option)
//						  NumericMatrix3<double, long, xMesh.Size(), yMesh.Size()>& Solution)
{
	// The boundaries when t = 0; IT'S DIFFERENT
	// Initialise the 'extremities' of the solution, that is along
	// the sides of the domain

	const long NR = xMesh.Size();
	const long NC = yMesh.Size();
	//extern NumericMatrix3<double, long, NR, NC> MOld;

	long i, j; // Index for looping
	long index;

	double t = 0.0;	// Initial time

	index = MOld.MinColumnIndex();
	// Bottom (Put option)
	for (i = MOld.MinRowIndex()+1; i <= MOld.MaxRowIndex(); i++)
	{
		MOld(i, index) = option.downOption.payoff(xMesh[i]);
	}

	// Top
	index = MOld.MaxColumnIndex();
	
	for (i = MOld.MinRowIndex()+ 1; i <= MOld.MaxRowIndex(); i++)
	{
		MOld(i, index) = option.BCUpper(xMesh[i], t);
	}

	// Left
	index = MOld.MinRowIndex();
	
	for (j = MOld.MinColumnIndex(); j <= MOld.MaxColumnIndex(); j++)
	{
		MOld(index,j) = option.leftOption.payoff(yMesh[j]);
		
	}

	// Right
	index = MOld.MaxRowIndex();
	
	for (j = MOld.MinColumnIndex()+1; j <= MOld.MaxColumnIndex(); j++)
	{
		MOld(index, j) = option.BCRight(yMesh[j], t);
	}


}

void DiscreteBC(const Vector<double, long>& xMesh, const Vector<double, long>& yMesh, double t,
				TwoBasketOption& option, 
				NumericMatrix3<double, long, xMesh.Size(), yMesh.Size()>& Solution)
{
	// Initialise the 'extremities' of the solution, that is along
	// the sides of the domain

	long i, j; // Index for looping

	// Bottom
	long index = Solution.MinColumnIndex();
	for (i = Solution.MinRowIndex()+1; i <= Solution.MaxRowIndex(); i++)
	{

		Solution(i, index) = option.BCUnder(xMesh[i], t);
	}

	// Top
	index = Solution.MaxColumnIndex();
	
	for (i = Solution.MinRowIndex()+1; i <= Solution.MaxRowIndex(); i++)
	{
		Solution(i, index) = option.BCUpper(xMesh[i], t);
	}
	// Left
	index = Solution.MinRowIndex();
	
	for (j = Solution.MinColumnIndex(); j <= Solution.MaxColumnIndex(); j++)
	{
		Solution(index, j) = option.BCLeft(yMesh[j], t);
	}

	// Right
	index = Solution.MaxRowIndex();
	
	for (j = Solution.MinColumnIndex()+1; j <= Solution.MaxColumnIndex(); j++)
	{
		Solution(index, j) = option.BCRight(yMesh[j], t);
	}

}

void DiscreteIC(const Vector<double, long>& xMesh, const Vector<double, long>& yMesh, 
				const TwoBasketOption& option, 
				NumericMatrix3<double, long, xMesh.Size(), yMesh.Size()>& Solution)
{
	// Initialise the matrix in the interior of the domain
	for (long j = Solution.MinColumnIndex()+1; j <= Solution.MaxColumnIndex() -1 ; j++)
	{
		for (long i = Solution.MinRowIndex()+1; i <= Solution.MaxRowIndex()- 1; i++) 
		{

			Solution(i,j) = option.IC(xMesh[i], yMesh[j]);
		}
	}
	
}

////
//////////////// End of Discrete Boundary and Initial Conditions ////////////////////////////////
////

TwoFactorOptionData* getOption()
{
	// Choose which factory you want and initialise the data
	InstrumentFactory* myFactory = GetInstrumentFactory();
	TwoFactorOptionData* myOptionData = myFactory ->CreateOption();

	return myOptionData;
}

int main()
{
	//
	/////////////////////////////////////////////////////////////////////////////////////
	// Now have to create a 2-factor basket option. All data and functionality will be 
	// extracted from it.
	//
	//
			// Steps
			// 1. Create option data (via Factory)
			// 2. Create the basket option == IBVP + Data

			TwoFactorOptionData* optData = getOption();

			// Create mesh pooints in x and y directions (Useful)
			Range<double> rx(0.0, optData->SMax1);
			Range<double> ry(0.0, optData->SMax2);
			Range<double> rt(0.0, optData->T);

			// Step sizes
			long NX = 40; long NY = 80; long NT = 100;

			cout << "Extent in S1 " << optData->SMax1 << endl;
			cout << "Extent in S2 " << optData->SMax2 << endl;
			cout << "Extent in T dir " << optData->T << endl;

			cout << "Explicit method for basket (Topper 2005)\n";
			cout << "!!CHOOSE ENOUGH TIME STEPS\n";
			cout << "Give NX: "; cin >> NX; cout << endl;
			cout << "Give NY: "; cin >> NY; cout << endl;
			cout << "Give NT: "; cin >> NT; cout << endl;

			double hx = optData->SMax1 / double(NX);
			double hy = optData->SMax2 / double(NY);
			double k = optData->T / double(NT); 

			Vector<double, long> xMesh = rx.mesh(NX); // NX + 1 elements!!
			Vector<double, long> yMesh = ry.mesh(NY); // NY + 1

			print(xMesh); print(yMesh);

			// Define two stack matrices
			const long cNX = xMesh.Size();
			const long cNY = yMesh.Size();
			NumericMatrix3<double, long, cNX, cNY)> MOld(xMesh.MinIndex(), yMesh.MinIndex());
			NumericMatrix3<double, long, cNX, cNY)> MNew(MOld);


			TwoBasketOption opt(rx, ry, rt, *optData); // Works with a copy of the data

			// This part of code is not really optimal but it works
			// For the moment we work with copies
			delete optData;

						
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////
	//
	// BLOCK "IC"
	// Calculate the discrete initial conditions, in the discrete closure of
	// the discrete domain
	//
	//NumericMatrix3<double, long, xMesh.Size(), yMesh.Size()> MOld(xMesh.MinIndex(), yMesh.MinIndex());

	DiscreteIC(xMesh, yMesh, opt, MOld);
	

	// Modify intial condition to take BC into account
	double current = 0.0; // Time counter
	DiscreteBCatTimeZero(xMesh, yMesh, opt, MOld);

	// Now the data structure to hold all values, all start indices 
	// start at 1.
	bool storeData = false;
	long tensorSize = 1;
	long index = 1;	// Index for the array of matrices
	

	cout << "Choose a tensor output (Y/y)?"; char choice; cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		tensorSize = NT + 1;
		storeData = true;
	}

	//Tensor2<double, long> repository(MOld.Rows(), MOld.Columns(), tensorSize);

	cout << "initialised";

	if (storeData == true)
	{
	//	repository[index] = MOld;
	}

//	print(MOld);
	cout << "kk " << repository.sizeThird() << endl;


	// ENDBLOCK "IC"

	// Define matrix to hold values at level n+1
	NumericMatrix3<double, long, xMesh.Size(), yMesh.Size()> MNew(MOld);

	cout << MNew.Rows() << ", " << MNew.Columns() << endl;
	int kk; cin >> kk;

	cout << "ready";
	// The Marching Process; Calculate the next level values
	// This code mimics very closely the correspodnding FDM scheme
	// as far as notation is concerned


	// The compass 9 point scheme
	double aW, aS, aE, aN, aC;
	double aSW, aSE, aNE, aNW;
	double madeFactor;			// Coefficient of U(n+1, i, j)

	// Preprocess, CFL-type variables
	double hx2 = hx*hx;
	double hy2 = hy*hy;
	double lambda1 = k / hx2;
	double lambda2 = k / hy2;
	double alpha = 0.25 * k /(hx*hy);
	double beta = 0.5 * k / hx;
	double gamma = 0.5 * k / hy;


	// Temp variables in loops
	double xtmp, ytmp;				// mesh points
	double difftmp1, difftmp2, contmp1, contmp2; // functions

	cout << "loop";

	// Loop constants
	long MinC = MNew.MinColumnIndex()+1;
	long MaxC = MNew.MaxColumnIndex() -1;
	long MinR = MNew.MinRowIndex()+1;
	long MaxR = MNew.MaxRowIndex()- 1;

	DatasimClock timer;
	timer.start();

	double t1, t2, t3, t4;

L1: // Calculate the next level
	current += k;

	// Discrete BC for level n+1; We use the points of the Compass so that we have 
	// 9 points
	DiscreteBC(xMesh, yMesh, current, opt, MNew);
	for (long j = MinC; j <= MaxC; j++)
	{
		for (long i = MinR; i <= MaxR; i++) 
		{
			xtmp = xMesh[i];
			ytmp = yMesh[j];
			difftmp1 = opt.diffusion1(xtmp, ytmp, current);
			difftmp2 = opt.diffusion2(xtmp, ytmp, current);
			contmp1 = opt.convection1(xtmp, ytmp, current);
			contmp2 = opt.convection2(xtmp, ytmp, current);

			// Initialise the coefficients
/*			aW = lambda1* difftmp1 - beta * contmp1;
			aE = lambda1* difftmp1 + beta * contmp1;
			aS = lambda2* difftmp2 - gamma * contmp2;
			aN = lambda2* difftmp2 + gamma * contmp2; */

			t1 = lambda1* difftmp1;
			t2 = beta * contmp1;
			t3 = lambda2* difftmp2;
			t4 = gamma*contmp2;

			aW = t1 - t2;
			aE = t1 + t2;
			aS = t3 - t4;
			aN = t3 + t4;

			aSW = alpha * opt.crossTerm(xtmp, ytmp, current);
			aSE = - aSW; aNE = aSW; aNW = -aSW;	

//			aC = 1.0 - 2.0 * (lambda1* difftmp1 + lambda2* difftmp2)
//				+ k * opt.zeroTerm(xtmp, ytmp, current);

			aC = 1.0;

			madeFactor = 1.0 + 2.0 * (lambda1* difftmp1 + lambda2* difftmp2)
				- k * opt.zeroTerm(xtmp, ytmp, current);


			MNew(i, j) = aW * MOld(i-1,j) + aS * MOld(i,j-1) 
						+ aE * MOld(i+1, j) + aN * MOld(i,j+1)
						+ aSW * MOld(i-1,j-1) + aSE * MOld(i+1,j-1) 
						+ aNE * MOld(i+1,j+1) + aNW * MOld(i-1,j+1)
						+ aC * MOld(i,j);
						
			MNew(i,j) /= madeFactor;
		//	cout << "fac " << madeFactor << ", " << i << ", " << j << endl;
		}
	}
	
	// Postprocessing ...
	// Go to next time level
	index++;
	cout << index << ",";

	if (storeData == true)
	{
		//repository[index] = MNew; // Add matrix to tensor
	}

//print(MNew);
//int uu; cin >> uu;

	if (index < NT) 
	{

		MOld = MNew;
		goto L1;
	}

	timer.stop();
	timer.print();
	
	// EXCEL OUTPUT PART

	try 
	{
		long freq = 20;
	//	printTensorInExcel(repository, xMesh, yMesh, string("2d Heatexp"), freq);
//		printMatrixInExcel(repository[NT+1], xMesh, yMesh, string("EXPE"));
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

	try
	{
	
		if (storeData == true)
		{
			cout << "Number of time steps is " << NT << ", Frequency? ";
			int freq; cin >> freq;
		//	printTensorInExcel(repository, xMesh, yMesh, string("Basket"), freq);
		}
		else
		{
	//		printMatrixInExcel(MNew, xMesh, yMesh, string("Price at N"));
//			print(MNew);

		}
	}

	catch (DatasimException& e)
	{
			e.print();
			return 0;
	}

	return 0;
}

/* V1 code

	aW = lambda1*opt.diffusion1(xMesh[i], yMesh[j], current) 
				- beta * opt.convection1(xMesh[i], yMesh[j], current);
		aE = lambda1*opt.diffusion1(xMesh[i], yMesh[j], current) 
				+ beta * opt.convection1(xMesh[i], yMesh[j], current);
		aS = lambda2*opt.diffusion2(xMesh[i], yMesh[j], current) 
				- gamma * opt.convection2(xMesh[i], yMesh[j], current);
		aN = lambda2*opt.diffusion2(xMesh[i], yMesh[j], current) 
				+ gamma * opt.convection2(xMesh[i], yMesh[j], current);

		aSW = alpha * opt.crossTerm(xMesh[i], yMesh[j], current);
		aSE = - aSW; aNE = aSW; aNW = -aSW;	

		aC = 1.0 - 2.0 * (lambda1*opt.diffusion1(xMesh[i], yMesh[j], current) + lambda2*opt.diffusion2(xMesh[i], yMesh[j], current))
			+ k * opt.zeroTerm(xMesh[i], yMesh[j], current);
*/
