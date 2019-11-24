// TesTAmeriacnOption.cpp
//
// This is code from my first C++ book, chapter 19. You
// can compare style and code with new C++ code. 
//
// 2006-1-9 DD Modified for new book + Excel Output. Changed 
// some input but structure is more or less the same.
// 2006-1-16 DD Code copied, now testing Ameriacn option case
//
// (C) Datasim Component Technology BV 2003-2006
//

//========********** AMERICAN OPTION *************
/* this is now in the class
Vector<V,long> mytmp;
mytmp = Vector<V,long> (J-1, 1);
mytmp = ss.result();
for (long mj = mytmp.MinIndex() + 1; mj <= mytmp.MaxIndex(); mj++)
{
tmp[mj] =(mytmp[mj]>K-XARR[mj]) ? mytmp[mj] : K-XARR[mj];
}
*/ 

#include "exceldriver.hpp"

#include "doublesweep.cpp"
#include "Vector.cpp"
#include "range.cpp"
#include "Characteristics.hpp"
#include "parabolicpde.cpp"
#include "detfunction.cpp"
#include "ParabolicFDM.cpp"
#include "excelmechanisms.hpp" // 2006
#include "arraymechanisms.cpp"
#include "DatasimException.hpp"

#include <list>


int main()
{
	// Set all ranges
	Range<double> X(Xfrom,Xto);
	Range<double> T(Yfrom,Yto);
	
	// Declare all TwoVarDFunctions
	TwoVarDFunction<double,double,double> Sigma(*sigma);
	TwoVarDFunction<double,double,double> Mu(*mu);
	TwoVarDFunction<double,double,double> Forcing(*forcing);
	TwoVarDFunction<double,double,double> B(*b);
	
	// Declare all AtomicDFunctions
	AtomicDFunction<double,double> Ic(*IC);
//	AtomicDFunction<double,double> Bcr(*BCR_Topper_p11);
	AtomicDFunction<double,double> Bcr(*BCR);
	AtomicDFunction<double,double> Bcl(*BCL);
	
	// Declare the pde
	ParabolicPDE<double,double,double> pde(X,T,Sigma,Mu,B,Forcing,Ic,Bcl,Bcr);

	// Declare the finite difference scheme
//	ParabolicFDM<double,double,double> FDM(pde,XINTERVALS,YINTERVALS,THETA); // V1
	int choice = 3;
	cout << "1) Explicit Euler 2) Implicit Euler 3) Crank Nicolson ";
	cin >> choice;

	// New: can create an American option
	OptionType optType = EuropeanPutType;
	ParabolicFDM<double,double,double> FDM(pde,XINTERVALS,YINTERVALS,choice,
												optType);

	// Compute option prices
	FDM.start();
	
	// Retrieve and store option prices
	Vector <double,long> result = FDM.line(); // Does include ENDS!!


///////////////////////////////////////////////////////////

	Vector<double, long> xArr = FDM.xarr();
	Vector<double, long> tArr = FDM.tarr();

	double h = xArr[2] - xArr[1];
	double k = tArr[2] - tArr[1];

	cout << "h " << h << endl;

	// Create and fill Delta vector
	Vector <double,long> DeltaMesh(xArr.Size()-2, xArr.MinIndex());
	for (long kk = DeltaMesh.MinIndex(); kk <= DeltaMesh.MaxIndex(); kk++)
	{
		DeltaMesh[kk] = xArr[kk+1];
	}

	Vector <double,long> Delta(result.Size()-2,result.MinIndex());
	for (long i = Delta.MinIndex(); i <= Delta.MaxIndex(); i++)
	{
		Delta[i] = (result[i+1] - result[i])/(h);
	}
	print(result);
	print(Delta);

	// Create and fill Gamma vector
	Vector <double,long> GammaMesh(DeltaMesh.Size()-2, DeltaMesh.MinIndex());
	for (long p = GammaMesh.MinIndex(); p <= GammaMesh.MaxIndex(); p++)
	{
		GammaMesh[p] = DeltaMesh[p+1];
	}

	Vector <double,long> Gamma(Delta.Size()-2, Delta.MinIndex());
	for (long n = Gamma.MinIndex(); n <= Gamma.MaxIndex(); n++)
	{
		Gamma[n] = (Delta[n+1] - Delta[n])/(h);
	}


	long NP1 = FDM.result().MaxRowIndex();
	long NP = FDM.result().MaxRowIndex() -1;

	Vector <double,long> Theta(result.Size(), result.MinIndex());
	for (long ii = Theta.MinIndex(); ii <= Theta.MaxIndex(); ii++)
	{
		Theta[ii] = -(FDM.result()(NP1, ii) -FDM.result()(NP, ii) )/k;
	}

	try
	{
		printOneExcel(FDM.xarr(), result, string("Price"));
		printOneExcel(DeltaMesh, Delta, string("Delta"));
		printOneExcel(GammaMesh, Gamma, string("Gamma"));
		printOneExcel(FDM.xarr(), Theta, string("Theta"));

	}
	catch(DatasimException& e)
	{
		e.print();

		ExcelDriver& excel = ExcelDriver::Instance();
		excel.MakeVisible(true);	

		long y = 1;
		excel.printStringInExcel(e.Message(), y, y, string("Err"));

		list<string> dump;
		dump.push_back(e.MessageDump()[0]);
		dump.push_back(e.MessageDump()[1]);
		dump.push_back(e.MessageDump()[2]);

		excel.printStringInExcel(dump, 1, 1, string("Err"));

		return 0;
	}

	return 0;
}


